///*******************************************************************************
///********************  GETCH() & KBKIT()  **************************************
///*******************************************************************************

// getch() and kbhit() implementation for linux

#include "kbhit.h"

static struct termios old_t, new_t;
/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old_t); /* grab old terminal i/o settings */
  new_t = old_t; /* make new settings same as old settings */
  new_t.c_lflag &= ~ICANON; /* disable buffered i/o */
  if(echo){                 /* fixed by Josemars@ifes.edu.br */
    new_t.c_lflag |= ECHO;  /* Reference: https://www.mkssoftware.com/docs/man5/struct_termios.5.asp */
  }else{
    new_t.c_lflag &= ~ECHO;
  }
  ///new_t.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */     Comentei esta linha em 21/04/2021 e não sei porque não havia comentado antes. Mesmo depois de ter feito as mudanças para correção
  tcsetattr(0, TCSANOW, &new_t); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old_t);
}

void set_echo(int echo){    /* included by Josemars@ifes.edu.br */
  tcgetattr(0, &new_t); /* grab terminal i/o settings */
  ///new_t.c_lflag &= ~ICANON; /* disable buffered i/o */
  if(echo){
    new_t.c_lflag |= ECHO;
  }else{
    new_t.c_lflag &= ~ECHO;
  }
  ///new_t.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new_t); /* use these new terminal i/o settings now */
}
/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}

int _kbhit() {

    int bytesWaiting;
    static const int STDIN = 0;

    // Use termios to turn off line buffering
    struct termios termold;
    struct termios term;

    /* grab old terminal i/o settings */
    tcgetattr(STDIN, &term);
    /* make new settings same as old settings */
    termold = term;
    /* disable buffered i/o */
    term.c_lflag &= ~ICANON;
    /* use these new terminal i/o settings now */
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    /* read number of bytes in the buffer */
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    /* use that old terminal i/o settings again */
    tcsetattr(STDIN, TCSANOW, &termold);
    setbuf(stdin, NULL);

    return bytesWaiting;
}

int wait_key(){
    initTermios(0);
    while(!_kbhit()){};
    resetTermios();
    return 0;
}
///*******************************************************************************
///*******************************************************************************
///*******************************************************************************

