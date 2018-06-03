# GrahpicsLib
## Introduction

This is a simple graphics library which is built mainly for learning purposes and to understand
how things work under the hood. 

The library is meant to be lightweight and to not offer "opinions" on how to do things as possible. 
It is merely an API to draw things in 3D within a given window. 

There is currently a strong coupling to windows, as an HWND is needed for initialization of the
main graphics object, FBGraphics. 

FBGraphics is an abstract class and currently implemented only by the DX9Graphics, but it 
can be implemented by different types of 3D hard- and software frameworks, such as OpenGL, DX11, DX12 etc. 

The exposed methods of the FBGraphics interface aim to be universally useable, regardless of the underlying 
implementation: 
* clearing the screen
* rendering a list of triangles (aka meshes)
* basic lighting
* render to texture
* flipping the backbuffer to present the rendered scene


