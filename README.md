# MAZE

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>

## Introduction

This project creates a maze and allows the user to travel within it.
The player will have some number of steps to travel through the maze.
The number of steps is determined by the quadratic function \\( t=\left\lfloor\frac{s^2}{8}+s+8\right\rfloor \\).

## How it Works

The `main.cpp` file handles setup, getting game size, timer, and checking for game end.
It runs the `make_maze` function from the `Maze.cpp` file.
The `Maze.cpp` file generates a random maze. The maze is a mathematical graph, a tree.
All nodes can have any number of child nodes.
Trees of this format can be created by the `make_maze` function.
It uses the recursive `link_rooms` function to connect the start and end nodes together, with the call:
```cpp
link_rooms(0, n-1, &m);
```
Then `link_rooms` may call itself to connect room 0 to a, and a to n-1, and the process continues.

## In Use

![example GIF](ex.gif "EXAMPLE")