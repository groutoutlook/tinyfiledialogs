# tiny file dialogs ( cross-platform C/C++ ) v3.19.1 [Jan 27, 2025]

**Forked on 2025-04-10.**

- Tray-popup InputBox PasswordBox MessageBox Notification Beep ColorPicker
- ColorPicker OpenFileDialog SaveFileDialog SelectFolderDialog
- ASCII UTF-8 (and also MBCS & UTF-16 for Windows)
- Native dialog library for Windows MAC OSX GTK+ QT CONSOLE X Wayland
- SSH: automatic switch to console mode / X forwarding / waypipe

```cpp
void tinyfd_beep();

int tinyfd_notifyPopup(
    char const * aTitle , // NULL or ""
    char const * aMessage , // NULL or "" may contain \n \t
    char const * aIconType ); // "info" "warning" "error"

int tinyfd_messageBox(
    char const * aTitle , // NULL or ""
    char const * aMessage , // NULL or "" may contain \n \t
    char const * aDialogType , // "ok" "okcancel" "yesno" "yesnocancel"
    char const * aIconType , // "info" "warning" "error" "question"
    int aDefaultButton );
        // 0 for cancel/no , 1 for ok/yes , 2 for no in yesnocancel

char const * tinyfd_inputBox(
    char const * aTitle , // NULL or ""
    char const * aMessage , // NULL or "" (\n and \t have no effect)
    char const * aDefaultInput ); // NULL for a passwordBox, "" for an inputbox
        // returns NULL on cancel

char const * tinyfd_saveFileDialog(
    char const * aTitle , // NULL or ""
    char const * aDefaultPathAndOrFile , // NULL or "" , ends with / to set only a directory
    int aNumOfFilterPatterns , // 0 (1 in the following example)
    char const * const * aFilterPatterns , // NULL or char const * lFilterPatterns[1]={"*.txt"};
    char const * aSingleFilterDescription ); // NULL or "text files"
        // returns NULL on cancel

char const * tinyfd_openFileDialog(
    char const * aTitle , // NULL or ""
    char const * aDefaultPathAndOrFile , // NULL or "" , ends with / to set only a directory
    int aNumOfFilterPatterns , // 0 (2 in the following example)
    char const * const * aFilterPatterns , // NULL or char const * lFilterPatterns[2]={"*.png","*.jpg"};
    char const * aSingleFilterDescription , // NULL or "image files"
    int aAllowMultipleSelects ); // 0
        // in case of multiple files, the separator is |
        // returns NULL on cancel

char const * tinyfd_selectFolderDialog(
    char const * aTitle , // NULL or ""
    char const * aDefaultPath ); // NULL or ""
        // returns NULL on cancel

char const * tinyfd_colorChooser(
    char const * aTitle , // NULL or ""
    char const * aDefaultHexRGB , // NULL or "#FF0000‚Ç¥
    unsigned char const aDefaultRGB[3] , // unsigned char lDefaultRGB[3] = { 0 , 128 , 255 };
    unsigned char aoResultRGB[3] ); // unsigned char lResultRGB[3];
        // returns the hexcolor as a string "#FF0000"
        // aoResultRGB also contains the result
        // aDefaultRGB is used only if aDefaultHexRGB is NULL
        // aDefaultRGB and aoResultRGB can be the same array
        // returns NULL on cancel
```

# Note

- This is not for ios nor android (it works in termux and iSH though).
- The files can be renamed with extension ".cpp" as the code is 100% compatible C C++
- Windows is fully supported from XP to 11 (maybe even older versions)
- C# & LUA via dll, see files in the folder EXTRAS
- OSX supported from 10.4 to latest (maybe even older versions)
- Do not use " and ' as the dialogs will be display with a warning
  instead of the title, message, etc...
- There's one file filter only, it may contain several patterns.
- If no filter description is provided,
  the list of patterns will become the description.
- On Windows link against Comdlg32.lib and Ole32.lib
  (on Windows the no linking claim is a lie)
- On unix / macos: it only tries command line calls, so no linking is need.
- On unix /macos you need one of the following:
  applescript, kdialog, zenity, matedialog, shellementary, qarma, yad,
  python (2 or 3)with tkinter/python-dbus, Xdialog
  or curses dialogs (opens terminal if running without console).
- One of those is already included on most (if not all) desktops.
- In the absence of those it will use gdialog, gxmessage or whiptail
  with a textinputbox.
- If nothing is found, it switches to basic console input,
  it opens a console if needed (requires xterm + bash).
- for curses dialogs you must set tinyfd_allowCursesDialogs=1
- You can query the type of dialog that will be used (pass "tinyfd_query" as aTitle)
- String memory is preallocated statically for all the returned values.
- File and path names are tested before return, they should be valid.
- tinyfd_forceConsole=1; at run time, forces dialogs into console mode.
- On Windows, console mode only make sense for console applications.
- On Windows, console mode is not implemented for wchar_T UTF-16.
- Mutiple selects are not possible in console mode.
- The package dialog must be installed to run in curses dialogs in console mode.
  It is already installed on most unix systems.
- On OSX, the package dialog can be installed via
  http://macappstore.org/dialog or http://macports.org
- On Windows, for curses dialogs console mode,
  dialog.exe should be copied somewhere on your executable path.
  It can be found at the bottom of the following page:
  http://andrear.altervista.org/home/cdialog.php

```mark
 | The project provides an Hello World example:                    |
 |   if a console is missing, it will use graphic dialogs          |
 |   if a graphical display is absent, it will use console dialogs |
```


# UNIX (including MacOS) :
```sh
$ clang -o hello hello.c tinyfiledialogs.c
( or gcc tcc owcc icx suncc )
( or g++ clang++ icpx sunCC )
( some possible options :
  -ansi -std=c89 -std=c++98 -pedantic -Wstrict-prototypes
  -g3 -Wall -Wextra -Wdouble-promotion -Wconversion -Wno-sign-conversion
  -Wno-unused-parameter -Wno-unused-function -fsanitize=undefined -fsanitize=thread
  -Wno-deprecated -Wno-incompatible-compiler )
( if using musl instead of glibc: clang -fuse-ld=lld --rtlib=compiler-rt )
```
# Windows

- Visual Studio command line (Developer Shell Profile on Windows Terminal):
```sh
cl hello.c tinyfiledialogs.c comdlg32.lib ole32.lib user32.lib shell32.lib /W4
```

- Visual Studio
	- In the properties of your project, in the linker input field, you may need to add: comdlg32.lib ole32.lib user32.lib shell32.lib or maybe simply add: %(AdditionalDependencies)
	- TODO: things should be united to CMake or ideally `nmake` or `meson`.	
