# PixelForge

A photo editor from scratch in C++17. You write the missing pieces one day at a time.

## Build

On a Mac, install Apple's compiler once with `xcode-select --install`. After that, `g++`
works in Terminal. No other libraries are required. Run these commands from this folder.

    g++ -std=c++17 -Wall -pthread -Iinclude -Itests src/*.cpp tests/*.cpp -o forge_tests
    g++ -std=c++17 -Wall -pthread -Iinclude src/*.cpp app/main.cpp -o forge

    g++ -std=c++17 -Wall -pthread -Iinclude src/*.cpp app/play.cpp -o play

If you have make, `make` runs all three commands.

## Daily use

1. Search the code for `TODO Day 7` (use your day number).
2. Write the code.
3. Rebuild, then run `./forge_tests day7`.

`./forge_tests` alone shows all days. PASS means done, TODO means not started and FAIL means
something is wrong. Failed checks print the line in `tests/test_days.cpp`.

## See your work

From Day 6, edit `app/play.cpp`, build it and run `./play`, then open `output/play.bmp`.
Rebuild after each change.

## Run the full app

The script app needs Days 1 to 24, because it uses everything you build.

    ./forge scripts/demo.forge

Open the .bmp files in `output/` with `open output/play.bmp`, which uses Preview on a Mac.

To use your own photo, convert it first, then start a script with `load my_photo.bmp`:

    sips -s format bmp my_photo.jpg --out my_photo.bmp

Commands: plasma, load, save, undo, redo, ascii, stats, history, invert, grayscale, threshold,
brightness, tint, equalize, blur, sharpen, median.

## Finding memory errors

Add `-g -fsanitize=address,undefined` to the compile command to catch double deletes and bad
pointers. Apple's compiler doesn't report leaks this way, but the day tests check for them.
