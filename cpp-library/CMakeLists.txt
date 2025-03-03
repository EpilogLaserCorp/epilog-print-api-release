cmake_minimum_required(VERSION 3.5)

project(epilog-print-api-example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z noexecstack")
endif()

add_executable(
    epilog-print-api-example
    example/main.cpp
    example/epilogprintfilegenerator.h
    example/epilogprintfilegenerator.cpp
    epilog-print-api.h
)

include(GNUInstallDirs)

install(
    TARGETS epilog-print-api-example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/example)

if(UNIX AND NOT APPLE)
    if(CMAKE_VERSION VERSION_LESS "3.21.0")
        file(
            COPY
            ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu-20.04/libepilog_print_api_libcpp.so
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        )
    else()
        file(
            COPY_FILE
            ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu-20.04/libepilog_print_api_libcpp.so
            ${CMAKE_CURRENT_BINARY_DIR}/libepilog_print_api_libcpp.so ONLY_IF_DIFFERENT
        )
    endif()

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu-20.04/libepilog_print_api_libcpp.so
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    target_link_libraries(
        epilog-print-api-example
        ${CMAKE_CURRENT_BINARY_DIR}/libepilog_print_api_libcpp.so
    )
elseif(WIN32)
    if(CMAKE_VERSION VERSION_LESS "3.21.0")
        file(
            COPY_FILE
            ${CMAKE_CURRENT_SOURCE_DIR}/win-x64/epilog_print_api_libcpp.dll
            ${CMAKE_CURRENT_BINARY_DIR}/epilog_print_api_libcpp.dll ONLY_IF_DIFFERENT
        )
    else()
        file(
            COPY_FILE
            ${CMAKE_CURRENT_SOURCE_DIR}/win-x64/epilog_print_api_libcpp.dll
            ${CMAKE_CURRENT_BINARY_DIR}/epilog_print_api_libcpp.dll ONLY_IF_DIFFERENT
        )
    endif()

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/win-x64/epilog_print_api_libcpp.dll
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    target_link_libraries(
        epilog-print-api-example
        ${CMAKE_CURRENT_SOURCE_DIR}/win-x64/epilog_print_api_libcpp.dll.lib
    )
endif()
