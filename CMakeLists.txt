project(CodeCoverage)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)
add_subdirectory(googletest EXCLUDE_FROM_ALL)
include(GoogleTest)
include_directories(googletest/googletest/include)

enable_testing()
add_executable(FunctionTest FunctionTest.cpp)
target_link_libraries(FunctionTest gtest_main ${CMAKE_THREAD_LIBS_INIT})
gtest_discover_tests(FunctionTest FunctionTest)

# ---- Variables ----

# We use variables separate from what CTest uses, because those have
# customization issues
set(
    COVERAGE_TRACE_COMMAND
    lcov -c -q
    -o "${PROJECT_BINARY_DIR}/coverage.info"
    -d "${PROJECT_BINARY_DIR}"
    --include "${PROJECT_SOURCE_DIR}/*"
    CACHE STRING
    "; separated command to generate a trace for the 'coverage' target"
)

set(
    COVERAGE_HTML_COMMAND
    genhtml --legend -f -q
    "${PROJECT_BINARY_DIR}/coverage.info"
    -p "${PROJECT_SOURCE_DIR}"
    -o "${PROJECT_BINARY_DIR}/coverage_html"
    CACHE STRING
    "; separated command to generate an HTML report for the 'coverage' target"
)

# ---- Coverage target ----

add_custom_target(
    coverage
    COMMAND ${COVERAGE_TRACE_COMMAND}
    COMMAND ${COVERAGE_HTML_COMMAND}
    COMMENT "Generating coverage report"
    VERBATIM
)


