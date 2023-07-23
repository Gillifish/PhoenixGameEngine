# PhoenixGameEngine
A game engine I am learning how to create using lectures from Dave Churchill on youtube.

# Tutorial link
> https://www.youtube.com/watch?v=S7lXSihz0ac&list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV&ab_channel=DaveChurchill

# Building on Mac

First, create a folder called "build" in your project directory.
Then create a bash script called "configure.sh" with these lines:
> cd build

> cmake ..

Second, create a bash script called "compile.sh" with these lines:
> cmake --build build/

Finally, create a bash script called "run.sh" with these lines:
> ./build/src/main

Execute these scripts in order and boom, engine built!

# Building on Windows

Follow Mac directions except in the "configure.sh" file replace:
> cmake ..

with:

> cmake -DBUILD_SHARED_LIBS=OFF ..

Then find the "open32al.dll" from your "_deps" folder once you have ran the "compile.sh" script and add it to the build/src/Debug file where your EXE file lives.
