#include "func_change.h"

const char *filename = "input.txt";

// input.txt에 있는 파일을 읽고 구조체 배열에 값을 넣어주는 함수 입니다.
void getGIS(struct coordinate *a, struct coordinate *b)
{
    printf("*************input**************\n");
    FILE *fp = fopen(filename, "r");
    int cur = 0;
    while (!feof(fp))
    {
        fscanf(fp, "(%d%c, %d%c) (%d%c, %d%c) \n",
               &a[cur].longitude.dms, &a[cur].longitude.direction,
               &a[cur].latitude.dms, &a[cur].latitude.direction,
               &b[cur].longitude.dms, &b[cur].longitude.direction,
               &b[cur].latitude.dms, &b[cur].latitude.direction);

        cur++;
    }
    // 내용이 잘 들어왔는지 확인해줍니다
    for (int i = 0; i < 10; i++)
    {
        fprintf(stdout, "(%d%c, %d%c) (%d%c, %d%c) \n",
                a[i].longitude.dms, a[i].longitude.direction,
                a[i].latitude.dms, a[i].latitude.direction,
                b[i].longitude.dms, b[i].longitude.direction,
                b[i].latitude.dms, b[i].latitude.direction);
    }
    fclose(fp);
    //return cur;
}

// 저장된 데이터 값을 요구사항에 적절하게 바꿔주는 함수 입니다.
void printGIS(struct coordinate *a, struct coordinate *b)
{
    // 각각의 d,m,s를 저장해줄 배열을 선언
    int longDeg1[10];
    int longMin1[10];
    int longSec1[10];

    int latDeg1[10];
    int latMin1[10];
    int latSec1[10];

    int longDeg2[10];
    int longMin2[10];
    int longSec2[10];

    int latDeg2[10];
    int latMin2[10];
    int latSec2[10];

    // first coordinate에 대한 d,m,s값 계산
    for (int i = 0; i < 10; i++)
    {
        longDeg1[i] = a[i].longitude.dms / 10000;
        longMin1[i] = (a[i].longitude.dms % 10000) / 100;
        longSec1[i] = a[i].longitude.dms % 10000 % 100;

        latDeg1[i] = a[i].latitude.dms / 10000;
        latMin1[i] = (a[i].latitude.dms % 10000) / 100;
        latSec1[i] = a[i].latitude.dms % 10000 % 100;
    }
    // second coordinate에 대한 d,m,s값 계산
    for (int l = 0; l < 10; l++)
    {
        longDeg2[l] = b[l].longitude.dms / 10000;
        longMin2[l] = (b[l].longitude.dms % 10000) / 100;
        longSec2[l] = b[l].longitude.dms % 10000 % 100;

        latDeg2[l] = b[l].latitude.dms / 10000;
        latMin2[l] = (b[l].latitude.dms % 10000) / 100;
        latSec2[l] = b[l].latitude.dms % 10000 % 100;
    }

    //total distance 계산
    for (int k = 0; k < 10; k++)
    {
        int firstSeconds, secondSeconds;

        firstSeconds = abs((longDeg1[k] * 3600 + longMin1[k] * 60 + longSec1[k]) -
                           (longDeg2[k] * 3600 + longMin2[k] * 60 + longSec2[k]));
        secondSeconds = abs((latDeg1[k] * 3600 + latMin1[k] * 60 + latSec1[k]) -
                            (latDeg2[k] * 3600 + latMin2[k] * 60 + latSec2[k]));
        //따로 배열을 선언하여 total 값을 넣어주었습니다
        totalSeconds[k] = firstSeconds + secondSeconds;
    }

    //최종적으로 요구사항에 맞게 출력해주는 for문
    printf("**********output***********\n");
    for (int j = 0; j < 10; j++)
    {
        printf("(%dd %02dm %02ds %c, %dd %02dm %02ds %c) (%dd %02dm %02ds %c, %dd %02dm %02ds %c) %06d 000d %02dm %02ds\n",
               longDeg1[j], longMin1[j], longSec1[j], a[j].longitude.direction, latDeg1[j], latMin1[j],
               latSec1[j], a[j].latitude.direction, longDeg2[j], longMin2[j], longSec2[j],
               b[j].longitude.direction, latDeg2[j], latMin2[j], latSec2[j], b[j].latitude.direction,
               totalSeconds[j], totalSeconds[j] / 60, totalSeconds[j] % 60);
    }
    /* for debuging
    for(int i=0; i<10; i++){
        printf("%c %c %c %c\n", a[i].longitude.direction, a[i].latitude.direction, b[i].longitude.direction, b[i].latitude.direction);
    }
    */
}