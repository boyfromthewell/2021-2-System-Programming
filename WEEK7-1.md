# Machine-level representation Basics

## Intel CPU history

* 시간 지날수록 트랜지스터 증가,
* 80386(1985) - 첫번째 32bit, IA32
* 80486(1989) - 최초로 파이프라인 등장
* Pentium 4E(2004) - 첫번째 64bit, x86-64
* 최근에는 멀티코어 형태로 진화

* Complex Instruction Set Computer (CISC) <-> RISC
    * 명령어수 많고, 디코딩 오래걸림, 회로복잡
    * but 실행효율 높고, 소스코드 작게 만들수 있다

### ISA(Instruction Set Architecture)

* SW와 HW사이의 인터페이스를 명령어 집합으로 정의한것
* 명령어와 machine state(레지스터 + 메모리) 정의
* x86, x86-64, IA64, ARM...

## Machine Instruction
* opcode
    * 실제 operation의 타입을 명시 ex. mov, add, jump
    1. data를 메모리나 레지스터에서 이동시킴
    2. 산술 논리 연산 수행 (add, sub..)
    3. branch 명령어 수행

* operands
    * opcode에 들어간 input/output데이터나 그 주소들 명시

### Machine State

프로그래머 관점에서 컴퓨터를 레지스터와 메모리로 추상화하기

<img width="60%" src="https://user-images.githubusercontent.com/86250281/136811697-deb179d7-c2ef-4d63-9c9c-9a6b5daff3b5.png"/>

* 레지스터 : CPU 내부에 있는 기억소자, 빠른 연산 지원

만약 레지스터가 없다면?

F = (X+Y) - (X*Y) 의 식을 수행해야 한다 하자, 변수 세개가 메모리에 있음 ,
먼저 X, Y를 load하고 더한결과를 레지스터가 없다면 메모리에 저장할 것임 총 3번의 접근이 필요, 곱셈, 빼기 연산도 마찬가지이기 때문에 총 9번의 메모리 접근이 필요하다

레지스터 있으면 -> X,Y 불러오는데 두번, F에 저장하는데 한번 총 세번의 메모리 접근 (임시 결과들은 다 레지스터에 저장하기 때문)

## X86-64 Integer Registers

<img width="60%" src="https://user-images.githubusercontent.com/86250281/136813279-81b85e4e-8427-4a68-917f-610cc5b90392.png"/>

16개의 레지스터, 호환구조 가짐, 서로 다른 크기의 값 사용 가능하다

* rsp : 기능 특정되어있음 (스택 포인터)
* rip : PC 기능
* eflags : 상태 레지스터

## Assembly

어셈블리 공부해야 하는 이유
1. 프로그램 비효율성 찾아서 최적화 가능
2. 취약점 문제점 파악가능
3. 불가피하게 레지스터 접근해야 할때 있을수 있다

### Disassembler

objdump -d test.o : 실행파일이나 오브젝트파일 어셈블리 코드로 

다른방법 gdb 사용 : gdb test.o

(gdb) disas swap(함수이름)
(gdb) x/13xb swap : 실제 머신코드 볼수있음

## Moving data

mov src, dst => dst = src 의미 (AT&T기준)

* Operand type
    * immediate : 상수값 
        * ex. &#36;0x400, &#36;-533
        * src에만 가능
    * Register
        * ex. %rax, %r13
        * %rsp는 기능적으로 제약(잘사용해야함)
    * Memory
        * ex. (%rax), 0x400
        * address mode
        * src, dst 둘중하나에만

## mov operand form

* Immediate
    ```
    mov $0x104, ____ 
    ```
    0x104값을 어딘가에 copy하기

* Registers
    ```
    mov %rbx, ____
    ```
    레지스터의 값을 어딘가에 copy하기
    ```
    mov ____, %rbx
    ```
    어딘가에 있는값을 %rbx 레지스터에 저장하기

* memory address
    ```
    mov 0x104, ____
    ```
    104번지 주소의 값을 어딘가에 저장
    ```
    mov ____, 0x104
    ```
    어떤 값을 104번지의 주소에 저장

* Indirect addressing mode
    ```
    mov (%rbx), ____
    ```
    레지스터의 값을 메모리 주소로 evalution, 그 메모리 주소에 해당 값을 어딘가에 저장
    ```
    mov ____, (%rbx)
    ```
    이 레지스터에 저장된 메모리 주소에 해당하는 주소에 어떤 값을 저장

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/136817775-43fce024-ec7b-4db0-b987-4e1a6274e0f8.png"/> 이 레지스터에 있는 값을 주소로 보고 그 주소에 해당하는 메모리에 access한다는 의미

* Displacement addressing mode

    레지스터 저장된 값과 앞의 상수 더해서 주소를 만들고 그 주소에 해당하는 메모리에 access <img width="40%" src="https://user-images.githubusercontent.com/86250281/136818859-c1546098-baf0-4cc3-8114-259dde985796.png"/>
    ```
    mov 0x10(%rax), ____
    ```
    그 메모리에 해당하는 값을 어딘가에 저장
    ```
    mov ____, 0x10(%rax)
    ```
    어떤값을 그 메모리에 저장

* Indexed addressing mode

    각각의 레지스터에 저장된 값을 더해서 그 값을 주소로 보고 그 주소로 메모리에 access <img width="40%" src="https://user-images.githubusercontent.com/86250281/136819443-99b74150-e46a-4658-8b68-eda8c708d73f.png"/>

    ```
    mov (%rax, %rax), ____
    ```
    메모리에 접근한 값을 어딘가에 저장
    ```
    mov ____, (%rax, %rdx)
    ```
    어떤 값을 그 메모리 주소(각각 레지스터에 저장된 값의 합)에 저장

    ***

    각각의 레지스터 값 더한뒤 앞에 상수까지 더하고 그값을 주소로 보고 메모리 access <img width="40%" src="https://user-images.githubusercontent.com/86250281/136820427-82c4f9e9-03b2-4b1d-8581-8c0b82d0dc4c.png"/>

    ```
    mov 0x10(%rax, %rdx), ____
    ```
    메모리에 접근한 값을 어딘가에 저장
    ```
    mov ____, 0x10(%rax, %rdx)
    ```
    어떤 값을 그 메모리 주소(각각의 레지스터 값 더한뒤 앞에 상수까지 더한 값)에 저장

* scaled Indexed addressing mode

    index 레지스터에 scaling 값 곱해주는것(1,2,4,8) 

    ```
    mov 0x4(%rax, %rdx, 2), ____
    ```
    rdx에 2곱하기, 나머지는 전의 과정과 동일
    ```
    mov ____, 0x4(%rax, %rdx, 2)
    ```
    어떤것을 rdx 2배하고 rax, 0x4더한 주소에 저장
    ```
    mov ____, 0x4(, %rdx, 4)
    ```
    생략된경우는 값을 0으로 봄

## movq operand combinations

<img width="70%" src="https://user-images.githubusercontent.com/86250281/136822294-e38f3925-8b8b-4409-9b3d-e71bffb1547e.png"/>

***
실제 어셈블리 코드 확인해보기
<img width="50%" src="https://user-images.githubusercontent.com/86250281/136823254-3bf945ea-e3a7-428c-a972-2781cb0e029a.png"/><img width="50%" src="https://user-images.githubusercontent.com/86250281/136823340-2dfbf82a-c4cc-4ef7-a792-e8db4dd60f3e.png"/>
