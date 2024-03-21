
<p align="center">
  <a href="" rel="noopener">
   <img width=400px height=200px src="https://blog.kakaocdn.net/dn/GxuVd/btqGexq5xu5/9tRFLpU6t9Tz8tONghC5L1/img.png" alt="Project logo"></a>
</p>

<h3 align="center">Simple Wolfenstein</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Issues](https://img.shields.io/github/issues/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/issues)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Raycasting in C with MiniLibX
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Key and Mouse Control](#key_and_mouse)
- [Images](#images)
- [External resources](#sources)
  
## 🧐 About <a name = "about"></a>

First Raycasting project in Hive. Goal of the assignment is to read 2D mapfile, calculate the player's angle and render the graphic on the screen based on player's point of view.

## Collaborators

[Yoonseon Lee](https://github.com/ynslee) , [Josefina Husso](https://github.com/hussojo)

## Language Used

[![Language Used](https://skills.thijs.gg/icons?i=c)](https://skills.thijs.gg)

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### 1. Compilation:

```shell
git clone the repository 
```

### 2. Running the Program:
There are two versions of the program: cub3D and cub3D_bonus. cub3D_bonus adds wall collision, a minimap, ability to rotate the view by moving the mouse and opening and closing the door. With cub3D_bonus, if you use 'maps/good/bonus/doggo.cub' as argument, you can also eat chicken blocks by going through it.

To compile the mandatory, do :

```shell
make
```

To compile the bonus, do :

```shell
make
```

To run the program:
```shell
./cub3D path/to/map.cub
./cub3D_bonus path/to/map.cub
```
The program takes a map file as an argument. Maps are available in the `maps` directory. Under 'maps' directory, 'good' directory should run smoothly with program, and 'bad' should be rejected. If you would like to see the doors, you should find 'bonus'under 'good' maps directory.<br/>
For example:

- `./cub3D maps/good/lava.cub` should run.
- `./cub3D_bonus maps/good/bonus/doggo.cub` should run.
- `./cub3D_bonus maps/bad/bad.cub` should fail. (for the forbidden.cub, please do 'chmod 000 maps/bad/forbidden.cub' and run)

## Key and Mouse Control <a name = "key_and_mouse"></a>

| __Key__        | __Action__   |
| -------------  |:-------------:|
| W              | Move forward |
| A       | Move left      |
| S  | Move backward      |
| D  | Move right      |
| Left Arrow  | Turn Left      |
| Right Arrow  | Turn Right      |
| Up Arrow  | Move forward      |
| Down Arrow  | Move backward      |
| Return  | Open door      |
| Space  | Close door      |
| Mouse - Click and drag  | Turn   |
| ESC  | Close window      |

## Images <a name = "images"></a>

### example 1 - ./cub3D_bonus maps/good/bonus/doggo.cub
<img width="1920" alt="doggo" src="https://github.com/ynslee/cub3d/assets/112563002/f4861526-927e-421f-9bae-cb1658c4e3c8">

### example2 - ./cub3D_bonus maps/good/bonus/frozen.cub
<img width="1920" alt="frozen" src="https://github.com/ynslee/cub3d/assets/112563002/311df614-c0c1-42fa-9870-631218ce0f5f">


## External resources <a name = "sources"></a>

+ [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
+ [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
+ [DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
+ [Flood fill algorithm](https://en.wikipedia.org/wiki/Flood_fill)
+ [Ray-Casting Tutorial For Game Development And Other Purposes by F.Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
+ [MiniLibX documentation](https://harm-smits.github.io/42docs/)
