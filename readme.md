# MicroRenderer

A self-built soft Rasterizer, called Micro(soft)Renderer.

## process
- [x] Triangle Rasterization(line mode and fill mode)
- [x] linear and barycentric interpolation
- [x] Z-buffering
- [x] mvp transformation

## bugs
- [ ] crash when set fov to a small value(eg. 6.0f)
- [ ] crash when using OrthoProjectionMatrix

## dependencies
1. SDL2
2. stb_image
3. glm

## current stage showcase
<img alt="line rasterization" height="480" src="./images/triangle_line_rasterize.jpg" width="640"/>
<img alt="line rasterization" height="480" src="./images/triangle_fill_zbuffer.png" width="640"/>


