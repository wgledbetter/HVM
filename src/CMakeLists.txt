add_library(hvm-c STATIC hvm.c)
target_include_directories(hvm-c PUBLIC ${PROJECT_SOURCE_DIR}/wgl)
target_link_libraries(hvm-c PUBLIC m)
target_compile_definitions(hvm-c PUBLIC TPC_L2=0) # Threads per CPU
