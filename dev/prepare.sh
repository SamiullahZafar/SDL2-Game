#!/bin/bash

echo "Setup the required libraries for the labs"
PREFIX=$PWD/install

wget https://www.libsdl.org/release/SDL2-2.0.10.tar.gz
tar -xf SDL*gz
cd SDL2-2.0.10
./configure --prefix=$PREFIX
make -j4
make -j4 install
cd ..

wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
tar -xf SDL2_mixer-2.0.4.tar.gz
cd SDL2_mixer-2.0.4
./configure --with-sdl-prefix=$PREFIX --prefix=$PREFIX
make -j4
make -j4 install
cd ..

wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
tar -xf SDL2_image-2.0.5.tar.gz
cd SDL2_image-2.0.5
./configure --with-sdl-prefix=$PREFIX --prefix=$PREFIX
make -j4
make -j4 install
cd ..
