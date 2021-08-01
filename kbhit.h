///*******************************************************************************
///********************  GETCH() & KBKIT()  **************************************
///*******************************************************************************

// getch() and kbhit() implementation for linux

#include <termios.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <sys/select.h>
//#include <stropts.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

/* Initialize new terminal i/o settings */
void initTermios(int echo);

/* Restore old terminal i/o settings */
void resetTermios(void);

/* Set or Reset echo */
void set_echo(int echo);

/* Read 1 character - echo defines echo mode */
char getch_(int echo);

/* Read 1 character without echo */
char getch(void);

/* Read 1 character with echo */
char getche(void);

int _kbhit();

int wait_key();

#ifdef __cplusplus
}
#endif

///*******************************************************************************
///*******************************************************************************
///*******************************************************************************

