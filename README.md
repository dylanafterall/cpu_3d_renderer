# 3D Graphics Renderer in C

<p>A 3D renderer built in C language, for self-study of graphics programming.<br>
This project was coded for readability, not optimization or commercial application.</p>

<p>This project contains code from Gustavo Pezzi's "3D Computer Graphics 
Programming", a fantastic and highly recommended course, found here: 
https://pikuma.com/courses.</p>

Course topics implemented:<br>
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
    <li>Camera Implementation and Clipping</li>
</ul>

Ancillary lessons learned / skills trained:<br>
<ul>
    <li>Command-line Git</li>
    <li>Include and Library Paths</li>
    <li>Static vs. Dynamic Libraries</li>
    <li>Makefile Advanced Features and Limitations</li>
    <li>Greater Understanding of C vs. C++</li>
    <li>Code Documentation Practices</li>
</ul>
</p>

## Installation

**Linux & Mac**

## Acknowledgment

<p>This project uses Simple DirectMedia Layer (SDL2), a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. Find SDL2 here: http://www.libsdl.org/.<br>

<p>This project uses Sean Middleditch's uPNG project, which supports loading and decoding PNG images into a simple byte buffer, suitable for passing directly to OpenGL as texture data. Find uPNG here: 
https://github.com/elanthis/upng.</p>