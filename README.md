The current way to compile the file is through the commands

g++ -std=c++11 -c main.cpp -lm

followed by

g++ main.o -o main.exec -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

There will soon be a make file that will counteract the deficiencies of this process.
