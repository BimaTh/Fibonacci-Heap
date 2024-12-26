#pragma once

#include "imgui.h"
#include "FibHeap.h"
#include "Node.h"
#include "_env.h"
#include "error_handler.h"

#include <string>
#include <iostream>
#include <cmath>

/**
 * @class ImDrawList
 * @brief Forward declaration of ImDrawList class.
 */
class ImDrawList;

struct ImVec2;

/**
 * @class VisualizeFibonacciHeap
 * @brief Class to visualize a Fibonacci Heap using Dear ImGui.
 */
class VisualizeFibonacciHeap {
private:

    error_handler * handler;

    /**
    * @struct NodePositionPair
    * @brief Structure to store a node and its position.
    */

    typedef struct {
        Node<std::string> *first;
        ImVec2 second;
    } NodePositionPair;

    /**
     * @struct NodeArray
     * @brief Structure to store an array of nodes.
     */

    typedef struct {
        Node<std::string> *nodes[MAX_NODES];
        int count;
    } NodeArray;

    /**
     * @brief Draws a node at the specified position.
     * @param drawList Pointer to the ImDrawList.
     * @param center Position of the node center.
     * @param key Key value of the node.
     * @param isMin Flag indicating if the node is the minimum node.
     * @param isMarked Flag indicating if the node is marked.
     * @param color Color of the node.
     */
    void drawNode(ImDrawList *drawList, ImVec2 center, int key, bool isMin, bool isMarked, ImU32 color) {
        drawList->AddCircleFilled(center, nodeRadius, color);

        // Highlight the minimum node if specified
        if (isMin) {
            drawList->AddCircle(center, nodeRadius + 5.0f, IM_COL32(255, 255, 0, 255), 0, 2.5f);
        }

        // Convert the key to a string and display it
        char keyStr[20];
        snprintf(keyStr, sizeof(keyStr), "%d", key);
        ImVec2 textSize = ImGui::CalcTextSize(keyStr);
        drawList->AddText(ImVec2(center.x - textSize.x * 0.5f, center.y - textSize.y * 0.5f), IM_COL32(0, 0, 0, 255),
                          keyStr);

        // Display a mark if the node is marked
        if (isMarked) {
            drawList->AddText(ImVec2(center.x + nodeRadius * 0.5f, center.y - nodeRadius * 0.5f),
                              IM_COL32(255, 0, 0, 255), "M");
        }
    }

