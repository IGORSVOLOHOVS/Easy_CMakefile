# easy-cmakefile

An annotated `CMakeLists.txt` from July 2023, written as an easy-to-read starting
point for a C++20 project that takes its libraries from vcpkg, with one example
source file. It is a template to copy from, not a program.

## What is here

- `CMakeLists.txt` sets C++20, creates `bin`, `lib`, `include` and `src` in the
  build folder, takes every `src/*.cpp` and `include/*.h` into one executable
  named `test_cmake`, and links it with `libcurl`. Its comments are in Russian and
  show where to switch to a static library or add more vcpkg libraries.
- `src/main.cpp` is the example: it sends one GET request with libcurl to
  `https://api.example.com/data`, a placeholder address, and prints the answer.
- `.vscode/` holds the tasks and launch settings the Easy C++ Projects extension
  wrote: build with `make` in `build/`, then run `build/main`.
- The old README explained the file section by section; this one replaces it.

Three things to know before copying it:

- The vcpkg path is fixed to `C:/Users/User/.clion-vcpkg/vcpkg`, one machine's
  folder.
- `CMAKE_TOOLCHAIN_FILE` is set after `project()`, where CMake no longer reads it,
  so the vcpkg toolchain is not used; the explicit include and library folders
  are what find curl.
- `set(-DCURL_STATICLIB=ON)` sets nothing: it is not a variable name.

Nothing here is built or tested in this lab.

## Working on it

This repository ships no program. `.\recipe.ps1` is still its whole interface:
`.\recipe.ps1 test` runs pytest and ruff over `.claude`, and `.\recipe.ps1 info`
prints the metadata. The other verbs print `nothing to <verb>`. `CLAUDE.md`
holds the rules.

## License

MIT, as it stood on GitHub. See [LICENSE](LICENSE).
