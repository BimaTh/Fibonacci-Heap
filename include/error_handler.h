#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <array>
#include <chrono>
#include <vector>

class error_handler {
private:

    struct TimedMessage {
        std::string message;
        std::chrono::steady_clock::time_point endTime;
    };

    std::vector<TimedMessage> activeMessages;

    std::array<std::string, 5> const errorClass = {
        "Hospital Task Manager: ", // ID: 0
        "Fibonacci Heap: ", // ID: 1
        "Doubly Circular Linked List: ", // ID: 2
        "VisualizeFibonacciHeap: ", // ID: 3
        "VisualizeTaskManager: " // ID: 4
    };
    std::array<std::string, 30> const errorMessages = {
        "Priority must be a positive integer.\n", // ID: 0
        "Task with the same priority already exists.\n", // ID: 1
        "Description cannot be empty or more than 50 characters.\n", // ID: 2
        "No tasks in the queue.\n", // ID: 3
        "Task not found.\n", // ID: 4
        "New priority is the same as the old priority.\n", // ID: 5
        "Task with new priority already exists.\n", // ID: 6
        "Node not Found.\n", // ID: 7
        "Heap Tree Empty.\n", // ID: 8
    };

    void addErrorMessage(const std::string& message, int durationMS);

public:

    void renderErrorMessages();
    void e_log(int id);
    void e_log(int id, std::string message);
    void verbose_log( int classID, std::string msg) const;


};



#endif
