#ifndef VISUALIZETASKMANAGER_H
#define VISUALIZETASKMANAGER_H

#include "imgui.h"
#include "HospitalTaskManager.h"
#include "error_handler.h"
#include "patient.h"

class VisualizeTaskManager
{
public:
    void visualize(HospitalTaskManager& manager, error_handler* error_handler)
    {
        // Set global font scale

        // Set a larger window size
        ImGui::Begin("Hospital Task Manager");

        // Get the available content region size
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();

        if (ImGui::BeginPopup("Add Patient"))
        {
            // Input controls for adding a task
            static int taskPriority = 0;
            static char Name[128] = "";
            static int Age = 0;
            static char Description[128] = "";
            static int genderIndex = 0;
            const char* genderItems[] = {"Male", "Female"};

            ImGui::InputText("Name", Name, IM_ARRAYSIZE(Name));
            ImGui::InputInt("Age", &Age);
            ImGui::Combo("Gender", &genderIndex, genderItems, IM_ARRAYSIZE(genderItems));
            ImGui::InputText("Description", Description, IM_ARRAYSIZE(Description));
            ImGui::InputInt("Priority", &taskPriority);

            if (ImGui::Button("Insert"))
            {
                Patient* newPatient = new Patient(Description, Age, genderItems[genderIndex]);
                int s = manager.countTasks();
                manager.addTask(Name, taskPriority, newPatient);
                ImGui::CloseCurrentPopup();
                if (manager.countTasks() > s) // Only reset the fields if the task was added
                {                             // Otherwise, the user may want to try again
                    Name[0] = '\0';
                    Age = 0;
                    genderIndex = 0;
                    Description[0] = '\0';
                    taskPriority = 0;
                }

            }

            ImGui::EndPopup();
        }
        // Button to add a task
        if (ImGui::Button("Insert Patient"))
        {
            ImGui::OpenPopup("Add Patient");
        }

        ImGui::SameLine();

        // Button to complete the highest priority task
        if (ImGui::Button("Complete Highest Priority Task"))
        {
            if (manager.countTasks() != 0)
                manager.completeHighestPriorityTask();
            else
                error_handler->e_log(03);
        }

        ImGui::Separator();

        // Input controls for updating a task's priority
        static int oldPriority = 0;
        static int newPriority = 0;
        ImGui::InputInt("Old Priority", &oldPriority);
        ImGui::InputInt("New Priority", &newPriority);

        // Button to update a task's priority
        if (ImGui::Button("Update Task Priority"))
        {
            // 50% width, 70px height
            manager.updateTaskPriority(oldPriority, newPriority);
        }

        ImGui::Separator();

        static int displayPriority = 0;
        ImGui::InputInt("Priority", &displayPriority);


        if (ImGui::BeginPopup("Display Patient"))
        {
            Node<std::string>* curr = manager.getTaskCopy(displayPriority);
            ImGui::Text("Name: %s", curr->getName().c_str());
            ImGui::Text("Priority: %d", curr->getKey());
            if (curr->getData() != nullptr)
            {
                ImGui::Text("Description: %s", curr->getData()->getDescription().c_str());
                ImGui::Text("Age: %d", curr->getData()->getAge());
                ImGui::Text("Gender: %s", curr->getData()->getGender().c_str());
            }
            ImGui::EndPopup();
        }
        static bool initialized = false;
        if (ImGui::BeginPopup("Edit Patient"))
        {
            Node<std::string>* curr = manager.taskHeap->find(displayPriority);
            static int taskPriority;
            static char Name[128];
            static int Age;
            static char Description[128];
            static int genderIndex;
            const char* genderItems[] = {"Male", "Female"};

            if (!initialized && curr != nullptr)
            {
                taskPriority = curr->getKey();
                strncpy(Name, curr->getName().c_str(), sizeof(Name) - 1);
                Name[sizeof(Name) - 1] = '\0';

                if (curr->getData() != nullptr)
                {
                    Age = curr->getData()->getAge();
                    genderIndex = curr->getData()->getGender() == "Male" ? 0 : 1;
                    strncpy(Description, curr->getData()->getDescription().c_str(), sizeof(Description) - 1);
                    Description[sizeof(Description) - 1] = '\0';
                }
                else
                {
                    Age = 0;
                    genderIndex = 0;
                    Description[0] = '\0';
                }
                initialized = true;
            }

            ImGui::InputText("Name", Name, IM_ARRAYSIZE(Name));
            ImGui::InputInt("Age", &Age);
            ImGui::Combo("Gender", &genderIndex, genderItems, IM_ARRAYSIZE(genderItems));
            ImGui::InputText("Description", Description, IM_ARRAYSIZE(Description));
            ImGui::InputInt("Priority", &taskPriority);

            if (ImGui::Button("Save"))
            {
                if (taskPriority != curr->getKey())
                    manager.updateTaskPriority(displayPriority, taskPriority);
                if (curr->getKey() == taskPriority)
                {
                    if (curr->getData() == nullptr)
                        curr->setData(new Patient(Description, Age, genderItems[genderIndex]));
                    else
                    {
                        curr->getData()->setAge(Age);
                        curr->getData()->setDescription(Description);
                        curr->getData()->setGender(genderItems[genderIndex]);
                    }
                    curr->setName(Name);
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (ImGui::Button("Display Data")){
            if (manager.taskHeap->find(displayPriority) != nullptr)
                ImGui::OpenPopup("Display Patient");
            else
                error_handler->e_log(04);
        }

        ImGui::SameLine();

        if (ImGui::Button("Edit Data")){
            if (manager.taskHeap->find(displayPriority) != nullptr)
            {
                initialized = false; // Reset the flag when the popup is closed
                ImGui::OpenPopup("Edit Patient");
            }
            else
                error_handler->e_log(04);
        }

        ImGui::SameLine();

        if (ImGui::Button("Display Minimum")){
            if (manager.taskHeap->displayMinimum() != nullptr){
                displayPriority = manager.taskHeap->displayMinimum()->getKey();
                ImGui::OpenPopup("Display Patient");
            }
            else
                error_handler->e_log(03);
        }
        ImGui::Separator();

        error_handler->renderErrorMessages();

        ImGui::Separator();

        // Display the number of tasks
        ImGui::Text("Number of Tasks: %d", manager.countTasks());

        displayTasks(manager);


        ImGui::End();
    }

private:
    void displayTasks(HospitalTaskManager& manager)
    {
        if (ImGui::BeginTable("TasksTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            // Set up the headers
            ImGui::TableSetupColumn("Task Name");
            ImGui::TableSetupColumn("Priority");
            ImGui::TableHeadersRow();

            // Display each task in the table
            traverseHeap(manager.taskHeap->displayMinimum());

            ImGui::EndTable();
        }
    }

    void traverseHeap(Node<std::string>* node)
    {
        if (!node) return;

        Node<std::string>* start = node;
        do
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", node->getName().c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", node->getKey());

            if (node->child)
            {
                traverseHeap(node->child->head);
            }
            node = node->right;
        }
        while (node != start);
    }
};

#endif
