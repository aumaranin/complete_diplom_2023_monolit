#!/bin/bash
rm -r build_expert_module
rm -r build_operator_module
rm expert_module/CMakeLists.txt.user
rm operator_module/CMakeLists.txt.user

cmake -S expert_module/ -B build_expert_module
cmake --build build_expert_module
cmake -S operator_module/ -B build_operator_module
cmake --build build_operator_module
