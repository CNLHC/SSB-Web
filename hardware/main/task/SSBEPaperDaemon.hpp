extern int globalFSM;
#include "../ssb/SSBEPaper.hpp"

static void ThSSBEPaperDaemon(void *arg);
static void ThSSBEPaperDaemon(void *arg)
{
    int previousState=0;
    int count=0;


    while (1)
    {
        switch (globalFSM)
        {
        case 0:
            break;
        case 1:
            EPaperReady();
            break;
        case 2:
            EPaperShopping();
            break;
        }
        vTaskDelay(500);
    }
}