#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Include your Fibonacci Heap headers
#include "FibHeap.h"
#include "HospitalTaskManager.h"
#include "VisualizeFibonacciHeap.h"
#include "VisualizeTaskManager.h"
#include "error_handler.h"
#include <string>

/**
 * @brief Main function to initialize and run the Fibonacci Heap visualization.
 *
 * This function sets up the GLFW window, initializes Dear ImGui, and runs the main loop
 * to visualize the Fibonacci Heap using Dear ImGui.
 *
 * @return int Returns 0 on successful execution, 1 on failure.
 */
int main(int, char **) {
    // Setup GLFW window
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Fibonacci Heap Visualization", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync ensures smooth transition from one frame to the next

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Create am instance of the Error Handler Class,
    error_handler handler;

    // Create an instance of your Fibonacci Heap (using std::string for the Name)
    FibHeap<std::string> myHeap(&handler);

    // Create an instance of the visualization class
    VisualizeFibonacciHeap visualizer;

    // Create an instance of the HospitalTaskManager
    HospitalTaskManager taskManager(&myHeap, &handler);

    // Create an instance of the HospitalTaskManager
    VisualizeTaskManager manager;


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call your visualization function
        visualizer.visualize(myHeap);
        manager.visualize(taskManager);


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
