@echo off
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
) else (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

set compilerflags=/Od /Zi /EHsc /MD /std:c++17 /I include /DUNICODE /D_UNICODE
set linkerflags=/OUT:bin\main.exe 
set libs=opengl32.lib user32.lib gdi32.lib kernel32.lib shell32.lib lib\glfw\glfw3.lib
cl.exe %compilerflags% src\*.cpp lib\glad\glad.c %libs% /link %linkerflags%
del bin\*.ilk *.obj *.pdb