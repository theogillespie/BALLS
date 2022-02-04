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
echo Installing GLFW
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev

echo ------------------------------------
echo Installing Debug-Draw...
git clone https://github.com/glampert/debug-draw.git BALLS/draw

echo ------------------------------------
echo Installing Python 2.7 and libraries....
sudo apt-get install python2.7-dev
sudo apt install python2-pip
python -m pip install -U matplotlib
python -m pip install -U numpy

echo make matplotlibcpp

echo ------------------------------------
echo BALLS: Successfully installed and built dependecies