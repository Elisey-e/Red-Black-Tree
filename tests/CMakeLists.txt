add_executable(test_function ./src/test_function.cpp)


target_include_directories(test_function
                           PRIVATE ${INCLUDE_DIR})


# install(TARGETS test_function
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#         COMPONENT test_function)



install(TARGETS test_function
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})