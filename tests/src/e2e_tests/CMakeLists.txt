add_executable(e2e_tests ./src/checker.cpp)
add_executable(generator ./src/generator.cpp)

# target_link_libraries(e2e_tests
#                       PRIVATE ${GTEST_LIBRARIES}
#                       PRIVATE ${CMAKE_THREAD_LIBS_INIT}
#                       PRIVATE m)



target_include_directories(e2e_tests
                           PRIVATE ${INCLUDE_DIR})


target_include_directories(generator
                           PRIVATE ${INCLUDE_DIR})

#gtest_discover_tests(e2e_tests)

install(TARGETS e2e_tests
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS generator
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Подкорректировать