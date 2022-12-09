# ycraft
my top down sandbox game

## compile
```
$ make
```

a binary will be placed in the `bin` folder
if compilation fails because of undefined `SDL_RenderGeometry` then compile again but do:
```
$ make triangles=off
```

## compile psvita
```
mkdir vita
cd vita
cmake ..
make
```
and you will get a file called `ycraft-vita.vpk`, move it to `ux0:VPK/` with vitashell FTP, and run it from vitashell.

## dependencies
SDL2, SDL2_ttf, SDL2_image, SDL2_mixer, libcurl

vitasdk for the vita build

### sdl2 autobuild (manual)
run `sdlautoinstall.sh` inside the repo

basically use this if you get issues about traingle rendering, means that your apt-get / package manager sdl version is a couple years old lmfao

### deps for ubuntu based systems
**i really reccomend the manual build above!! this will most likely have issues**

```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libcurl4-openssl-dev
```

## controls
WASD - move player

left click - delete block

right click - place block

t - open chat

e - open/close inventory

## screenshots
<img src="/img/screenshot.png">
