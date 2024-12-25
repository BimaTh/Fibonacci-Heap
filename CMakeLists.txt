cmake_minimum_required(VERSION 3.26)
project(FibonacciHeapGUI)

set(CMAKE_CXX_STANDARD 17)

# --- Include Directories ---
include_directories(include)

# --- Source Files ---
add_executable(FibonacciHeapGUI
        src/main.cpp
        src/VisualizeFibonacciHeap.h
        include/DoublyCircularLinkedList.h
        include/FibHeap.h
        include/Node.h
        include/HospitalTaskManager.h
        src/VisualizeTaskManager.h
        src/_env.h
        src/error_handler.cpp
        src/error_handler.h
)

# --- ImGui ---
add_library(imgui STATIC
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC include/imgui)

# --- GLFW ---
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/GLFW"
)

# --- Link Libraries ---
target_link_libraries(FibonacciHeapGUI
        imgui
        glfw
        opengl32 # Link with OpenGL on Windows
)
