## Relation between signed & unsigned

Signed 에서 unsigned로 바꿀경우

<img width="60%" src="https://user-images.githubusercontent.com/86250281/135484202-e9a39f05-14af-494a-828b-aed97ad27910.png"/> 

-1 (예 1111)은 UMAX값으로 바뀌고, TMIN (예 1000)은 TMAX+1로 바뀐다

* Casting surprises
    * unsigned 와 signed의 조합에서 signed 값은 암묵적으로 unsigned로 cast됨

```c
#include <stdio.h>
#include <limits.h>
int main(){

    int x = -1;
    unsigned int y = 214783647; //INT_MAX
    if( x > 0U){  //0을 unsigned로 x도 unsigned로 바꾸면 ? UMAX가 된다
        printf("casting surprise!\n");
    } 
    if( y < -1){ //-1 -> umax로 캐스팅
        printf("casting surprise again!\n");
    }

    return 0;

}
```
Signed 및 unsigned int를 포함하는 표현식: int는 unsigned로 캐스트됨!!!

EX ) W =32

 TMIN=-2147483648 TMAX=2147483647

1. -1 (UMAX로 캐스팅) | 0U | > | Unsigned

2. 2147483647U | -2147483647-1 (TMIN)을 unsigned 캐스팅하면 TMAX+1 | < | unsigned

signed 및 unsigned를 포함하는 표현식: signed는 unsigned로 캐스트됨!!!

# Byte ordering

* big endian -  낮은 주소에 데이터의 높은 바이트 부터 저장하는 방식 (Sun, PPC Mac, Internet)

* little endian - 낮은 주소에 데이터의 낮은 바이트 부터 저장하는 방식 (대부분의 인텔 cpu계열)

    <img width="60%" src="https://user-images.githubusercontent.com/86250281/135486776-060e3af6-7f16-404a-a648-0979242b639b.png"/>

```c
#include <stdio.h>
int main(){
    int x = 15213;
    long y = 0x12345678;
    return 0;
}
```
```
(gdb) b 5
(gdb) r
(gdb) x /1wd &x (32비트 워드단위 10진으로 보기)
0x7fffffffe554: 15213
(gdb) x /1wt &x (32비트 워드단위 2진으로 보기)
0x7fffffffe554: 00000000000000000011101101101101
(gdb) x /1wx &x (32비트 워드단위 16진으로 보기)
0x7fffffffe554: 0x00003b6d
(gdb) x /4bt &x (4개의 바이트 단위로 보기)
0x7fffffffe554: 01101101 00111011 00000000 00000000
(gdb) x /4bx &x
0x7fffffffe554: 0x6d 0x3b 0x00 0x00
(gdb) x /4bd &x
0x7fffffffe554: 109 59 0 0
```
```
(gdb) x /8bt &y
0x7fffffffe558: 01111000 01010110 00110100 00010010
00000000 00000000 00000000 00000000
(gdb) x /8bx &y
0x7fffffffe558: 0x78 0x56 0x34 0x12 0x00
0x00 0x00 0x00
(gdb) x /8bd &y
0x7fffffffe558: 120 86 52 18 0
0 0 0
(gdb) x /2wx &y
0x7fffffffe558: 0x12345678 0x00000000
(gdb) x /1gx &y
0x7fffffffe558: 0x0000000012345678
```
참고
```
<GDB x command format>
The size modifiers are supported:
b - byte
h - halfword (16-bit value)
w - word (32-bit value)
g - giant word (64-bit value)
Valid format specifiers are:
t - binary
x - hexadecimal
d - decimal
o - octal
u - unsigned decimal
f - floating point
a - address
c - char
s - string
i - instruction
```
## Expanding the bit representation of a number 

어떤 16비트 수가 32비트로 늘어났을때

양수-> 나머지 0으로 채워주기, 음수 -> 나머지 1로 채워주기

줄어들면? 그냥 잘라버림

## 2의 보수 negation

* TMIN은 스페셜 케이스

```C
#include <stdio.h>
#include <limits.h>
int main(){
    int x = 1;
    int y = INT_MIN; //(TMIN)
    printf("%#x \n", y); //0x8000 0000
    printf("%#x \n", ~y);
    printf("%#x \n", ~y+1); //0x8000 0000 (값 동일하게 출력)
    if(y < 1 && y-1 >=0){ // tmin-1 => tmax (오버플로우)
        printf("surprise %d \n", y-1);
    }
    if(y < 0 && -y <= 0){ // (-TMIN=TMIN : TRUE)
        printf("surprise %d \n", -y);
    }
    if( x > y && x-y <= 0){
        printf("surprise %d \n", x-y);
    }
    return 0;
```

* 2의 보수 덧셈에서 양수+양수 ->음수 (오버플로우)

    음수+음수->양수 (오버플로우) 발생
    
    <img width="60%" src="https://user-images.githubusercontent.com/86250281/135569222-d16821c9-7a3f-4b77-b076-0f1f7b62692f.png"/>