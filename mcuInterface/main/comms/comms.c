#include "comms.h"
#include <stdio.h>

void comms_send(const float filtered[]){
    printf("Filtered data:\n");
    for(int i=0; i<DAQ_TOTAL_SENSORS; i++){
        printf("%7.2f ", filtered[i]);
        if((i%16)==15) printf("\n");
    }
    printf("\n\n");
}
