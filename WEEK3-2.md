# The GNU Project Debugger

* Debug(버그 잡기)
    * 의도하지 않은 버그 -> 에러 찾기, 에러 fix하기

    * 문법 뺴먹는다던가 친숙한 버그는 금방 잡힘,  
    상태 보기위해 과도한 printf쓰는것 지양 (에러범위 더 늘어남)

    * Debug-only code

    <img width="60%" src="https://user-images.githubusercontent.com/86250281/133635480-44678867-8ee3-41a0-8d72-d3b49f8c7308.png"/>

    * Debug command line switch

    <img width="60%" src="https://user-images.githubusercontent.com/86250281/133635611-754ea249-f4c8-42ef-88ad-98c4b1d066d2.png"/>

    * $ ./a.out error_log (파일 에러메세지 분석 방법)

    * 미리 정의된 매크로도 사용 가능

    ## Matloff Program

    <img width="50%" src="https://user-images.githubusercontent.com/86250281/133636052-f4e9d176-db97-4056-9a8b-97433b6112dd.png"/>

    앞전에 몇가지의 오류가 있다는 코드

***

* 첫번째 오류 발생

    <img width="50%" src="https://user-images.githubusercontent.com/86250281/133637700-e33a8502-e9ab-4e75-9e09-57ce7c0ad0c9.png"/>
    <img width="50%" src="https://user-images.githubusercontent.com/86250281/133637816-a287efe9-8dea-4795-91b5-7d45d595ee34.png"/>

    gdb를 통해 해결하자

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/133638069-1d7244fa-e565-4ccc-8458-c6a0f976c16c.png"/>

    bt (backtrace) 옵션 통해 더 많은 정보 얻기 가능, 스텍 프레임 보는것, 번호로 디버깅하기

    <img width="50%" src="https://user-images.githubusercontent.com/86250281/133638313-c8a77b79-640d-4160-bfac-81288e32389c.png"/>

    up - 스텍 프레임 하나씩 올라가기 옵션, 10번 라인이 이상하다?

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/133638718-42cce86e-2d39-4b3a-bfc1-d66d89346245.png"/>

    해당 코드 보기 (main.c 10라인)

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/133639215-8327c208-78a1-405e-a78f-c9d9c18cdc11.png"/>

    오류 수정 하기

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/133639824-5581724f-6ab3-44f7-9e20-37a16c6d378a.png"/>

    첫번째 버그는 잡혔지만, 여전히 세그멘테이션 오류, 또 다른 버그의 암시

    <img width="40%" src="https://user-images.githubusercontent.com/86250281/133640261-213bf5d1-fdd8-4ee6-8a6b-c807c77535de.png"/>

*** 

* 두번째 오류

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133640823-6f9ded22-e08c-4898-98eb-d8850d18765a.png"/>

k=3일때 8번라인에서 출구가 없는 상태 (배열에서 세그멘테이션 fault-> 보통 out of bound)

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133642340-40f957d5-dda4-439b-9c44-9c8c574e907f.png"/>

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133642261-5d1a2f7e-ea18-429a-9dba-b19b2086644d.png"/>

변수 상태 어떤가 여러가지 방법으로 보기

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133643175-0dae8ae4-a1bb-4192-98c3-e1ef43b7050e.png"/>

반복문 빠져나올수 있게 코드수정 후 다시 컴파일 실행

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133643295-42c2e203-db04-4c35-9042-dcc65416a6b7.png"/>

9, 15가 소수? -> 여전히 버그 존재

***
* 세번째 오류

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133643913-1cd7aef2-0e8d-4ae7-8abc-fa7ef324c8bd.png"/>

breakpoint main으로 잡고 한줄씩 실행 해보자!

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133644798-4082a857-ac4e-45eb-b2f7-adc79204dd84.png"/>

계속 n 반복해야될까? 위와 같은 조건 주면 k>=9일때부터 볼수 있다

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133646135-fcd2fc09-a801-47d3-bea4-8b62ddaafb70.png"/>

j=3일때 9와 나누어져 소수가 아니라고 나와야되는데 j 두번 ++되서 건너 뛰어버림

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133647014-34aa22a7-7b31-42b6-af40-f31635c1a0d0.png"/>
<img width="40%" src="https://user-images.githubusercontent.com/86250281/133647100-443290eb-6288-4b9c-a01b-20bf9971c2fc.png"/>

오류 수정후 컴파일 실행 -> 정상 출력!!

***

## WatchPoint

gdb의 watch 기능 : 특정주소영역의 값을 감시하여, 해당 주소영역의 값이 변경이 되었을 경우 이를 알려주는 기능

만약, 특정 변수가 있는데 이 변수의 값이 어느 순간부터 원하지 않는 이상한 쓰레기(garbage)값으로 할당되어 연속적인 문제를 일으킬 경우, 이 변수 주소 영역을 watch 를 이용하여 감시하면 변경의 원인이 되는 코드를 손쉽게 찾을 수 있음

```
wa[tch] *(변수형 *)주소값
example> wa *(int *) 0x7fffffffdd3c
```

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133648746-e001fff0-d428-446c-a4e2-310090a57b2b.png"/> 

평문이 특정 길이 넘어가면 key값(123) 유지 못하는 버그 발생 

<img width="40%" src="https://user-images.githubusercontent.com/86250281/133649880-9441fbc3-1ceb-44f6-abbf-aeb8e390d110.png"/>

old 값, new 값 볼수있고 타이밍도 볼수 있다


