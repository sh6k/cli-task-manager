#pragma once
#include <string>

struct Task {
    int id;
    std::string description;
    int priority;
    bool isCompleted;
    Task* next;

    Task(int i, std::string d, int p, bool c = false)
        : id(i), description(d), priority(p), isCompleted(c), next(nullptr) {
    }
};

class TaskManager {
private:
    Task* head;
    int nextId;
    Task* split(Task* source);
    Task* merge(Task* first, Task* second);
    Task* mergeSort(Task* headNode);

public:
    TaskManager();
    ~TaskManager();

    void addTask(std::string desc, int priority);
    void viewTasks();
    void deleteTask(int id);
    void markDone(int id);
    void sortTasks();
    void saveToFile();
    void loadFromFile();
};