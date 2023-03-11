mkdir ~/sdlbuildenv
cd ~/sdlbuildenv

echo ">>>>>>>> Installing SDL2!"
git clone https://github.com/libsdl-org/SDL
cd SDL
mkdir build
cd build
../configure
make -j4
sudo make install
cd ../../
echo ">>>>>>>> Finished SDL2! Enter any character to continue"
read

echo ">>>>>>>> Installing SDL2_image!"
git clone https://github.com/libsdl-org/SDL_image
cd SDL_image
mkdir build
cd build
../configure
make -j4
sudo make install
cd ../../
echo ">>>>>>>> Finished SDL2_image! Enter any character to continue"
read

echo ">>>>>>>> Installing SDL2_mixer!"
git clone https://github.com/libsdl-org/SDL_mixer
cd SDL_mixer
mkdir build
cd build
../configure
make -j4
sudo make install
echo ">>>>>>>>  Finished installing! You can now safely remove the folder ~/sdlbuildenv .!!"
read
