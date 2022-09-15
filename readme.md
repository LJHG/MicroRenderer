# MicroRenderer

✨ A self-built soft Rasterizer, called Micro(soft)Renderer. ✨

## feature
- [x] Triangle Rasterization(line mode and fill mode)
- [x] linear and barycentric interpolation
- [x] Z-buffering
- [x] mvp transformation
- [x] load model
- [x] Gouraud shading phong shading

## dependencies
1. SDL2
2. stb_image
3. glm
4. assimp

> currently only test on macos, building on linux/windows requires extra dynamic libraries for sdl2.
## how to run
```bash
# clone the repo
git clone https://github.com/LJHG/MicroRenderer
# make
cd MicroRenderer
mkdir build
cd build
cmake ..
make
### run ###
# run main.cpp
./MicroRenderer
# run example1
./examples/01_Triangle/01_Triangle
# run example2
./examples/02_mvpTriangle/02_mvpTriangle
# run example3 (need to cd into the folder to run example3, for the relative path setting for the model)
cd examples/03_mary
./03_mary

```

## current stage showcase
<img alt="line rasterization" height="480" src="./images/phong_shading.gif" width="640"/>
<img alt="line rasterization" height="480" src="./images/mary.gif" width="640"/>
<img alt="line rasterization" height="480" src="./images/rock.gif" width="640"/>

