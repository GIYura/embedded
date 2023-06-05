#include <stdio.h>
#include <string.h>
#include "buffer.h"

#define BUFF_SIZE 10

typedef struct
{
    char brand[20];
    int mileage;
} Car_t;

static Car_t cars[BUFF_SIZE + 1];
char brands[][10] = { "VW", "BMW", "AUDI", "MERSEDES", "SKODA" };

int main(int argc, char* argv[])
{
    RingInit(cars, sizeof(Car_t), sizeof(cars) / sizeof(cars[0]));
    
    Car_t car;

    for (int i = 0; i < 1000; i++)
    {
        char brand[10];
        int j = 0;
        int x = 0;
        while (brands[i][j] != '\0')
        {
            brand[x++] = brands[i][j++];
        } 
        brand[x] = '\0';

        memcpy(car.brand, brand, 10);
        car.mileage = (i + 1) * 100;
        if (!RingEnqueue(&car, sizeof(Car_t)))
            break;
    }

    memset(&car, 0, sizeof(Car_t));
    
    for (int i = 0; i < 1000; i++)
    {
        if (!RingDequeue(&car, sizeof(Car_t)))
            break;
        
        printf("Brand: %s\t", car.brand);
        printf("Mileage: %d miles\n", car.mileage);
    }

    return 0;
}
