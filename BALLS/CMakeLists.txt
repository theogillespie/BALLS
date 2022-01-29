# CMakeList.txt : CMake project for BALLS, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BALLS "BALLS.cpp" "BALLS.h" "core/Vector3.h" "core/effects/Gravity.h" "core/Effects.h")

# TODO: Add tests and install targets if needed.
