## HW organization of a Typical System
* CPU(central processing unit)-간단한 프로세서, 메인메모리에 있는 명령어를 처리 (명령어 반복적으로 수행!)

* Main memory- 프로세서가 프로그램 실행하는 동안 프로그램과 데이터를 가지고 있는 저장 장치

* Buses-정보 바이트들을 앞뒤로 전달해줌

* I/O device - I/O 버스와 연결, controller, adapter 같아 i/o 디바이스 교통정리하는 칩셋 있음

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132215836-ab3ac980-edd4-4820-b4f8-8b0acdc398ee.png"/>

## When we run our program?

우리가 엔터키를 쉘 커맨드에서 누른후 ->

* shell이 hello file을 로드
* hello 오브젝트 파일의 코드와 데이터를 디스크에서 메인 메모리로 복사
* DMA(direct memory access)라는 기술 사용
    * CPU 개입 없이 독립적으로 메인 메모리에 접근 가능
* 프로세서는 hello 프로그램의 기계어 명령어를 수행하기 시작

***

1. CPU는 disk 읽기 시작

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132216678-188e66b1-ed07-4bdc-ab76-3dfd1729ea89.png"/>

2. disk controller는 sector read 후, DMA방식을 통해 직접 메인메모리로 전송 (cpu는  DMA 덕에 다른일 요긴하게 가능!)

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132216815-3a4029f4-08fa-4ab3-a62e-bc8c8b921a74.png"/>

3. DMA 전송이 완료되면 disk controller가 CPU에게 인터럽트 여부 알림

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132217229-087fad92-aa56-43fa-a94f-dfbe0892510e.png"/>

*** 

## Caches Matter

시스템이 정보를 이동하는데 너무 많은 시간 씀

* flow of instructions and data
    1. hello 프로그램의 명령어 처음에는 디스크에 있음
    2. 프로그램이 로드 되면, 메인메모리로 copy됨
    3. 프로세스가 프로그램을 실행하면 명령어는 메인메모리에서 프로세서로 copy
    (너무 많은 copy 발생!!)

* Cache-데이터와 값 미리 복사(학교 사물함과 같음=학교 사물함에 책들을 넣어 놓으면 책이 필요할때 굳이 집까지 가지 않아도 됨)

* 자주 access될거같은 data를 hold함 (ex. 배열, 함수)

* 캐시는 큰 메모리와 속도가 빠른거같은 illusion을 제공

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132228026-7dad4215-aee0-46a3-b688-4752637e40b2.png"/>
disk, DRAM 사이에 버퍼캐시도 존재 (virtual cache)

***

## OS Manages the hardware(컴퓨터 자원관리)

* OS from programmer's 관점

1) hw를 안전하게 지켜줌
2) low-level의 하드웨어 장치를 조작하기 위해 간단한고 균일한 메커니즘 프로그램에 제공

* OS는 근본적인 추상화를 통해 두가지 목표 달성

    processes, virtual memory, files

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132229025-d5bfde6a-c764-44f2-ae3a-343fb7506772.png"/>

1. Processes (virtual CPU)

    * 수행중인 프로그램의 추상화
    * 다수의 프로세스는 같은 시스템에서 동시에 수행 가능
    * 시스템에서 독점적으로 수행하고 있는거 같은 illusion 제공
    * 단일 CPU는 프로세스를 전환하며 여러 프로세스를 동시에 수행하는것처럼 보이게 가능
        * context switch(user code<->kernel code)
        * Process switch(Process A<->Process B)

2. Virtual memory

    * 각 프로세스가 메인메모리를 혼자 독점하는거 같은 illusion 제공

<img width="100%" src="https://user-images.githubusercontent.com/86250281/132229862-568f66e0-ea1f-450d-be94-e71e48812bea.png"/>


3. File

    * 다양한 i/o 디바이스 위한 추상화: byte들의 연속
    * 저장장치의 물리적 특성을 추상화하여 논리적 저장 단위, 파일을 정의