# 3D Graphics Renderer in C

<p>A 3D renderer built in C language, for self-study of graphics programming.<br>
The renderer uses a left-handed coordinate system, with a clockwise triangle face
winding order.<br>
This project is for educational purposes, not commercial application. 
Code was written for readability, not optimization.</p>

Primary functionality learned / implemented:<br>
<ul>
    <li>Vector (Vertex) Transformations</li>
    <li>Orthographic vs. Isometric vs. Perspective Projection</li>
    <li>Coordinate System Handedness</li>
    <li>Game Loop Time Step / Delay Function / Constant Framerate</li>
    <li>Creating Triangle Meshes</li>
    <li>Digital Differential Analyzer vs. Bresenham's Line Algorithms</li>
    <li>OBJ File (3D Model) Input</li>
    <li>Back-face Culling</li>
    <li>Triangle Rasterization</li>
    <li>Painter's Algorithm (Face Sorting by Depth)</li>
    <li>Z-Buffer (Replacing Painter's Algorithm)</li>
    <li>3D Matrix Transformations</li>
    <li>Light and Shading</li>
    <li>Texture Mapping</li>
    <li>Perspective Correct Interpolation</li>
    <li>Camera Implementation and (Frustum) Clipping</li>
    <li>Graphics Pipeline Structure</li>
</ul>

Ancillary lessons learned / skills trained:<br>
<ul>
    <li>Command-line Git</li>
    <li>Include and Library Paths</li>
    <li>Static vs. Dynamic Libraries</li>
    <li>Makefile Advanced Features and Limitations</li>
    <li>Greater Understanding of C vs. C++</li>
    <li>Broad differences between graphics APIs / Graphics Pipelines</li>
</ul>
</p>

## Installation

**Linux & Mac**

<ol>
    <li>Download the SDL2 library, following the instructions provided:</li>
        <ul>
            <li>https://www.libsdl.org/download-2.0.php</li>
        </ul>
    <li>Clone this repository into a local directory:</li>
        <ul>
            <li>https://github.com/dylanafterall/cRenderer.git</li>
        </ul>
    <li>Using console/terminal, navigate to local directory.</li>
    <li>Enter command "make" to build the renderer.</li>
    <li>Enter command "make run" to start running the renderer.</li>
</ol>

## Instructions

Keypress Guide<br>
<ul>
    <li>ESC Key: close window / exit program</li>
    <li>W Key: rotate camera pitch down (objects rotate 'up') - </li>
    <li>A Key: rotate camera yaw right (objects rotate 'left')</li>
    <li>S Key: rotate camera pitch up (objects rotate 'up')</li>
    <li>D Key: rotate camera yaw left (objects rotate 'right')</li>
    <li>Up Arrow Key: move camera forwards</li>
    <li>Down Arrow Key: move camera backwards</li>
    <li>1 Key: render wireframes and dots at vertices</li>
    <li>2 Key: render wireframes</li>
    <li>3 Key: render filled triangles (solid color)</li>
    <li>4 Key: render filled triangles and wireframes</li>
    <li>5 Key: render textured triangles</li>
    <li>6 Key: render textured triangles and wireframes</li>
    <li>C Key: enable backface culling</li>
    <li>X Key: disable backface culling</li>
</ul>

## Acknowledgment

<p>This project follows the tutorial of, and contains code from,
Gustavo Pezzi's "3D Computer Graphics Programming", a fantastic and highly
recommended course, found here: https://pikuma.com/courses.</p>

<p>This project uses Simple DirectMedia Layer (SDL2), a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. Find SDL2 here: http://www.libsdl.org/.</p>

<p>This project uses Sean Middleditch's uPNG project, which supports loading and decoding PNG images into a simple byte buffer, suitable for passing directly to OpenGL as texture data. Find uPNG here:
https://github.com/elanthis/upng.</p>
