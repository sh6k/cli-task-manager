#include "TaskManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

TaskManager::TaskManager() : head(nullptr), nextId(1) {}

TaskManager::~TaskManager() {
    Task* current = head;
    while (current) {
        Task* next = current->next;
        delete current;
        current = next;
    }
}

void TaskManager::addTask(string desc, int priority) {
    Task* newNode = new Task(nextId++, desc, priority);
    if (!head) {
        head = newNode;
    }
    else {
        Task* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    cout << "Task added with ID: " << newNode->id << endl;
}

void TaskManager::viewTasks() {
    if (!head) {
        cout << "\nNo tasks found.\n";
        return;
    }
    cout << "\n" << setw(5) << "ID" << setw(20) << "Description" << setw(10) << "Pri" << setw(10) << "Status" << endl;
    cout << string(45, '-') << endl;
    Task* temp = head;
    while (temp) {
        cout << setw(5) << temp->id
            << setw(20) << (temp->description.length() > 17 ? temp->description.substr(0, 14) + "..." : temp->description)
            << setw(10) << temp->priority
            << setw(10) << (temp->isCompleted ? "[DONE]" : "[ ]") << endl;
        temp = temp->next;
    }
}

void TaskManager::markDone(int id) {
    Task* temp = head;
    while (temp) {
        if (temp->id == id) {
            temp->isCompleted = true;
            cout << "Task " << id << " marked as completed.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Task ID not found.\n";
}

void TaskManager::deleteTask(int id) {
    if (!head) return;
    if (head->id == id) {
        Task* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Task deleted.\n";
        return;
    }
    Task* temp = head;
    while (temp->next && temp->next->id != id) temp = temp->next;
    if (temp->next) {
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task deleted.\n";
    }
    else {
        cout << "ID not found.\n";
    }
}


Task* TaskManager::merge(Task* a, Task* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->priority <= b->priority) {
        a->next = merge(a->next, b);
        return a;
    }
    else {
        b->next = merge(a, b->next);
        return b;
    }
}

Task* TaskManager::split(Task* source) {
    Task* fast = source->next;
    Task* slow = source;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Task* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Task* TaskManager::mergeSort(Task* node) {
    if (!node || !node->next) return node;
    Task* second = split(node);
    return merge(mergeSort(node), mergeSort(second));
}

void TaskManager::sortTasks() {
    head = mergeSort(head);
    cout << "Tasks sorted by priority!\n";
}

void TaskManager::saveToFile() {
    ofstream out("tasks.txt");
    Task* temp = head;
    while (temp) {
        out << temp->id << "|" << temp->description << "|" << temp->priority << "|" << temp->isCompleted << "\n";
        temp = temp->next;
    }
    out.close();
}

void TaskManager::loadFromFile() {
    ifstream in("tasks.txt");
    if (!in) return;
    string line;
    int maxId = 0;
    while (getline(in, line)) {
        stringstream ss(line);
        string idS, desc, priS, statS;
        getline(ss, idS, '|'); getline(ss, desc, '|'); getline(ss, priS, '|'); getline(ss, statS, '|');

        int id = stoi(idS);
        Task* newNode = new Task(id, desc, stoi(priS), statS == "1");
        if (id > maxId) maxId = id;

        if (!head) head = newNode;
        else {
            Task* t = head;
            while (t->next) t = t->next;
            t->next = newNode;
        }
    }
    nextId = maxId + 1;
}