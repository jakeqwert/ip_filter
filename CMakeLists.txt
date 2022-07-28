cmake_minimum_required(VERSION 3.5)
project(ip_filter CXX)



#+++googletest
#add_definitions("-std=c++11")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#find_package(GTest REQUIRED)
#---googletest
find_package (Threads REQUIRED)

add_executable(${PROJECT_NAME} src/ip_filter.cpp src/main.cpp)
add_executable(${PROJECT_NAME}_tests tests/ip_filter_tests.cpp src/ip_filter.cpp)

#+++googletest
# #Use the global target
#target_link_libraries(${PROJECT_NAME}_tests gtest::gtest)
target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})
#---googletest



#target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})




set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror"
        )

#set_target_properties(filter_tests PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#        INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
#        )

#target_link_libraries(filter_tests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


# set warning flags for popular compilers
#function(set_warning_flags target)
#    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#        target_compile_options(${target} PRIVATE "-Wall" "-Wextra" "-pedantic-errors")
#    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#        target_compile_options(${target} PRIVATE "/W4")
#    endif()
#endfunction()
#set_warning_flags(ip_filter)
#set_warning_flags(filter_tests)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

enable_testing()
add_test(test bin/${PROJECT_NAME}_tests)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
if (ENV{TRAVIS_BUILD_NUMBER})
    set(CPACK_PACKAGE_VERSION_PATCH "$ENV{TRAVIS_BUILD_NUMBER}")
else()
    set(CPACK_PACKAGE_VERSION_PATCH "3")
endif()


set(CPACK_PACKAGE_CONTACT eliseevz@mail.ru)

include(CPack)
