#/bin/bash 2>nul || goto :windows


# bash
echo hello Bash
ls

src/build/premake5.linux codelite
src/build/premake5.linux gmake
src/build/premake5.linux vs2013
src/build/premake5.linux xcode4
src/build/premake5.linux ninja
src/build/ninja.linux -C ide

src/build/premake5.osx codelite
src/build/premake5.osx gmake
src/build/premake5.osx vs2013
src/build/premake5.osx xcode4
src/build/premake5.osx ninja
src/build/ninja.osx   -C ide

exit


:windows
@echo off
echo hello Windows
ver

src\build\premake5.exe codelite
src\build\premake5.exe gmake
src\build\premake5.exe vs2013
src\build\premake5.exe xcode4
src\build\premake5.exe ninja
src\build\ninja.exe -C ide
if "0"=="%ERRORLEVEL%" (
pushd bin\debug
echo ^>^> avlauncher
avlauncher
echo ^<^< avlauncher
popd
)

exit /b
