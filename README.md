# Redmax

```console
$ make setup
$ make
```

The first command will clone in the lastest C++ bindings and targeted version of raylib, copy across any relevant header files into `/includes`, and build a static library file from them, placing it in `/lib`. The second command then compiles, runs and cleans up your project using the source code in `/src/main.cpp`.

By using the following Make commands instead of the default target, we can skip the cleanup step, and only recompile files that changed:

```console
$ make bin/app; make execute
```
