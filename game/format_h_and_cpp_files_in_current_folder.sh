#!/bin/bash

clang-format -style="{BasedOnStyle: LLVM, AllowShortFunctionsOnASingleLine: Empty, BreakBeforeBraces: Stroustrup, IndentWidth: 4, PointerAlignment: Left, TabWidth: 4, UseTab: Always}" -i *.h *.cpp
