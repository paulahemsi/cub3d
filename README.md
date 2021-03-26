# cub3d
cause Doom was a milestone in my childhood

* [Introduction](#introduction)
* [Step by step](#step_by_step)
* [Work Diary](#work_diary)
* [Mindmap](#mindmap) 
* [Study resources](#study_resources)
* [Usage](#usage)

## introduction 
:suspect:

This [project](https://github.com/paulahemsi/cub3d/blob/main/study_resources/en.subject.pdf) is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. It will enable to explore ray-casting. My goal will be to make a dynamic view inside a maze, in which you’ll have to find your way

## step_by_step 
:hurtrealbad:

## work_diary

inspired by L.R.Couto [Grumpy Robot](https://github.com/lrcouto) and some articles [like this one](https://hbr.org/2011/04/four-reasons-to-keep-a-work-di) from Teresa Amabile or [this one](https://medium.com/the-productivity-inn/how-to-maintain-a-work-diary-for-better-career-growth-eb543f97c34b) from Musa Mawanda.

>Keeping regular work diaries, which took no more than ten minutes a day, gave many of our research participants a new perspective on themselves as professionals and what they needed to improve.

<details>
  <summary>Click to expand (:</summary>

* 16/03 and 17/03: I watched this free [course](https://courses.pikuma.com/courses/raycasting) *Introduction to Raycasting Theory with JavaScript* from Pikuma
and this [coding challenge](https://www.youtube.com/watch?v=TOEi6T2mtHo) *2d Raycasting with p5js* from Coding Train

* 18/03: I studied collision detection and field of view algotithms. [more info](#study) and start to code a js prototype with p5.js library to understand the concepts better

![](./study_resources/mindmaps/prototype_cub.gif)

* 19/03: I inserted ft_printf in libft and libft in cub project, making the necessaries adjustments. I created makefile with some rules (including a test rule with -fsanitize flag to check leaks during the process). I created cub3d header with a first struct organization to keep the informations from the .cub configuration file. I began this work diary and I started to study those new authorized functions:

* perror:

> The C library function void perror(const char *str) prints a descriptive error message to stderr. First the string str is printed, followed by a colon then a space.
[mais infos](https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm)

* strerror: 

>The C library function char *strerror(int errnum) searches an internal array for the error number errnum and returns a pointer to an error message string. The error strings produced by strerror depend on the developing platform and compiler.
[mais infos](https://www.tutorialspoint.com/c_standard_library/c_function_strerror.htm)

* exit:

>The C library function void exit(int status) terminates the calling process immediately. Any open file descriptors belonging to the process are closed and any children of the process are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.
[mais infos](https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm)

I made main.c function and error handling for program arguments (.cub and flag --save). I began the error handling in the scene from the .cub file, parsing the possibles type identifiers.

* 20/03: I manage to adjust [vscode debugger for wsl](https://code.visualstudio.com/docs/cpp/launch-json-reference) thanks to [this extension](https://code.visualstudio.com/docs/remote/wsl-tutorial). I began a error handling mindmap.

![](./study_resources/mindmaps/cub3d_errors.jpg)

* 21/03: I manage to save textures paths and resolution, floor and ceiling values in theyer own variables (inside configs struct).
I still need to deal with the map and double configs.

* 22/03: Paths duplicicty problem solved! It was easier than I've imagined, I'm very glad with this path function =) I realised that resolution and color duplicity was already solved because of the function logic. yey!

* 23/03: I finished map and walls errors handling. Map correctly stored in a 2d array.

* 24/03: I included minilibx but I'm struggling to generate a window with it. May be is an Wsl issue :/

  
![](./study_resources/mindmaps/check_walls.jpg)

* 25/03: I gave up wsl and started working on the vm. The window with mlx was generated and I manage to render some pixels and lines (yey!). I start to studied geometry in computer graphics

![](./study_resources/vectors.png)

> linear algebra is a branch of mathematics that has to do with the study of vectors. 

>A vector can be represented as an array of numbers. This array of numbers, which can assume any desired length, is also sometimes called a tuple in mathematics.

>Here, a point is a position in a three-dimensional space. A vector, on the other hand, usually means a direction (and some corresponding magnitude, or size) in three-dimensional space. Vectors can be thought of as arrows pointing various directions.

Player position and player orientation are now been saved in the configs struct, I bet it will be very important in the future.

</details>

## mindmap 
:goberserk:

## study_resources
:finnadie:

### raycasting
* [Nothing To Hide's light explanation](https://ncase.me/sight-and-light/) by Nicky Case 
* [2d Raycasting coding challenge](https://www.youtube.com/watch?v=TOEi6T2mtHo) by Daniel Shiffman (Coding Train)
* [Ray Marching](https://www.youtube.com/watch?v=Cp5WWtMoeKg) by Sebastian Lague
* [Collision Detection book](http://www.jeffreythompson.org/collision-detection/) by Jeffrey Thompson
* [Symmetric Shadowcasting](https://www.albertford.com/shadowcasting/) by Albert Ford
* [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
* [field of view algotithms overview](http://www.adammil.net/blog/v125_Roguelike_Vision_Algorithms.html) by Adam Milazzo
* [2d visibility article](https://www.redblobgames.com/articles/visibility/) by Red Blob Games

### minilibX and computer graphics
* [minilibX-linux](https://github.com/42Paris/minilibx-linux)
* [minilibX guide](https://harm-smits.github.io/42docs/libs/minilibx) by Harm-Smits
* [computer graphics from scratch](https://www.scratchapixel.com/)
* [math.h](https://www.tutorialspoint.com/c_standard_library/math_h.htm)
 
### virtual machine
* [vscode settings sync video](https://www.youtube.com/watch?v=f-uzUsHTQ8s) by James Q Quick

### further_reading

## usage 
:feelsgood:


