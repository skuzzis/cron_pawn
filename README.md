# SA:MP Example Plugin (C++11)

This is a SA:MP plugin starter kit project for developing plugins in C++.

## Requirements

**Visual Studio**

I've tested this on Visual Studio 2022 and will also work on earlier versions.

[Get Visual Studio 2022](https://visualstudio.microsoft.com/vs/)

**CMake 3+**

This is used for project files generation. I recommend you to use the cmake command from PowerShell.

[Get CMake 3+](https://cmake.org/download/)

**Some Command-Line Knowledge**

I've used PowerShell on Windows, but you can also use CMD or Git-Bash.

## First Run

When you first clone the project, you need to do some modifications before you can begin writing code.

### Name

You need to change the project name from `CMakeLists.txt`, `src/CMakeLists.txt` and also `src/common/common.hpp`.

Also, you can do a find-and-replace action across all files for the following:

- `example_plugin` => into your plugin name. 
- `src/include/example_plugin.inc` => into `src/include/YOUR_PLUGIN_NAME.inc`.

### Create a CMake Build Directory

You need now to open PowerShell and create the build directory for the plugin. It will automatically generate an `.sln` file for Visual Studio project.

#### x86 Windows Architecture
```
mkdir build; cd build;
cmake ..
```

#### x86_64 (x64) Windows Architecture
```
mkdir build; cd build;
cmake -G "Visual Studio 17 2022" -A Win32 ..
```

![](https://cdn.pubber.xyz/images/7x6k9df88ohqdly1qllh9y2y4gdlbhfh.gif)

## Explanation of files

### ***``lib``***

This folder contains external dependencies like `cmake-modules` provided by Zeex to use with CMake and `samp-plugin-sdk` for SA:MP plugins to work with SA:MP itself.

### ***``src``***

This folder contains the full source code of the plugin itself. It's structured as shown below:

```
main.cpp
common/common.hpp
include/PLUGIN_NAME.inc
natives/natives.hpp
natives/natives.cpp
utilities/utilities.hpp
utilities/utilities.cpp
```

The `src/CMakeLists.txt` declares which files are relevant to build the project.