# Bits, Bytes, Integers

# Bits and Bytes

정보 저장 최소 단위 - bits

* bit patterns- 하나의 메모리 접근 단위 

* 8bits = 1byte , 비트 패턴은 encoding/interpreting sets에서 다양한 방법있음

* 컴퓨터 메모리는 bytes의 큰 배열(byte-addressable)

*** 

* Unsigned Integers - 숫자의 양수만 표현 가능한 값 (부호를 가질 수 없어, 양수인지 음수인지 구분 X)

* Signed Integers - 숫자의 양수, 음수 전부 표현 가능한 값 (부호를 가질 수 있어, 양수인지 음수인지 구분 O), C언어에서 디

음,양의 정수를 이진수로 어떻게 표현 할까?

* Sign Maginitude representation

<img width="60%" src="https://user-images.githubusercontent.com/86250281/134908121-ffa53a97-f3f5-4a70-91fd-3a46cac8238c.png"/>

* 문제 : 0이 두개 되는 경우 발생, 계산상의 비효율성

## two's complement Representation

C=2^w - x = (2^w - 1)- x + 1 = ~x + 1

만약 숫자가 양수, 0 이면 -> 일반 이진표현,
음수이면 ?
* 일단 양의 정수로 시작
* 모든 비트 flip
* 1 더하기

ex) -5 -> 0000 0101 (+5)

-> 1111 1010 (flip)

-> 1111 1011 (1 더하기)

* 다른 trick -> 오른쪽에서 1이 나오면 멈추고  그 부분 copy, 나머지만 flip하자 -> 2의 보수

    <img width="50%" src="https://user-images.githubusercontent.com/86250281/134925746-89a8e611-836a-4381-bb48-3190c576dd44.png"/>

***
## typical integer representation

* 원래 number 사이즈는 h/w에 depend함, 컴파일러에 의해 변할 수 있었다

<img width="60%" src="https://user-images.githubusercontent.com/86250281/134926716-e5cd2a42-d204-4703-985e-78d65c7257cf.png"/> 

정확히 사이즈화된 독립적인 integer 데이터 타입 

### printf and integers

* %d : signed 32-bit int
* %u : unsigned 32-bit int
* %x : hex 32-bit int // %#0 (0x 자동으로 붙여줌)

## Overflow

정수형의 크기는 고정되어 있는데 정수형이 저장할 수 있는 값의 크기보다 큰 값을 저장하려 할 때 발생하는 예상치 않은 문제

<img width="50%" src="https://user-images.githubusercontent.com/86250281/134928873-bae42543-2433-4395-b429-49fee89c3ab4.png"/>

TMAX에서 1 더해지면 TMIN으로 (싸이클같음)

```C
예시 코드
#include <stdio.h>
#include <limits.h>

int main() {
    
    short s_money = SHRT_MAX; // 32767
    unsigned short u_money = USHRT_MAX; // 65535
    
    s_money = s_money + 1;
    printf("s_money = %d", s_money); // sign 정수 max 값에서 1을 더하면 -(32767 + 1) 화 됌 -> -32768 출력

    u_money = u_money + 2;
    printf("u_money = %d", u_money); // unsigned 정수 max 값에서 +2 한경우 (UMAX에서 2칸) -> 1출력
    
    return 0;
}
```

## Casting (형변환)

* 확실한 캐스팅 방법 예
```
int tx, ty;
unsigned ux, uy;
tx = (int) ux;
uy = (unsigned) ty;
```
* 암묵적 캐스팅
```
tx = ux;
uy = ty;
```

```c
#include <stdio.h>

    int main(void){
        int v = -1;
        unsigned int uv = (unsigned int) v;
        printf("v = %d, uv = %u\n", v, uv);
        printf("v = %#x, uv = %#x\n", v, uv);
        return 0;
    }

    //출력
    //v = -1, uv = 4294967295
    //v = 0xffffffff, uv = 0xffffffff
```

메모리상의 비트패턴은 변하지 않고, 해석만 달라지는것을 알 수 있다
