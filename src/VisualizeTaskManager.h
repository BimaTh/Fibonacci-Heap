#ifndef VISUALIZETASKMANAGER_H
#define VISUALIZETASKMANAGER_H

#include "imgui.h"
#include "HospitalTaskManager.h"

class VisualizeTaskManager {
public:
    void visualize(HospitalTaskManager &manager) {
        // Set global font scale
        ImGui::GetIO().FontGlobalScale = 4.0f; // Increase font size globally

        // Set a larger window size
        ImGui::SetNextWindowSize(ImVec2(1280, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Hospital Task Manager");

        // Get the available content region size
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();

        // Input controls for adding a task
        static int taskPriority = 0;
        static char taskDescription[128] = "";

        // ImGui::PushItemWidth(contentRegion.x * 0.7f); // 70% of the content region width
        ImGui::InputText("Description", taskDescription, IM_ARRAYSIZE(taskDescription));
        // ImGui::PopItemWidth();
        // ImGui::PushItemWidth(contentRegion.x * 0.3f); // 30% of the content region width
        ImGui::InputInt("Priority", &taskPriority);
        // ImGui::PopItemWidth();

        // Button to add a task
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20)); // Increase button size
        if (ImGui::Button("Add Task", ImVec2(contentRegion.x * 0.5f, 90))) {
            // 40% width, 70px height
            std::string descriptionStr(taskDescription);
            manager.addTask(descriptionStr, taskPriority);
        }
        ImGui::PopStyleVar();

        ImGui::SameLine();
        // Button to complete the highest priority task
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20)); // Increase button size
        if (ImGui::Button("Complete Highest Priority Task", ImVec2(contentRegion.x * 0.5f, 90))) {
            // 50% width, 90px height
            manager.completeHighestPriorityTask();
        }
        ImGui::PopStyleVar();

        ImGui::Separator();

        // Input controls for updating a task's priority
        static int oldPriority = 0;
        static int newPriority = 0;
        ImGui::PushItemWidth(contentRegion.x * 0.3f); // 30% of the content region width
        ImGui::InputInt("Old Priority", &oldPriority);
        ImGui::PopItemWidth();
        ImGui::PushItemWidth(contentRegion.x * 0.3f); // 30% of the content region width
        ImGui::InputInt("New Priority", &newPriority);
        ImGui::PopItemWidth();

        // Button to update a task's priority
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
        if (ImGui::Button("Update Task Priority", ImVec2(contentRegion.x * 0.5f, 90))) {
            // 50% width, 90px height
            manager.updateTaskPriority(oldPriority, newPriority);
        }
        ImGui::PopStyleVar();

        ImGui::Separator();

        // Display the number of tasks
        ImGui::Text("Number of Tasks: %d", manager.countTasks());

        // Button to display all tasks
        static bool showTasks = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
        if (ImGui::Button("Display Tasks", ImVec2(contentRegion.x * 0.5f, 90))) {
            // 50% width, 90px height
            showTasks = !showTasks;
        }
        ImGui::PopStyleVar();

        // Conditionally display the tasks table
        if (showTasks) {
            displayTasks(manager);
        }

        ImGui::End();
    }

private:
    void displayTasks(HospitalTaskManager &manager) {
        if (ImGui::BeginTable("TasksTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            // Set up the headers
            ImGui::TableSetupColumn("Task Name");
            ImGui::TableSetupColumn("Priority");
            ImGui::TableHeadersRow();

            // Display each task in the table
            traverseHeap(manager.taskHeap->displayMinimum());

            ImGui::EndTable();
        }
    }

    void traverseHeap(Node<std::string> *node) {
        if (!node) return;

        Node<std::string> *start = node;
        do {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", node->getName().c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", node->getKey());

            if (node->child) {
                traverseHeap(node->child->head);
            }
            node = node->right;
        } while (node != start);
    }
};

#endif
