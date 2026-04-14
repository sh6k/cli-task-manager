#include "TaskManager.h"
#include <iostream>

using namespace std;

int main() {
    TaskManager tm;
    tm.loadFromFile();
    int choice;

    do {
        cout << "\n--- ADVANCED TASK MANAGER ---\n";
        cout << "1. Add   2. View   3. Sort   4. Done   5. Delete   6. Exit\n";
        cout << "Selection: ";
        if (!(cin >> choice)) break;
        cin.ignore();

        if (choice == 1) {
            string d; int p;
            cout << "Description: "; getline(cin, d);
            cout << "Priority (1-High, 5-Low): "; cin >> p;
            tm.addTask(d, p);
        }
        else if (choice == 2) tm.viewTasks();
        else if (choice == 3) tm.sortTasks();
        else if (choice == 4) {
            int id; cout << "Enter ID: "; cin >> id;
            tm.markDone(id);
        }
        else if (choice == 5) {
            int id; cout << "Enter ID: "; cin >> id;
            tm.deleteTask(id);
        }
    } while (choice != 6);

    tm.saveToFile();
    return 0;
}
