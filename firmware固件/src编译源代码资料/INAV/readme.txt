# Clone iNav source code
git clone https://github.com/iNavFlight/inav.git
cd inav

# Create a build directory and initialize CMake
mkdir build && cd build
cmake

# Move the OpenblF405RGT6 folder to the directory ~/inav/src/main/target/.
# Compile firmware
cd ~/inav

# 1.  Create a build directory
mkdir -p build

# 2.  Run CMake configuration
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm-none-eabi.cmake

# 3.  Compile your target (-j4 to compile with 4 CPU threads)
cmake --build build --target OpenblF405RGT6 -j4

# Check firmware
# Typically located in the ~/inav/build directory
