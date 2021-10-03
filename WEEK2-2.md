# Advanced C programming

## Separte Compile

C 프로그램이 하나의 파일로 되있다면? -> 컴파일 어렵, 관리 힘듬 -> 다수의 파일로 나눠서 관리하자!

(modules : 함수와 데이터의 컬렉션)

* 코드와 협동을 재사용 가능
* 다른 모듈들의 세부 사항에대해 걱정 안해도 됨
* 개발 더 빨리 가능
* 다른 파일을 다시 컴파일할 필요 x

***

1. Just divide 

```
int x;
x = 0;          a.c
---------------
x++;            b.c
---------------
x--;            c.c
```
x 정의 안되있음 -> 컴파일 에러

2. Insert int x; 
```
int x;
x = 0;            a.c
-------------
int x;
x++;            b.c
-------------
int x;
x--;            c.c
```
Linking 할때 변수 중복 -> 컴파일 에러

3. extern:
```
int x;
x = 0;          a.c
------------
extern int x;
x++;            b.c
------------
extern int x;
x--;            c.c
```
extern : 컴파일러에게 언젠간 나오니까 일단 ㄱㄷ
(단지 선언만 되고 정의는 안됨)

linking 하면 int x 정의 완료 되고 외부변수 해결됨 -> 실행가능한 binary파일

만약 int x를 char로 바꾸고 싶다면? -> 일일이 다찾아야되고 다 바꿔줘야함(매우 불편)
so, 헤더파일의 필요성

<img width="70%" src="https://user-images.githubusercontent.com/86250281/132695395-ca19d527-5c05-4413-addd-7a890c9c19bf.png"/>

자동으로 전처리기에서 int x 업데이트

char로 바꾸고싶다? 헤더만 바꿔주면 됨

## Headers

The header (모듈 사이에 공유할 정보 가짐)

* extern 변수
* 모든 함수의 정의
* 공통 상수 및 구조
* 주석도 포함

### Multiple inclusion problem
```C
// main.c
#include "A.h"
#include "B.h"
```
```c
//A.h
#include "B.h"
extern int x = 0;
```
```c
//B.h
const double PI = 3.14;
```
컴파일 할 경우 PI 변수 두번 정의 되는 에러
```c
//B.h
#ifndef B_H
#define B_H
const double PI = 3.14;
...
#endif
```
이런 방식으로 해결가능 (코딩 할때 의무적으로 하는 것이 좋다)

* Library 의 필요성
    
    disk의 속도 매우 느리기 때문에, 자주 사용하는 object코드 따로 그룹화 해서 저장 (ex. printf(), scanf()....)

## Scope and Class
* Local variable (지역 변수)

    block({})이 시작되면 자동으로 생성, block 끝나면 끝남 (stack영역에 자동생성, 소멸)
    * scope : block 내에서 정의 접근 가능
    * Storage duration : dynamic (일시적으로 필요할 떄만)
    * Linkage : x (함수하나에 제한)

* Global variable (전역 변수)

    프로그램 끝날 때 까지 유지
    * scope : file
    * storage duration : static (실행전에 만들어 놓음) 
    * Linkage : external 이거나 Internal(다른 파일에서는 접근 x)

## Static Modifier
사용 법에 따라 두가지 의미 가짐

1. 지역변수 앞에 static 쓴 경우
    
    마지막에 할당된 값 block이 끝나더라도 그대로 유지 (마치 전역 변수 처럼 동작)

    <img width="70%" src="https://user-images.githubusercontent.com/86250281/132701040-3da9a140-da8a-40d6-aa1f-b037b652a8b6.png"/>
    <img width="70%" src="https://user-images.githubusercontent.com/86250281/132701141-ee8f8788-be2e-48f5-bd49-b136f221beac.png"/>

    예시 코드

2. 전역변수 앞에 static 쓴 경우

    공유금지, 해당 파일에서만 사용 (private)

    <img width="70%" src="https://user-images.githubusercontent.com/86250281/132701942-28e3a5e1-a4bc-4ff3-8b28-a855dcbc8e83.png"/>
    <img width="70%" src="https://user-images.githubusercontent.com/86250281/132702017-fc7f9e5d-31e9-49c5-b51c-d776165ee58e.png"/>
    <img width="70%" src="https://user-images.githubusercontent.com/86250281/132702109-0a4b1670-15d2-4ebe-9a32-c18c6740aacd.png"/>

    예시 코드

    ## Extern Modifier

    외부파일에 자유롭게 변수 share 가능
    <img width="80%" src="https://user-images.githubusercontent.com/86250281/132702677-bb7ec0b1-f624-4f87-a31a-01397b2be088.png"/>



    ## Example Code
```c
//test1.c
#include <stdio.h>
extern int x;
void useLocal( void )
{
int x = 25;
printf( "\nlocal x in useLocal is %d after entering useLocal\n", x );
x++;
printf( "local x in useLocal is %d before exiting useLocal\n", x );
}
void useStaticLocal( void )
{
/* initialized only first time useStaticLocal is called */
static int x = 50;
printf( "\nlocal static x is %d on entering useStaticLocal\n", x );
x++;
printf( "local static x is %d on exiting useStaticLocal\n", x );
}
void useGlobal( void )
{
printf( "\nglobal x is %d on entering useGlobal\n", x );
x *= 10;
printf( "global x is %d on exiting useGlobal\n", x );
}

int main( void )
{
int x = 5;
printf("local x in outer scope of main is %d\n", x );
{
int x = 7;
printf( "local x in inner scope of main is %d\n", x );
}
printf( "local x in outer scope of main is %d\n", x );
useLocal();
useStaticLocal();
useGlobal();
useLocal();
useStaticLocal();
useGlobal();
printf( "\nlocal x in main is %d\n", x );
return 0;
}
```
```c
//test2.c
int x = 1;
```
<img width="80%" src="https://user-images.githubusercontent.com/86250281/132704581-eac9306f-004b-44bc-9738-b1689f71ed40.png"/>
