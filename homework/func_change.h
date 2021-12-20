#include <stdio.h>
#include <stdlib.h>

int totalSeconds[10];

struct gisinfo
{
    int degree;
    int minute;
    int second;
    int totalSec;
    int dms;
    char direction;
};
struct coordinate
{
    struct gisinfo longitude;
    struct gisinfo latitude;
} a, b;

void getGIS(struct coordinate *a, struct coordinate *b);
void printGIS(struct coordinate *a, struct coordinate *b);