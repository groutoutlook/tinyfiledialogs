#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"

int main( int argc , char * argv[] )
{
	int lIntValue;
	char * lPassword;
	char * lTheSaveFileName;
	char * lTheOpenFileName;
	char * lTheSelectFolderName;
	char * lTheHexColor;
	char * lWillBeGraphicMode;
	unsigned char lRgbColor[3];
	FILE * lIn;
	char lBuffer[1024];
	char const * lFilterPatterns[2] = { "*.txt", "*.text" };

	(void)argv; /*to silence stupid visual studio warning*/

	tinyfd_verbose = argc - 1;  /* default is 0 */
	tinyfd_silent = 1;  /* default is 1 */

	tinyfd_forceConsole = 0; /* default is 0 */
	/* tinyfd_assumeGraphicDisplay = 0; */ /* default is 0 */

#ifdef _WIN32
	 tinyfd_winUtf8 = 1; /* default is 1 */
/* On windows, you decide if char holds 1:UTF-8(default) or 0:MBCS */
/* Windows is not ready to handle UTF-8 as many char functions like fopen() expect MBCS filenames.*/
/* This hello.c file has been prepared, on windows, to convert the filenames from UTF-8 to UTF-16
   and pass them passed to _wfopen() instead of fopen() */
#endif

	tinyfd_beep();

	lWillBeGraphicMode = tinyfd_inputBox("tinyfd_query", NULL, NULL);

	strcpy(lBuffer, "tinyfiledialogs\nv");
	strcat(lBuffer, tinyfd_version);
	if (lWillBeGraphicMode)
	{
		strcat(lBuffer, "\ngraphic mode: ");
	}
	else
	{
		strcat(lBuffer, "\nconsole mode: ");
	}
	strcat(lBuffer, tinyfd_response);
	tinyfd_messageBox("hello", lBuffer, "ok", "info", 0);

	tinyfd_notifyPopup("the title", "the message\n\tfrom outer-space", "info");

	if ( lWillBeGraphicMode && ! tinyfd_forceConsole )
	{
#if 0
		lIntValue = tinyfd_messageBox("Hello World", "\
graphic dialogs [Yes]\n\
console mode [No]\n\
quit [Cancel]",
			"yesnocancel", "question", 1);
		if (!lIntValue) return 1;
		tinyfd_forceConsole = (lIntValue == 2);
#else
		lIntValue = tinyfd_messageBox(
			"Hello World", "graphic dialogs [Yes] / console mode [No]",
			"yesno", "question", 1);
		tinyfd_forceConsole = ! lIntValue;
#endif
	}

	lPassword = tinyfd_inputBox(
		"a password box", "your password will be revealed later", NULL);

	if (!lPassword) return 1;

	tinyfd_messageBox("your password as read", lPassword, "ok", "info", 1);

	lTheSaveFileName = tinyfd_saveFileDialog(
		"let us save this password",
		"./passwordFile.txt",
		2,
		lFilterPatterns,
		NULL);

	if (! lTheSaveFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Save file name is NULL",
			"ok",
			"error",
			1);
		return 1 ;
	}

#ifdef _WIN32
	if (tinyfd_winUtf8)
		lIn = _wfopen(tinyfd_utf8to16(lTheSaveFileName), L"w"); /* the UTF-8 filename is converted to UTF-16 to open the file*/
	else
#endif
	lIn = fopen(lTheSaveFileName, "w");

	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in write mode",
			"ok",
			"error",
			1);
		return 1 ;
	}
	fputs(lPassword, lIn);
	fclose(lIn);

	lTheOpenFileName = tinyfd_openFileDialog(
		"let us read the password back",
		"../",
		2,
		lFilterPatterns,
		"text files",
		1);

	if (! lTheOpenFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Open file name is NULL",
			"ok",
			"error",
			0);
		return 1 ;
	}

#ifdef _WIN32
	if (tinyfd_winUtf8)
		lIn = _wfopen(tinyfd_utf8to16(lTheOpenFileName), L"r"); /* the UTF-8 filename is converted to UTF-16 */
	else
#endif
	lIn = fopen(lTheOpenFileName, "r");

	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in read mode",
			"ok",
			"error",
			1);
		return(1);
	}

	lBuffer[0] = '\0';
	fgets(lBuffer, sizeof(lBuffer), lIn);
	fclose(lIn);

	tinyfd_messageBox("your password as it was saved", lBuffer, "ok", "info", 1);

	lTheSelectFolderName = tinyfd_selectFolderDialog(
		"let us just select a directory", "../../");

	if (!lTheSelectFolderName)
	{
		tinyfd_messageBox(
			"Error",
			"Select folder name is NULL",
			"ok",
			"error",
			1);
		return 1;
	}

	tinyfd_messageBox("The selected folder is", lTheSelectFolderName, "ok", "info", 1);

	lTheHexColor = tinyfd_colorChooser(
		"choose a nice color",
		"#FF0077",
		lRgbColor,
		lRgbColor);

	if (!lTheHexColor)
	{
		tinyfd_messageBox(
			"Error",
			"hexcolor is NULL",
			"ok",
			"error",
			1);
		return 1;
	}

	tinyfd_messageBox("The selected hexcolor is", lTheHexColor, "ok", "info", 1);

	tinyfd_messageBox("your read password was", lPassword, "ok", "info", 1);

	return 0;
}
