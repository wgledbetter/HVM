# 00 ###########################################################################
add_executable(00-JustBuild 00-JustBuild.c)
target_link_libraries(00-JustBuild PUBLIC hvm-c)

# 01 ###########################################################################
add_executable(01-DemoMain 01-DemoMain.c)
target_link_libraries(01-DemoMain PUBLIC hvm-c)
