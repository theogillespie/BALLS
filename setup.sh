echo Setting up...
echo Updating repos
sudo apt-get update

echo Installing Compiler and Toolchain...
sudo apt install build-essential
sudo apt-get install manpages-dev
sudo apt-get -y install cmake
sudo apt-get -y install git

echo ------------------------------------
echo Successfully installed dependecies