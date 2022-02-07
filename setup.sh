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
echo Installing RayLib
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

git clone https://github.com/raysan5/raylib.git BALLS/raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP 
sudo make install

echo ------------------------------------
echo Installing Python 2.7 and libraries....
sudo apt-get install python2.7-dev
sudo apt install python2-pip
python -m pip install -U matplotlib
python -m pip install -U numpy

echo make matplotlibcpp

echo ------------------------------------
echo BALLS: Successfully installed and built dependecies