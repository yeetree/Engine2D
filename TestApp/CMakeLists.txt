# Engine2D TestApp

# Create the executable
add_executable(TestApp main.cpp)

# Link the engine library (also includes necessary headers)
target_link_libraries(TestApp PRIVATE Engine2D::Engine2D)

# Copy assets
add_custom_command(TARGET TestApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:TestApp>/Assets"
    COMMENT "Copying assets to build directory..."
)