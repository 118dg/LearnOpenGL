# learnopengl.com code repository
Contains code samples for all chapters of Learn OpenGL and [https://learnopengl.com](https://learnopengl.com). 

## Windows building
All relevant libraries are found in /libs and all DLLs found in /dlls (pre-)compiled for Windows. 
The CMake script knows where to find the libraries so just run CMake script and generate project of choice.
Note that you still have to manually copy the required .DLL files from the /dlls folder to your binary folder for the binaries to run.

Keep in mind the supplied libraries were generated with a specific compiler version which may or may not work on your system (generating a large batch of link errors). In that case it's advised to build the libraries yourself from the source.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev  libxi-dev` .
Next, run CMake (preferably CMake-gui). The source directory is LearnOpenGL and specify the build directory as LearnOpenGL/build. Creating the build directory within LearnOpenGL is important for linking to the resource files (it also will be ignored by Git). Hit configure and specify your compiler files (Unix Makefiles are recommended), resolve any missing directories or libraries, and then hit generate. Navigate to the build directory (`cd LearnOpenGL/build`) and type `make` in the terminal. This should generate the executables in the respective chapter folders.

Note that CodeBlocks or other IDEs may have issues running the programs due to problems finding the shader and resource files, however it should still be able to generate the exectuables. To work around this problem it is possible to set an environment variable to tell the tutorials where the resource files can be found. The environment variable is named LOGL_ROOT_PATH and may be set to the path to the root of the LearnOpenGL directory tree. For example:

    `export LOGL_ROOT_PATH=/home/user/tutorials/LearnOpenGL`

Running `ls $LOGL_ROOT_PATH` should list, among other things, this README file and the resources direcory.

### Linux building in Docker
Using [this project](https://github.com/01e9/docker-ide) you can start IDE in docker:
```
.../docker-ide/ide cpp-gpu ~/.../clion/bin/clion.sh -x11docker "--gpu"
```

## Mac OS X building
Building on Mac OS X is fairly simple (thanks [@hyperknot](https://github.com/hyperknot)):
```
brew install cmake assimp glm glfw
mkdir build
cd build
cmake ../.
make -j8
```

## Glitter
Polytonic created a project called [Glitter](https://github.com/Polytonic/Glitter) that is a dead-simple boilerplate for OpenGL. 
Everything you need to run a single LearnOpenGL Project (including all libraries) and just that; nothing more. 
Perfect if you want to follow along with the chapters, without the hassle of having to manually compile and link all third party libraries!

-----------------------------------------------------------------------------------------------------------------------------------------------------

# Explanation about my works
You can see my projects' source codes at ComputerGraphics/src/3.model_loading folder.
3.model_loading/2.robot_arms & 3.model_loading/3.cylinder are projects which I had been working on.

## 2.robot_arms
You can handle robot_arms with WASD keys (oh, except A key because I am using A key to handle the light) and moving mouse.
If you enter A key, you can see the light changing.

The doll next to the robot arm is miniature of my real doll. I made it into 3D object using '3DF Zephyr Free' program.

You can get extra explanation about my work from my blog.
Link is over here > https://blog.naver.com/118dg/222112739224
                    https://blog.naver.com/118dg/222123534219
                    https://blog.naver.com/118dg/222131018308
                    https://blog.naver.com/118dg/222156074649

## 3. Cylinder
...(will write sth)...

You can get extra explanation about my work from my blog.
Link is over here > https://blog.naver.com/118dg/222178707354

