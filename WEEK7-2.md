# Arithmetic operation

## x86 Data size

* b : byte (8bit)
* w : word (16bit)
* l : double word (32bit)
* q : quad word (64bit)

## Movabsq instruction

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137904045-84f71b1a-0225-43f1-bcbd-2313e4793263.png"/>

movq는 32bit밖에 이동하지 못하는 제약있음 -> movabsq에서 64bit 복사 지원

## movz and movs

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137905094-e9e1c877-9869-4927-a612-78c77a7ee802.png"/>

ex) movzwl 0x202, %eax : word to double word -> 16bit만큼 0x202번지에서 복사하고 나머지 16bit에 0으로 채우기

movslq 0x200, %rax: double word to quad -> 32bit만큼 0x200번지에서 복사하고 나머지 f로 채움

## Load Effective Address

mov랑 비슷하지만 lea는 address자체를 저장 
<img width="60%" src="https://user-images.githubusercontent.com/86250281/137915646-a4793bb0-6efb-42ba-9ad1-25b78ee56c01.png"/>

1. 실제 주소 접근에 사용
2. x+k*y 연산(산술계산)에도 사용

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137916747-6d0e8432-47ee-4107-af3c-f4a2a71d49da.png"/> 3x를 shift left 2만큼 3x * 4 = 12x

## Unary operations (단항 연산)

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137917527-7aff0cf0-29f3-40ff-a61c-cc153da5af5b.png"/>

ex) decq %rcx : rcx레지스터 값에서 1을 빼줌

incq 16(%rax) : rax레지스터에 값에 16을 더한후 그 주소에 값을 1증가

## binary operations

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137923686-32cff215-e1b3-490a-862d-532467ab97a7.png"/>

첫번째 ex) 0xff에 1더함

두번째 0x100+8=0x108 -> 0xAB에서 3뺌

세번째 rax=0x100, rdx=0x3*8(16진수로 통일해주기)=0x118 -> 0x11 x 0x10 = 0x110

## shift operations

* shift logical right: 0으로 채워줌 (SHR)
* shift arithmetic right: MSB(가장 왼쪽비트)로 채워줌 (SAR)

* left같은경우는 다 0채워줌

<img width="60%" src="https://user-images.githubusercontent.com/86250281/137925082-16c19000-6a20-48f4-bcbb-2ab3d4ddf93d.png"/>

### practice

실제 어셈블리 코드 보기

<img width="50%" src="https://user-images.githubusercontent.com/86250281/137929197-aa5b7869-ab03-4af3-8e22-fe1e43b19444.png"/><img width="50%" src="https://user-images.githubusercontent.com/86250281/137929289-98705748-6c35-4378-8045-b2054a7f767b.png"/>
<img width="50%" src="https://user-images.githubusercontent.com/86250281/137929373-057b4e15-2b7e-459e-b401-f933fdc5d3a6.png"/>