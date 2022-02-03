echo ------------------------------------
echo Setting up...
echo Updating repos
sudo apt-get update

echo ------------------------------------
echo Installing Compiler and Toolchain...
sudo apt install build-essential
sudo apt-get install manpages-dev
sudo apt-get -y install cmake
sudo apt-get -y install git

echo ------------------------------------
echo Installing Required Graphics and Audio libraries...
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

echo ------------------------------------
echo Installing RayLib....
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/

echo ------------------------------------
echo Building RayLib...
make PLATFORM=PLATFORM_DESKTOP
sudo make install

echo ------------------------------------
echo Successfully installed and built dependecies