    /**
     * @brief Draws links between a node and its children, and horizontally between the children and root nodes.
     * @param drawList Pointer to the ImDrawList.
     * @param node Pointer to the parent node.
     * @param nodePositions Array of node positions.
     * @param numPositions Number of node positions.
     * @param heap Reference to the Fibonacci Heap.
     */
    void drawLinks(ImDrawList *drawList, Node<std::string> *node, NodePositionPair *nodePositions, int numPositions,
                   const FibHeap<std::string> &heap) {
        if (node == nullptr) return;

        // Find the position of the current node
        ImVec2 parentPos;
        for (int i = 0; i < numPositions; i++) {
            if (nodePositions[i].first == node) {
                parentPos = nodePositions[i].second;
            }
        }

        // Draw links to children if they exist
        if (node->child) {
            NodeArray children = getChildren(node);
            ImVec2 previousChildPos;

            for (int i = 0; i < children.count; i++) {
                Node<std::string> *child = children.nodes[i];
                ImVec2 childPos;
                for (int j = 0; j < numPositions; j++) {
                    if (nodePositions[j].first == child) {
                        childPos = nodePositions[j].second;
                    }
                }

                // Draw vertical link from parent to child
                ImVec2 direction = ImVec2(childPos.x - parentPos.x, childPos.y - parentPos.y);
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                ImVec2 unitDirection = ImVec2(direction.x / length, direction.y / length);

                ImVec2 start = ImVec2(parentPos.x + unitDirection.x * nodeRadius,
                                      parentPos.y + unitDirection.y * nodeRadius);
                ImVec2 end = ImVec2(childPos.x - unitDirection.x * nodeRadius,
                                    childPos.y - unitDirection.y * nodeRadius);

                drawList->AddLine(start, end, IM_COL32(255, 255, 255, 255), 3.0f);

                // Draw horizontal link between siblings
                if (i > 0) {
                    ImVec2 siblingDirection = ImVec2(childPos.x - previousChildPos.x, childPos.y - previousChildPos.y);
                    float siblingLength = sqrt(
                        siblingDirection.x * siblingDirection.x + siblingDirection.y * siblingDirection.y);
                    ImVec2 siblingUnitDirection = ImVec2(siblingDirection.x / siblingLength,
                                                         siblingDirection.y / siblingLength);

                    ImVec2 siblingStart = ImVec2(previousChildPos.x + siblingUnitDirection.x * nodeRadius,
                                                 previousChildPos.y + siblingUnitDirection.y * nodeRadius);
                    ImVec2 siblingEnd = ImVec2(childPos.x - siblingUnitDirection.x * nodeRadius,
                                               childPos.y - siblingUnitDirection.y * nodeRadius);

                    drawList->AddLine(siblingStart, siblingEnd, IM_COL32(0, 255, 0, 255), 3.0f);
                    // Green color for horizontal links
                }

                previousChildPos = childPos;
                drawLinks(drawList, child, nodePositions, numPositions, heap);
            }
        }

        // Draw horizontal links between root nodes
        NodeArray roots = getRoots(heap);
        ImVec2 previousRootPos;
        for (int i = 0; i < roots.count; i++) {
            Node<std::string> *root = roots.nodes[i];
            ImVec2 rootPos;
            for (int j = 0; j < numPositions; j++) {
                if (nodePositions[j].first == root) {
                    rootPos = nodePositions[j].second;
                }
            }

            if (i > 0) {
                ImVec2 rootDirection = ImVec2(rootPos.x - previousRootPos.x, rootPos.y - previousRootPos.y);
                float rootLength = sqrt(rootDirection.x * rootDirection.x + rootDirection.y * rootDirection.y);
                ImVec2 rootUnitDirection = ImVec2(rootDirection.x / rootLength, rootDirection.y / rootLength);

                ImVec2 rootStart = ImVec2(previousRootPos.x + rootUnitDirection.x * nodeRadius,
                                          previousRootPos.y + rootUnitDirection.y * nodeRadius);
                ImVec2 rootEnd = ImVec2(rootPos.x - rootUnitDirection.x * nodeRadius,
                                        rootPos.y - rootUnitDirection.y * nodeRadius);

                drawList->AddLine(rootStart, rootEnd, IM_COL32(0, 0, 255, 255), 3.0f); // Blue color for root links
            }

            previousRootPos = rootPos;
        }
    }

    /**
     * @brief Calculates positions for the nodes.
     * @param node Pointer to the current node.
     * @param nodePositions Array of node positions.
     * @param numPositions Reference to the number of node positions.
     * @param parentPos Position of the parent node.
     * @param canvasWidth Width of the canvas.
     */

    void calculateNodePositions(Node<std::string> *node, NodePositionPair *nodePositions, int &numPositions,
                                ImVec2 parentPos, float canvasWidth) {
        if (node == nullptr || node->child == nullptr) return;

        NodeArray children = getChildren(node);

        float childSpacing = canvasWidth / (4 * (children.count + 1));

        for (size_t i = 0; i < children.count; ++i) {
            if (numPositions < MAX_NODES) {
                ImVec2 childPos = ImVec2(parentPos.x + (i * childSpacing), parentPos.y + 100);
                nodePositions[numPositions++] = {children.nodes[i], childPos};
                calculateNodePositions(children.nodes[i], nodePositions, numPositions, childPos, canvasWidth);
            } else {
                handler->e_log(4, "Maximum number of nodes reached in CalculateNodePositions.");
                return;
            }
        }
    }

    /**
     * @brief Gets the root nodes of the heap.
     * @param heap Reference to the Fibonacci Heap.
     * @return Array of root nodes.
     */
    NodeArray getRoots(const FibHeap<std::string> &heap) {
        NodeArray roots = {{}, 0}; // Initialize NodeArray
        if (heap.min == nullptr) return roots;

        Node<std::string> *current = heap.min;
        do {
            if (roots.count < MAX_NODES) {
                roots.nodes[roots.count++] = current;
                current = current->right;
            } else {
                handler->e_log(4,"Maximum number of nodes reached in getRoots." );
                break;
            }
        } while (current != heap.min);
        return roots;
    }

    /**
     * @brief Gets the children of a node.
     * @param node Pointer to the parent node.
     * @return Array of child nodes.
     */
    NodeArray getChildren(Node<std::string> *node) {
        NodeArray children = {{}, 0}; // Initialize NodeArray
        if (node == nullptr || node->child == nullptr || node->child->head == nullptr) return children;

        Node<std::string> *current = node->child->head;
        do {
            if (children.count < MAX_NODES) {
                children.nodes[children.count++] = current;
                current = current->right;
            } else {
                handler->e_log(4, "Maximum number of nodes reached in getChildren.");
                break;
            }
        } while (current != node->child->head);
        return children;
    }

public:
    /**
     * @brief Default constructor.
     */
    VisualizeFibonacciHeap(error_handler * handler): handler(handler) {};

