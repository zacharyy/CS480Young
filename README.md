# Example OpenGL Graphics Program
## This is for use at the University of Nevada, Reno CS 480/680 Graphics Class

# Build Instructions
The building of the project is done using CMake. Running CMake in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  
Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place ```COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders```.

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```
