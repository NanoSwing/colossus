# Colossus
A modular game framework written in C.


# Compiling
### Windows
Windows builds have only been tested with cygwin.
```shell
$ git clone https://github.com/NanoSwing/colossus.git
$ cd colossus
$ make release
```

### Arch
```shell
$ git clone https://github.com/NanoSwing/colossus.git
$ cd colossus
$ make release
```

# Using in project
When linking with the colossus libraray, you'll also need to link **-lgdi32** if you're on windwos and **-lm** on linux.

You'll need to copy the colossus folder from the setup folder into the same place the binary recides in. It contains assets used by the library.

# Dependencies
[GLFW](https://github.com/glfw/glfw), [glad](https://github.com/Dav1dde/glad) and some [stb](https://github.com/nothings/stb) headers are used for graphics. Both libraries are compiled into the Colossus library.
