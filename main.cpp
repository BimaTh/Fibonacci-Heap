#include <iostream>
#include "DoublyCircularLinkedList.h"
#include "FibHeap.h"
#include "HospitalTaskManager.h"

int main() {
        HospitalTaskManager manager;

        // Add tasks with priorities from 1 to 100
        for (int i = 1; i <= 20; ++i) {
                manager.addTask("Task", rand() % 101);
        }

        // Complete the highest priority task
        // manager.completeHighestPriorityTask();
        std::cout << "Tasks in the queue: " << manager.countTasks() << std::endl;
        // Update task priority
        manager.updateTaskPriority(24, 104);


        // Complete the highest priority task again
        manager.completeHighestPriorityTask();
        manager.displayTasks();
        // Complete the remaining tasks
        int size = manager.countTasks();
        for (int i = 0; i < size; ++i) {
                manager.completeHighestPriorityTask();
        }
        manager.displayTasks();
        return 0;
}
