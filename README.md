# LIBNFC-CROSSENGINE

## Demo

[![Watch the demo](http://img.youtube.com/vi/fMQwZRW1wng/mqdefault.jpg)](http://www.youtube.com/watch?v=fMQwZRW1wng)

You can also watch the video directly:  
<http://www.youtube.com/watch?v=fMQwZRW1wng>

---

## Building the Project

### 1. Initialize submodules

If the repository was cloned **without the `--recursive` flag**, run:

```bash
git submodule update --init --recursive
```

- Build the native library:

```bash
mkdir build
cd build
cmake ..
make
make install
```

To disable Godot support, run:
```cmake .. -DBUILD_GODOT=OFF```

## Build the Unity C# bindings

```bash
cd csharp-unity
dotnet build ./csharp-unity.slnx
```

## Installing from Source

### Unity

- Copy the contents of:  
   `csharp-unity/src/bin/netstandard2.0`
- Place the following files in:  
 `<Project Dir>/Assets/Plugins`
  - libcastanetsDotNet.*
- Place all remaining files in:  
  `<Project Dir>/Assets/Plugins/x86_64`

### Unreal Engine

- Copy the entire unreal directory into:
  `<Project Dir>/Plugins/UnrealLibNFC`
- Build the project using UAT (Unreal Automation Tool).  
  ⚠️ Note
  The .so / .dll files may sometimes be placed in:
  `<Project Dir>/Plugins/UnrealLibNFC/Binaries/Linux64`
  instead of the expected Linux folder.  
  This appears to be an Epic Games build system issue.

### Godot
If you built the project using CMake, copy:
`<repo>/install/GDCastanets`  
into:  
`<Project Dir>/addons/`
