#include "ui/commandReader.h"

#include <signal.h>
#include <unistd.h>

int main(void) {  
    struct sigaction act = {.sa_handler = SIG_IGN};;
    sigaction(SIGINT, &act, NULL);

    init_commandReader();
    
    while(1) {
        read_commandLine();
    }

    return 0;
}
