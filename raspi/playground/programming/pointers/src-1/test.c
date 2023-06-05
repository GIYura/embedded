/*
Exploring how to pass pointers to functions
*/
#include <stdio.h>

#define BUFF_MAX 10

static void decompode(double x, long* iPart, double* fPart);
static void minMax(int buff[], int size, int* min, int* max);
static void swap(int* a, int* b);
static void avgSum(int* buff, unsigned int buffSize, double* avg, double* sum);
static int* findLargest(int* buff, unsigned int size);

int main(int argc, char* argv[])
{
/*
Decompose double on int and fractional
*/
    long i = 0;
    double d = 0;

    decompode(3.14159, &i, &d);
    printf("Int part: %ld\n", i);
    printf("Dec part: %.4f\n", d);

/*
Enter buffer and find min / max
*/
    int buff[BUFF_MAX];
    int max, min;
    printf("Enter %d numbers\n", BUFF_MAX);
    for (int i = 0; i < BUFF_MAX; i++)
    {
        scanf("%d", &buff[i]);
    }
    minMax(buff, BUFF_MAX, &min, &max);
    printf("MAX: %d\n", max);
    printf("MIN: %d\n", min);

/*
Swap two int values
*/
    int a = 1000;
    int b = 2000;
    printf("a: %d\n", a);
    printf("b: %d\n", b);

    swap(&a, &b);

    printf("a: %d\n", a);
    printf("b: %d\n", b);

/*
Calculate buffer avg and largest
*/
    int buffer[10] = {1,2,3,4,5,6,7,8,9};
    double avg, sum;
    avgSum(buffer, 10, &avg, &sum);
    printf("Avg: %.2f\n", avg);
    printf("Sum: %.2f\n", sum);

/*
Find largest item in the buffer by returning pointer
*/
    int BUFFER[10] = {100,221,-3,4,0,6,555,8,88};
    int* l = findLargest(BUFFER, 10);
    printf("Largest: %d\n", *l);
/**/

    return 0;
}

static void decompode(double x, long* iPart, double* fPart)
{
    *iPart = (long)x;
    *fPart = x - *iPart;
}

static void minMax(int buff[], int size, int* min, int* max)
{
    *min = *max = buff[0];

    for (int i = 1; i < size; i++)
    {
        if (buff[i] > *max)
        {
            *max = buff[i];
        }
        else if (buff[i] < *min)
        {
            *min = buff[i];
        }
    }
}

static void swap(int* a, int* b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

static void avgSum(int* buff, unsigned int buffSize, double* avg, double* sum)
{
    if (buffSize == 0)
    {
        return;
    }   

    for (int i = 0; i < buffSize; i++)
    {
        *sum += *(buff + i);
    }
    *avg = *sum / buffSize;
}

static int* findLargest(int* buff, unsigned int size)
{
    int i, j;
    int largest = *buff;

    for(i = 1; i < size; i++)
    {
        if (*(buff + i) > largest)
        {
            largest = *(buff + i);
            j = i;
        }
    }
/*
Equvalent:
    return &buff[j];
*/
    return (buff + j);
}