    /**
     * @brief Visualizes the Fibonacci Heap.
     * @param heap Reference to the Fibonacci Heap.
     */
    void visualize(FibHeap<std::string> &heap) {
        ImGui::Begin("Fibonacci Heap Visualization");

        // --- Control Panel ---
        ImGui::Text("Controls");

        ImGui::Checkbox("Development", &FLAG_DEV);

        if (FLAG_DEV) {
            ImGui::Text("Feature is enabled");
        } else {
            ImGui::Text("Feature is disabled");
        }

        ImGui::Separator();

        if (FLAG_DEV) {
            // Input controls for inserting a node
            static int insertValue = 0;
            static char insertName[128] = "";
            ImGui::InputText("Name", insertName, IM_ARRAYSIZE(insertName));
            ImGui::InputInt("Key", &insertValue);

            // Button to trigger insertion
            // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
            if (ImGui::Button("Insert")) {
                if (insertValue >= 0 && heap.find(insertValue) == nullptr) {
                    std::string nameStr(insertName);
                    Node<std::string> *node = new Node<std::string>(nameStr, insertValue);
                    heap.insert(node);
                }
                else
                {
                    if (insertValue < 0) {
                        handler->e_log(10);
                    }
                    if (heap.find(insertValue) != nullptr) {
                        handler->e_log(11);
                    }
                }
            }
            // ImGui::PopStyleVar();

            ImGui::SameLine();
            // Button to extract the minimum node
            // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
            if (ImGui::Button("Extract-Min")) {
                heap.extractMin();
            }
            // ImGui::PopStyleVar();

            ImGui::Separator();

            // Input controls for modifying a key
            static int modifyKey = 0;
            static int newValue = 0;
            ImGui::InputInt("Key to Modify", &modifyKey);
            ImGui::InputInt("New Key Value", &newValue);

            // Button to trigger key modification
            // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
            if (ImGui::Button("Modify Key")) {
                if (newValue >= 0)
                    heap.modifyKey(modifyKey, newValue);
                else
                    handler->e_log(10);

            }
            // ImGui::PopStyleVar();

            ImGui::Separator();

            // Input control for deleting a node
            static int deleteKey = 0;
            ImGui::InputInt("Delete Key", &deleteKey);

            // Button to trigger deletion
            // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 15)); // Increase button size
            if (ImGui::Button("Delete")) {
                heap.deleteNode(deleteKey);
            }
            // ImGui::PopStyleVar();

            ImGui::Separator();
        }

        // --- Visualization Area ---
        ImGui::Text("Fibonacci Heap");

        // Get ImGui's draw list
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        ImVec2 canvasPos = ImGui::GetCursorScreenPos(); // Top-left of the drawing area
        ImVec2 canvasSize = ImGui::GetContentRegionAvail();

        // Get the roots of the heap
        NodeArray roots = getRoots(heap);
        // Initialize an array to store node positions
        NodePositionPair nodePositions[MAX_NODES];
        int numPositions = 0;

        // Calculate positions for the root nodes
        float rootSpacing = canvasSize.x / (roots.count + 1);
        for (size_t i = 0; i < roots.count; ++i) {
            ImVec2 rootPos = ImVec2(canvasPos.x + rootSpacing * (i + 1), canvasPos.y + 50);
            // Adjust vertical position as needed
            nodePositions[numPositions++] = {roots.nodes[i], rootPos};

            // Recursively calculate positions of children
            calculateNodePositions(roots.nodes[i], nodePositions, numPositions, rootPos, canvasSize.x);
        }

        // Draw the nodes
        for (int i = 0; i < numPositions; i++) {
            Node<std::string> *node = nodePositions[i].first;
            ImVec2 position = nodePositions[i].second;

            drawNode(drawList, position, node->getKey(), node == heap.min, node->mark, IM_COL32(51, 255, 255, 255));
        }

        // Draw links between nodes
        if (roots.count > 0) {
            for (int i = 0; i < roots.count; i++) {
                drawLinks(drawList, roots.nodes[i], nodePositions, numPositions, heap);
            }
        }

        ImGui::End();
    }
};
