## Multiplication

<img width="60%" src="https://user-images.githubusercontent.com/86250281/136644158-a6652b50-0642-4abe-9fbf-99a0960a361e.png"/>add와 shift로 구현가능

u << k 연산은 u * 2^k와 동일

* u << 3 == u * 8
* (u << 5) - (u << 3) == u * 24
* shift와 add연산은 곱셈보다 빠른수행속도 가짐

## Division

shift와 substract 연산으로 구현가능

* x >> k == x / 2^k

<img width="50%" src="https://user-images.githubusercontent.com/86250281/136644353-36eaf90c-c33e-4540-a427-0f9b4605a22e.png"/><img width="50%" src="https://user-images.githubusercontent.com/86250281/136644359-6b9b8a71-21bd-43c6-85b8-7a6fde6fde01.png"/>

음수의 경우 0에 가까운수 나와야하는데 그렇지않은 문제 발생

* (x + (1 << k)-1) >> k 로 계산하기

따라서 x / 2^k 일때 실제로는 (x < 0 ? x+ (1 << k) -1 : x) >> k  이렇게 동작

```c
#include <stdio.h>
#include <limits.h>
Int main(){
    int x;
    int y;
    x = 1;
    y = 2147483647; //INT_MAX
    if(x + y < 0 ){ // tmax + 1 -> tmin
        printf(“surprise %d \n”, x + y);
    }
    x = 50000;
    if(x*x <= 0 ){ // 25 * 10^8 (오버플로우 발생)
        printf(“surprise %d \n”, x*x);
    }
    x = -2147483648; //INT_MIN
    if(2*x >= 0 ){ // tmin * 2 => 1000 0000 ... (왼쪽으로 1bit shift) => 0000 0000...
        printf("surprise %d \n", 2*x);
    }
    return 0;
}
```
```
surprise -2147483648
surprise -1794967296
surprise 0
```

# Floating Point

매우 크거나 작은수 담기 가능

* Very small numbers (e.g. 1.0 × 10^–9)
* Very large numbers (e.g. 8.64 × 10^13)

## fixed point representation

3.4375를 이진수로 고치려면? 정수부분은 정상적으로 2진수로 바꿔준다

소수부분은?
1. 0.4875 * 2 = 0 + 0.875
2. 0.875 * 2 = 1 + 0.75
3. 0.75 * 2 = 1 + 0.5
4. 0.5 * 2 = 1 + 0

->11.0111(2)

한계

1. 정확히 표현할수 없는 수가 존재한다 (ex 1/3, 1/5, 1/10....)
2. 표현할수 있는 숫자의 범위 제한적

## IEEE Floating Point

* Sign bit S : 양수인지 음수인지 알려주는 bit
* Manstissa M : 1.xxxx (Frac)
* Exponent Exp : E = e - bias
<img width="60%" src="https://user-images.githubusercontent.com/86250281/136644937-9df42bfd-4bff-40b5-bd94-2b1b287fc52b.png"/>

* Single Precision (32bits)
    * 1-bit sign + 8-bit exponent + 23-bit fraction
* Double Precision (64bits)
    * 1-bit sign + 11-bit exponent + 52-bit fraction

* biased 값은
    * single 에선 127
    * double 에선 1023

ex1) 1.0

1.0=1.0(2) X 2^0 (S:0, M=1.0, E=0)

E = Exp - 127 =0 이므로 Exp=127 

따라서 0(s) 01111111(Exp) 0000000000 0000000000 000(frac)

ex2) 2.75

2.75=10.11(2) => 1.011 * 2^1 (S:0, M=1.011, E=1)

E= Exp - 127 = 1이므로 Exp = 128

따라서 0(s) 10000000(exp) 0110000000 0000000000 000(frac)

ex3) 3.14

3.14 = 11.0010 0011 1101 0111 0000 1010(2)=> 1.1001 0001 1110 1011 1000 0101 02 x 2^1 (S:0, M:1.1001..... E=1)

E=Exp -127 =1 이므로 Exp =128

따라서 0(s) 10000000(Exp) 1001 0001 1110 1011 1000 010(Frac)

ex4) 15213

15213= 11101101101101(2) => 1.1101 1011 0110 1 * 2^13 (S:0, M:1.11011011.... E: 13)

E = Exp -127 = 13이므로 Exp = 140

따라서 0(s) 10001100(exp) 11011011011010000000000(frac)

* double precision -> 10진수로 바꾸기

    0 10000000101 0010101000000000000000000000000000000000000000000000

    10000000101 => 1029이므로 1029 - 1023 = 6, E=6임

    => frac부분은 1.001010101......으로 바꾸고 최종적으로 1.00101101.. x 2^6으로 표현가능 => 1001010.10(2) => 74.5

## Largest Normalized value
* single precision

    0 11111110 11111111111111111111111

    Exponent=254-127 = 127
    frac=1.11111....(2)= 1-2^-23 = 1-ε

    따라서 -1^0 * 2^127 * (2-ε : 거의 2에 수렴) = 2 × 2^127 ≈ 2^128 ≈ 3.4028 … × 10^38

* double precision

    0 11111111110 11111111111111111111
    11111111111111111111111111111111

    Exponent= 2046-1023 = 1023
    frac=1.1111111..(2) = 1-2^-52 = 1-ε

    따라서 -1^0 * 2^1023 * (2-ε : 거의 2에 수렴) = 2 × 2^1023 ≈ 2^1024 ≈ 1.79769 … × 10^308

## Smallest Normalized Value

* single precision

    0 00000001 00000000000000000000000

    Exponent – bias = 1 – 127 = –126
    
    따라서 1 × 2^–126 = 1.17549 … × 10^–38

* double precision

    0 00000000001 00000000000000000000
    00000000000000000000000000000000

    Exponent – bias = 1 – 1023 = –1022

    따라서 1 × 2^–1022 = 2.22507 … × 10^–308

## denormalized values

exp가 모두 0일때 조건 만족

M은 그냥 M=0.xxxx으로 계산해라 (E= 1- bias로 계산하기 (E= 0- bias로 하지 않기))

### special values

exp가 모두 1일때 조건 만족

* infinity (frac=0000...)
* NaN (frac!=0000...)

## Floating Point Addition

(1.111)2 × 2^–1 + (1.011)2 × 2^–3

* 지수 큰부분 작은쪽으로 맞춰주기
* (1.011) × 2^–3 = (0.1011) × 2^–2 = (0.01011) × 2^–1
* (1.111) × 2^–1 + (1.011) × 2^–3 = (10.00111) × 2^–1
* 정규화 시켜주기 : (10.00111) × 2^–1 = (1.000111) × 2^0
* frac 3bits라고 가정했으므로,  (1.000111) ≈ (1.001)

## Floating Point Multiplication

1.010 × 2^–1 * –1.110 × 2^–2

* E = -1+-2=-3
* 양수*음수이므로 s=1
* 1.010 × 2^–1 × –1.110 × 2^–2 = –10. 001100 × 2^–3
* 정규화 해주기 : 10. 001100 × 2^–3 = 1.0001100 × 2^–2
* frac 3bits라고 가정했으므로 Result ≈ –1. 001 × 2^–2