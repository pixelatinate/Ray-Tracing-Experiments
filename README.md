# Ray-Tracing-Experiments

I wanted to write a ray tracer, and Peter Shirley's *Ray Tracing in One Weekend* seemed like a good place to start! Nearly all of the C++ was written by him, though I've gone through and added a couple of things that helped me both in understanding the content and building the files. 

One of the earliest things I wrote for this project was the Makefile- some instructions for it:

After navigating to the Ray-Tracing directory, you can run three commands. 
```make``` will compile the program 
```make test``` will compile and run the program 
```make clean``` will delete the last compiled version of the program, the .ppm file, and the .txt file. 

For people who are unfamiliar with .ppm's- that's the image file! Your computer should be able to open them directly. If not, there are a few online .ppm viewers, and I've also included the .txt file in there too. 

Another thing I have changed is that in Peter's original code, the same image would be generated each time. I seed the random number generator because I thought it would be fun to have a new picture on each run. Feel free to remove the srand( time(NULL) ) ; line in generateppm.cpp. This can be helpful for troubleshooting or the like. 
