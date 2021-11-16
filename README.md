# fract-ol

This project’s goal is to create a small fractal exploration program. Start by seeing what a fractal is.
The constraints are as follows:
• Your software should offer the Julia set and the Mandelbrot set.
• The mouse wheel zooms in and out, almost infinitely (within the limits of the computer). This is the very principle of fractals.
• You must use at least a few colors to show the depth of each fractal. It’s even better if you hack away on psychedelic effects.
• A parameter is passed on the command line to define what type of fractal will be viewed. If no parameter is provided, or if the parameter is invalid, the program displays a list of available parameters and exits properly.
• More parameters must be used for fractal parameters or ignored.
• You must be able to create different Julia set with the parameters of the program.
As for the graphic representation:
• ESC will exit the program.
• The use of images of the minilibX is strongly recommended.



Ex:

make re && ./fractol Mandelbrot
