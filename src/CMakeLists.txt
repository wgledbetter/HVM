add_library(hvm-c hvm.c)
target_include_directories(hvm-c PUBLIC ${PROJECT_SOURCE_DIR}/wgl)
target_link_libraries(hvm-c PUBLIC m)
