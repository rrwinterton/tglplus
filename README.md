# tglplus
This repo will detect the current microarchitectures greater than Intel tiger lake and if it has AVX10 support

There are two ways to build:

Install LLVM Compiler to your machine. This example is c:\program files\llvm\bin. You can use clang-cl as well

To build with cmake:
    cd build

    cmake .. -DCMAKE_C_COMPILER="C:\Program Files\LLVM\bin\clang.exe" -DCMAKE_CXX_COMPILER="C:\Program Files\LLVM\bin\clang++.exe" -DCMAKE_C_FLAGS="/MD /Zi /O2 /Ob2 /EHsc /DNDEBUG" -DCMAKE_CXX_FLAGS="/MD /Zi /O2 /Ob2 /EHsc /DNDEBUG" -DCMAKE_BUILD_TYPE=RelWithDebInfo

    cmake --build . --config RelWithDebInfo

To build with visual studio
    Open tglplus.vcxproj in visual studio and build.

    run RelWithDebInfo\tglplus.exe

The output results should lookd something like this with appropriate data:

    c:\Users\rrwin\Downloads\dev\tglplus\build>RelWithDebInfo\tglplus.exe
    Detect Intel Tiger Lake Plus
    Model detected:  Lion Cove (0xbd)
    Model detected to be >= Tiger Lake.
    AVX 10 not supported.

