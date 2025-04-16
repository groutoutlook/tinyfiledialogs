/* not cross platform - unix zenity only */
#ifndef _WIN32
char * tinyfd_arrayDialog(
	char const * aTitle , /* NULL or "" */
	int aNumOfColumns , /* 2 */
	char const * const * aColumns, /* {"Column 1","Column 2"} */
	int aNumOfRows, /* 2 */
	char const * const * aCells);
		/* {"Row1 Col1","Row1 Col2","Row2 Col1","Row2 Col2"} */
#endif /*_WIN32 */
/* not cross platform - UNIX and OSX only */
#ifndef _WIN32
char * tinyfd_checklistDialog(
    char const * aTitle ,
    int aNumOfOptions ,
    char const * const * aOptions);
#endif /*_WIN32 */
