#!/bin/sh

# Run this file in the folder in which you would like to install the implant
echo "Cloning remote repository into $PWD"
git clone https://github.com/TrevorPeitzman/linuxImplantFundamentals

echo "Installing dependencies"
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install gcc-multilib