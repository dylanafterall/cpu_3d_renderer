## \*** This Project is Archived \***

<p>This project served its educational purpose, teaching me mathematical and programming concepts behind rendering a 3D space. I do not plan to revisit this project, other than to review as a personal reference.</p>

# CPU 3D Renderer in C

![]()

<p>This project uses code found in Gustavo Pezzi's (highly recommended) "3D Computer Graphics Programming" course, found here:
<a href="https://pikuma.com/courses">Pikuma Courses</a></p>

<p>Assets (models and textures) made by Author: <a href="https://opengameart.org/users/mathildelea">Mathilde_Lea</a>, <a href="https://creativecommons.org/licenses/by/4.0/">LICENSE</a></p>

<p>This 3D renderer uses a left-handed coordinate system, with a clockwise triangle face
winding order. Its development was for educational purposes, not commercial application. Understanding mathematical and programming concepts was prioritized over performance considerations. All rendering is done on CPU.</p>

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

## Instructions

Keypress Guide<br>

<ul>
    <li>ESC Key: close window / exit program</li>
    <li>W Key: rotate camera pitch down (objects rotate 'up')</li>
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

## Dependencies:

<p>
<ul>
    <li><a href="http://www.libsdl.org/">Simple DirectMedia Layer (SDL2):</a></li>
    <ul>
        <li>A cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D</li>
    </ul>
    <li><a href="https://github.com/elanthis/upng">Sean Middleditch's uPNG:</a></li>
    <ul>
        <li>Supports loading and decoding PNG images into a simple byte buffer, suitable for passing directly to OpenGL as texture data</li>
    </ul>
</ul>
</p>

## Tools Used:

<p>
<ul>
    <li>Vim, VS Code, Ubuntu, MacOS</li>
</ul>
</p>
