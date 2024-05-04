#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    int id;
    string description;
    bool completed;

    Task(int id, string description) : id(id), description(description), completed(false) {}
};

class ToDoListManager {
private:
    vector<Task> tasks;
    int nextId = 1;

public:
    // Add a new task
    void addTask(string description) {
        tasks.push_back(Task(nextId++, description));
        cout << "Task added successfully with ID: " << tasks.back().id << endl;
    }

    // View all tasks
    void listTasks() {
        if (tasks.empty()) {
            cout << "No tasks found." << endl;
        } else {
            cout << "Tasks:" << endl;
            for (const Task& task : tasks) {
                cout << task.id << ". " << (task.completed ? "[X] " : "[ ] ") << task.description << endl;
            }
        }
    }

    // Mark a task as completed
    bool markCompleted(int taskId) {
        for (Task& task : tasks) {
            if (task.id == taskId) {
                task.completed = true;
                cout << "Task " << taskId << " marked as completed." << endl;
                return true;
            }
        }
        cout << "Task ID not found." << endl;
        return false;
    }

    // Delete a task
    bool deleteTask(int taskId) {
        auto it = find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.id == taskId; });
        if (it != tasks.end()) {
            tasks.erase(it);
            cout << "Task " << taskId << " deleted successfully." << endl;
            return true;
        } else {
            cout << "Task ID not found." << endl;
            return false;
        }
    }
};

int main() {
    ToDoListManager manager;

    int choice;
    string description;
    int taskId;

    while (true) {
        cout << "\nTo-Do List Manager:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task Completed" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore(); // Clear input buffer
                getline(cin, description);
                manager.addTask(description);
                break;
            case 2:
                manager.listTasks();
                break;
            case 3:
                cout << "Enter task ID to mark completed: ";
                cin >> taskId;
                manager.markCompleted(taskId);
                break;
            case 4:
                cout << "Enter task ID to delete: ";
                cin >> taskId;
                manager.deleteTask(taskId);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
