#include "mem.h"
#include "errlib.h"

#include <signal.h>

static void
sigquitHandle(int sig)
{
    printf("\nCaught SIGQUIT... Exiting\n");
    exit(EXIT_SUCCESS);
}

static void
sigHandler(int sig)
{
    static int count = 0;

    if (sig == SIGINT) {
        count++;
        printf("\nCaught SIGINT (%d) Please use ctrl-\\ to exit\n", count);
        return;
    }

    if(sig == SIGQUIT) {
        if(signal(SIGQUIT, sigquitHandle) == SIG_ERR)
            errnoExit("signal");
        if(raise(SIGQUIT) < 0)
            errnoExit("raise");
    }
}

int
main(const int argc, const char *argv[])
{
    if(signal(SIGINT, sigHandler) == SIG_ERR)
        errnoExit("signal");
    if(signal(SIGQUIT, sigHandler) == SIG_ERR)
        errnoExit("signal");
    
    for(;;)
        pause();

    exit(EXIT_SUCCESS);
}