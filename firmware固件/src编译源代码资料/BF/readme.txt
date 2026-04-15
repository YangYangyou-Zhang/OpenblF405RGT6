# Update package list and upgrade system
sudo apt update && sudo apt upgrade

# Install basic compilation tools
# You need to install git (for cloning code), make (for building), clang (required for some tests), python, etc.
sudo apt -y install build-essential git curl clang-18 python3 python-is-python3

# Clone Betaflight source code
git clone https://github.com/betaflight/betaflight.git

# Enter the source code directory
cd betaflight

# Switch to a stable version (e.g. 4.5.3)
git checkout 4.5.3

# This command will automatically download and install the required toolchain
make arm_sdk_install

# After the first compilation or switching to a new branch, run this command to generate the default configuration for all target boards.
make configs

# Place the OpenblF405RGT6 folder into the ~/betaflight/src/config/configs directory, and then compile the OpenblF405RGT6 firmware
make config OpenblF405RGT6

# Find the compiled firmware betaflight_4.5.3_STM32F405_OpenblF405RGT6.hex in ~/betaflight/obj
