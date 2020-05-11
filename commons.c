#include <xc.h>
#include "commons.h"

void sleep(int miliseconds) {
    int i, j;
    for(i=0; i<miliseconds; i++) {
        for(j=0; j<100;j++);
    }
}
