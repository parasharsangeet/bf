# Brainfuck 

An interpreter for the Brainfuck programming language

## Installation

### 1. Clone the source
```sh
$ git clone https://github.com/Sangeet-Parashar/bf.git
$ cd bf
```

### 2. Building the project
This project uses CMake as the build system. You can install it from [here](https://cmake.org/download/).
```sh
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config Release
```
This binary will be generated inside the bin folder in the project root.
###

### 3. Testing the executable

There is a hello world example in the examples/ folder. You can test the executable by running the hello world example. 

On Windows, 
```sh
$ .\bin\Release\bf.exe .\examples\hello_world.bf
```

On Unix,
```sh
$ ./bin/Release/bf ./examples/hello_world.bf
```

If everything worked out successfully, you should be able to see the "Hello, World!" message printed to the console.