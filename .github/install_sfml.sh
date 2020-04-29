#!/bin/sh
sudo apt-get install freeglut3-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libxrandr-dev

git clone https://github.com/SFML/SFML.git
mkdir -p SFML/build
cd SFML/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2 || make
sudo make install

sudo cp /usr/local/lib/libsfml-* /usr/lib
