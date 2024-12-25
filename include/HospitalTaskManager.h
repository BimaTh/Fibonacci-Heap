#ifndef HOSPITALTASKMANAGER_H
#define HOSPITALTASKMANAGER_H

#include "FibHeap.h"
#include "Node.h"
#include"../src/_env.h"

#include <iostream>
#include <string>

#include "error_handler.h"

// Forward Declaration
class VisualizeTaskManager;

class HospitalTaskManager {
private:
    FibHeap<std::string> * taskHeap;
    error_handler * handler;

public:

    HospitalTaskManager(FibHeap<std::string> * taskHeap, error_handler * handler): taskHeap(taskHeap), handler(handler){};

    friend class VisualizeTaskManager;

    ~HospitalTaskManager() {
        while (!taskHeap->isEmpty()) {
            Node<std::string> *task = taskHeap->extractMin();
            delete task;
        }
    }

    void addTask(const std::string &description, int priority) {
        if (priority < 0) {
            handler->e_log(00);
            return;
        }
        if (taskHeap->find(priority) != nullptr) {
            handler->e_log(01);
            return;
        }
        if (description.empty() || description.length() > 50 || taskHeap->getSize() >= MAX_TASKS) {
            handler->e_log(02);
            return;
        }
        Node<std::string> *newNode = new Node<std::string>(description, priority);
        taskHeap->insert(newNode);
        handler->verbose_log(0, "Task added: " + description);
    }

    void completeHighestPriorityTask() {
        Node<std::string> *highestPriorityTask = taskHeap->extractMin();

        if (highestPriorityTask == nullptr) {
            handler->e_log(04);
            return;
        }
        handler->verbose_log(0, "Completed task: " + highestPriorityTask->getName());
        delete highestPriorityTask;
    }

    void updateTaskPriority(int oldPriority, int newPriority) {
        Node<std::string> *taskNode = taskHeap->find(oldPriority);
        if (taskNode == nullptr) {
            handler->e_log(04);
            return;
        }
        if (newPriority < 0) {
            handler->e_log(00);
            return;
        }
        if (oldPriority == newPriority) {
            handler->e_log(05);
            return;
        }
        if (taskHeap->find(newPriority) != nullptr) {
            handler->e_log(06);
            return;
        }
        taskHeap->modifyKey(taskNode->getKey(), newPriority);
        handler->verbose_log(0, "Task priority updated: " + taskNode->getName());
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
