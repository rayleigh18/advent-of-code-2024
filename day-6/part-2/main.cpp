#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <future>
#include <chrono>
#include <bitset>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i < threads; ++i)
            workers.emplace_back([this] {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }

    template<class F>
    future<typename result_of<F()>::type> enqueue(F&& f) {
        using return_type = typename result_of<F()>::type;
        auto task = make_shared<packaged_task<return_type()>>(forward<F>(f));
        future<return_type> res = task->get_future();
        {
            unique_lock<mutex> lock(queue_mutex);
            if(stop)
                throw runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(thread &worker: workers)
            worker.join();
    }

private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

void updateDirection(int& direction) {
    direction = (direction + 1) % 4;
}

pair<int, int> getNext(pair<int, int> current, int direction) {
    pair<int, int> next;
    if (direction == 0) {
        next = make_pair(current.first - 1, current.second);
    }
    else if (direction == 1) {
        next = make_pair(current.first, current.second + 1);
    }
    else if (direction == 2) {
        next = make_pair(current.first + 1, current.second);
    }
    else {
        next = make_pair(current.first, current.second - 1);
    }
    return next;
}

bool isMapHaveLoop(pair<int, int> start, const vector<vector<char>>& map, vector<vector<bitset<4>>>& directionMap, int direction) {
    auto current = start;
    const int rowSize = map.size();
    const int colSize = map[0].size();
    
    directionMap[current.first][current.second].set(direction);
    
    while (true) {
        auto next = getNext(current, direction);
        if (next.first < 0 || next.first >= rowSize || next.second < 0 || next.second >= colSize) {
            return false;
        }

        if (map[next.first][next.second] == '#') {
            updateDirection(direction);
        }
        else {
            if (directionMap[next.first][next.second].test(direction)) {
                return true;
            }
            current = next;
            directionMap[current.first][current.second].set(direction);
        }
    }
    return false;
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1 ^ (h2 << 1);
    }
};

int solve(const vector<vector<char>>& map, const pair<int, int>& start, 
         const unordered_map<int, vector<int>>& rowObstacles, 
         const unordered_map<int, vector<int>>& colObstacles) {
    int direction = 0;
    const int rowSize = map.size();
    const int colSize = map[0].size();
    auto current = start;
    vector<int> threadResults;
    mutex resultsMutex;

    unordered_set<pair<int, int>, pair_hash> placedObstacles;
    
    const unsigned int threadCount = thread::hardware_concurrency();
    ThreadPool pool(threadCount);
    vector<future<void>> futures;

    mutex placedObstaclesMutex;

    vector<pair<pair<int, int>, int>> tasksToProcess;
    
    while (true) {
        auto next = getNext(current, direction);
        if (next.first < 0 || next.first >= rowSize || next.second < 0 || next.second >= colSize) {
            break;
        }
        
        if (map[next.first][next.second] == '.') {
            bool shouldProcess = false;
            {
                lock_guard<mutex> lock(placedObstaclesMutex);
                if (placedObstacles.find(next) == placedObstacles.end()) {
                    placedObstacles.insert(next);
                    shouldProcess = true;
                }
            }

            if (shouldProcess) {
                tasksToProcess.push_back({current, direction});
            }
        }
        if (map[next.first][next.second] == '#') {
            updateDirection(direction);
        }
        else {
            current = next;
        }
    }

    for (const auto& task : tasksToProcess) {
        auto [pos, dir] = task;
        auto tempMap = map;
        auto tempDirectionMap = vector<vector<bitset<4>>>(rowSize, vector<bitset<4>>(colSize));
        
        auto currentPos = pos;
        auto currentDir = dir;
        
        auto nextPos = getNext(currentPos, currentDir);
        if (nextPos.first >= 0 && nextPos.first < rowSize && 
            nextPos.second >= 0 && nextPos.second < colSize) {
            tempMap[nextPos.first][nextPos.second] = '#';
        }
        
        futures.push_back(pool.enqueue(
            [&threadResults, &resultsMutex, start=currentPos, tempMap, 
             tempDirectionMap=std::move(tempDirectionMap), dir=currentDir]() mutable {
                if (isMapHaveLoop(start, tempMap, tempDirectionMap, dir)) {
                    lock_guard<mutex> lock(resultsMutex);
                    threadResults.push_back(1);
                }
            }));
    }

    for (auto& f : futures) {
        f.get();
    }

    return threadResults.size();
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");

    vector<vector<char>> map;
    string line;
    unordered_map<int, vector<int>> rowObstacles;
    unordered_map<int, vector<int>> colObstacles;
    pair<int, int> start;
    int i = 0;
    int direction = 0; // 0: up, 1: right, 2: down, 3: left
    while (getline(inputFile, line)) {
        vector<char> row;
        for (int j = 0; j < line.size(); j++) {
            row.push_back(line[j]);
            if (line[j] == '^') {
                start = make_pair(i, j);
            }
            else if (line[j] == '#') {
                rowObstacles[i].push_back(j);
                colObstacles[j].push_back(i);
            }
        }
        map.push_back(row);
        i++;
    }


    int result = solve(map, start, rowObstacles, colObstacles);
    cout << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}