#include <xc.h>
#include "commons.h"

void sleep(int miliseconds) {
    for(int i = 0; i < miliseconds; i++) {
        for(int j = 0; j < 100; j++);
    }
}
