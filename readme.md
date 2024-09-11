# FRACTOL
42 School project for generating fractals with use of MLX42 windowing library

### 1. ADDING MLX42:
- MLX library has its repository https://github.com/codam-coding-college/MLX42
this project includes it as sa submodule, run git submodules update --init --recursive to get it
- if doesn't work, clone the repo: git clone https://github.com/codam-coding-college/MLX42 MLX42
- then to make executable of the lib:
cd MLX42
cmake -B build
make -C build/
- MLX42 must be linked in Makefile with other libraries it depends on:
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm (or -lglfw3, based on system)
	- l... = prefix for linking
	- dl = dynamically typed
	- m = math library
	- glfw = graphics library framework

###
