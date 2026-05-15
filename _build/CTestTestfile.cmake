# CMake generated Testfile for 
# Source directory: /root/barsik20/workspace/projects/lab05h
# Build directory: /root/barsik20/workspace/projects/lab05h/_build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(check_print "/root/barsik20/workspace/projects/lab05h/_build/check_print")
set_tests_properties(check_print PROPERTIES  _BACKTRACE_TRIPLES "/root/barsik20/workspace/projects/lab05h/CMakeLists.txt;28;add_test;/root/barsik20/workspace/projects/lab05h/CMakeLists.txt;0;")
add_test(check_banking "/root/barsik20/workspace/projects/lab05h/_build/check_banking")
set_tests_properties(check_banking PROPERTIES  _BACKTRACE_TRIPLES "/root/barsik20/workspace/projects/lab05h/CMakeLists.txt;38;add_test;/root/barsik20/workspace/projects/lab05h/CMakeLists.txt;0;")
subdirs("formatter_lib")
subdirs("formatter_ex_lib")
subdirs("solver_lib")
subdirs("hello_world_app")
subdirs("solver_app")
subdirs("banking")
subdirs("third-party/gtest")
