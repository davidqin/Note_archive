#include "../unp.h"
#include <syslog.h>

int deamon_proc;
static void err_doit(int, int, const char *, va_list);

void err_quit(const char * fmt, ...){
  va_list ap;
  va_start(ap, fmt);
  err_doit(0, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(1);
}

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap){
  int errno_save, n;
  char buf[MAXLINE + 1];

  //errno_save = errno;
  n = strlen(buf); 
#ifdef HAVE_VSNPRINTF
  vsnprintf(buf, MAXLINE, fmt, ap);
#else
  vsprintf(buf, fmt, ap);
#endif

  fflush(stdout);
  fputs(buf, stderr);
  fflush(stderr);
}
