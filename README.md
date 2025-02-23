# vscode-msvc
A program that launches Visual Studio Code with MSVC Toolchain support.

## Pre-requisites
* Visual Studio Code installed;
* Visual Studio Build Tools installed along with MSVC and Windows SDK;
* VS Code must be added to ```PATH``` (This is done automatically when VS Code is installed, but check if you can run the command ```code``` from the terminal just in case);
* An environment variable ```VSBUILDTOOLSDIR``` must be set, containing the path of Visual Studio Build Tools directory (usually: ```C:\Program Files (x86)\Microsoft Visual Studio\<visual-studio-edition-year>\BuildTools```, may be different for your system).

## Installation
* Make sure pre-requisites are fulfilled.
* Download the latest version of ```vscode-msvc``` from the [Releases](https://github.com/ArijitKD/vscode-msvc/releases) section. There are two files, ```vscode-msvc-x86.exe``` and ```vscode-msvc-x64.exe```. They are for the 32-bit and 64-bit MSVC toolchains respectively, and do not denote the program architecture. You'd want to download both for convenience.
* Copy them to your Desktop/Workspace folder and use them as per your requirements.

## License
```vscode-msvc``` is available under the MIT License.
