# `tinyfiledialogs` (pure C)

v3.19.1 [Jan 27, 2025]

**Forked on 2025-04-10.**

- `Tray-popup InputBox PasswordBox MessageBox Notification Beep ColorPicker OpenFileDialog SaveFileDialog SelectFolderDialog`
- ASCII UTF-8 (and also MBCS & UTF-16 for Windows)
- Native dialog library for Windows MAC OSX GTK+ QT CONSOLE X Wayland
- SSH: automatic switch to console mode / X forwarding / `waypipe`

```cpp
void tinyfd_beep();

int tinyfd_notifyPopup(
    char const * aTitle , // NULL or ""
    char const * aMessage , // NULL or "" may contain \n \t
    char const * aIconType ); // "info" "warning" "error"

int tinyfd_messageBox(
    char const * aTitle ,
    char const * aMessage , 
    char const * aDialogType , // "ok" "okcancel" "yesno" "yesnocancel"
    char const * aIconType ,
    int aDefaultButton );
        // 0 for cancel/no , 1 for ok/yes , 2 for no in yesnocancel

char const * tinyfd_inputBox(
    char const * aTitle , 
    char const * aMessage ,
    char const * aDefaultInput ); // NULL for a passwordBox, "" for an inputbox
        // returns NULL on cancel

char const * tinyfd_saveFileDialog(
    char const * aTitle , 
    char const * aDefaultPathAndOrFile , // NULL or "" , ends with / to set only a directory
    int aNumOfFilterPatterns , // 0 (1 in the following example)
    char const * const * aFilterPatterns , // NULL or char const * lFilterPatterns[1]={"*.txt"};
    char const * aSingleFilterDescription ); // NULL or "text files"
        // returns NULL on cancel

char const * tinyfd_openFileDialog(
    char const * aTitle , 
    char const * aDefaultPathAndOrFile , 
    int aNumOfFilterPatterns ,
    char const * const * aFilterPatterns , 
    char const * aSingleFilterDescription , // NULL or "image files"
    int aAllowMultipleSelects ); // 0
        // in case of multiple files, the separator is |
        // returns NULL on cancel

char const * tinyfd_selectFolderDialog(
    char const * aTitle , 
    char const * aDefaultPath ); // NULL or ""
        // returns NULL on cancel

char const * tinyfd_colorChooser(
    char const * aTitle , 
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
- This is not for iOS nor Android (it works in termux and iSH though).
- File and path names are tested before return, they should be valid.
- Do not use `"` and `'` as the dialogs will be display with a warning instead of the title, message, etc...
- There's one file `FilterPatterns` only, it may contain several patterns.
- If no filter description is provided, the `FilterPatterns` will become the description.
- You can query the type of dialog that will be used (pass `tinyfd_query` as `aTitle`)
- Mutiple selects are not possible in console mode.
- String memory is preallocated statically for all the returned values.
- `tinyfd_forceConsole=1;` at run time, forces dialogs into console mode.
- `tinyfd_allowCursesDialogs=1;` : for `curses` dialogs you must set 

## Note for Windows
- Windows is fully supported from XP to 11 (maybe even older versions)
- On Windows, console mode only make sense for console applications.
- On Windows, console mode is not implemented for wchar_T UTF-16.
- On Windows, for curses dialogs console mode, dialog.exe should be copied [somewhere on your executable path](http://andrear.altervista.org/home/cdialog.php)
- On Windows link against Comdlg32.lib and Ole32.lib (on Windows the no linking claim is a lie).
    - Update 2025-04: actually it's no need to specify linking those library now in CMake/Windows.
- [C# & LUA via dll in this folder of original repo](https://sourceforge.net/p/tinyfiledialogs/code/ci/master/tree/dll_cs_lua_R_fortran_pascal/)

### Build on Windows
- I use CMake to build from VS2022 with C++ projects. It worked as intended
- Untested on other platform as OSX, Linux or BSD, may try WSL though.

### TODO
- Finish the C++ wrapper in `tfd.hpp`. As now there are 2 of the most important wrapped, which is `tfd::openFile` and `tfd::openFolder`.

## Note for OSX/BSD/Linux
- On OSX supported from 10.4 to latest (maybe even older versions)
- On OSX, [the package `dialog` can be installed here](http://macappstore.org/dialog) or [macport](http://macports.org) or [`homebrew`](https://formulae.brew.sh/formula/dialog)
    - `dialog` must be installed to run in `curses` dialogs in console mode.
- On OSX/BSD: it only tries command line calls, so no linking is need.
- On OSX/BSD: you need one of: `applescript, kdialog, zenity, matedialog, shellementary, qarma, yad, python (2 or 3) with tkinter/python-dbus, Xdialog` or `curses dialog`
- In the absence of those it will use `gdialog, gxmessage or whiptail` with a `textinputbox`.
