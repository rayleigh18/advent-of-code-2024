#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node {
    long long value;
    Node* next;
};

Node* applyRulesAndReturnNext(Node* head) {
    Node* next = head->next;
    if (head->value == 0) {
        head->value = 1;
        return next;
    }

    string valueStr = to_string(head->value);
    int totalOfDigits = valueStr.size();
    if (totalOfDigits % 2 == 0) {
        // split into two halves
        int half = totalOfDigits / 2;
        int left = stoi(valueStr.substr(0, half));
        int right = stoi(valueStr.substr(half, totalOfDigits));
        Node* newNode = new Node();
        newNode->value = right;
        newNode->next = next;
        head->next = newNode;
        head->value = left;
    } else {
        head->value = head->value * 2024;
    }

    return next;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

int solve(Node* head, int repetitions) {
    for (int i = 0; i < repetitions; i++) {
        Node* current = head;
        while (current != nullptr) {
            current = applyRulesAndReturnNext(current);
        }
        // printList(head);
    }

    // find length of the list
    int length = 0;
    Node* current = head;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    getline(inputFile, line);
    vector<int> values;
    stringstream ss(line);
    string value;
    while (getline(ss, value, ' ')) {
        values.push_back(stoi(value));
    }

    Node* head = new Node();
    head->value = values[0];
    head->next = nullptr;

    Node* current = head;
    for (int i = 1; i < values.size(); i++) {
        Node* newNode = new Node();
        newNode->value = values[i];
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }

    cout << solve(head, 75) << endl;


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}