#ifndef HOSPITALTASKMANAGER_H
#define HOSPITALTASKMANAGER_H

#include "FibHeap.h"
#include "Node.h"
#include <iostream>
#include <string>
const int MAX_TASKS = 100;

class HospitalTaskManager {
private:
    FibHeap<std::string> * taskHeap;

public:
    HospitalTaskManager(FibHeap<std::string> * taskHeap): taskHeap(taskHeap){};

    ~HospitalTaskManager() {
        while (!taskHeap->isEmpty()) {
            Node<std::string> *task = taskHeap->extractMin();
            delete task;
        }
    }

    void addTask(const std::string &description, int priority) {
        if (priority < 0) {
            std::cerr << "Priority must be a positive integer.\n";
            return;
        }
        if (taskHeap->find(priority) != nullptr) {
            std::cerr << "Task with the same priority already exists.\n";
            return;
        }
        if (description.empty() || description.length() > 50) {
            ////////////////////
            std::cerr << "Description cannot be empty or more than 50 characters.\n";
            return;
        }
        if (taskHeap->getSize() >= MAX_TASKS) {
            std::cerr << "Task queue is full.\n";
            return;
        }
        Node<std::string> *newNode = new Node<std::string>(description, priority);
        taskHeap->insert(newNode);
        std::cout << "Task added: " << description << " (Priority: " << priority << ")\n";
    }

    void completeHighestPriorityTask() {
        Node<std::string> *highestPriorityTask = taskHeap->extractMin(); /////////////////

        if (highestPriorityTask == nullptr) {
            std::cerr << "No tasks in the queue.\n";
            return;
        }
        std::cout << "Completed task: " << highestPriorityTask->getName() << " (Priority: " << highestPriorityTask->
                getKey() << ")\n";
        delete highestPriorityTask;
    }

    void updateTaskPriority(int oldPriority, int newPriority) {
        Node<std::string> *taskNode = taskHeap->find(oldPriority);
        if (taskNode == nullptr) {
            std::cerr << "Task not found.\n";
            return;
        }
        if (newPriority < 0) {
            std::cerr << "Priority must be a positive integer.\n";
            return;
        }
        if (oldPriority == newPriority) {
            std::cerr << "New priority is the same as the old priority.\n";
            return;
        }
        if (taskHeap->find(newPriority) != nullptr) {
            std::cerr << "Task with new priority already exists.\n";
            return;
        }
        taskHeap->modifyKey(taskNode->getKey(), newPriority);
        std::cout << "Task priority updated: " << taskNode->getName() << " (Old Priority: " << oldPriority <<
                ", New Priority: " << newPriority << ")\n";
    }

    int countTasks() {
        return taskHeap->getSize();
    }

    void displayTasks() {
        std::cout << "Number of Tasks: " << taskHeap->getSize() << std::endl;
        taskHeap->display();
    }
};

#endif
