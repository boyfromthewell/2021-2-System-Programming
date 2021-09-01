# A Tour of Computer Systems

## Source File (=text file)
* c 프로그램은 바이트의 시퀀스로서 저장됨
* hello.c와 같은 파일은 아스키 코드로 exclusively하게 존재  (vs binary files)

<img width="100%" src="https://user-images.githubusercontent.com/86250281/131701823-18337b91-809e-4540-82d7-5cb64125fe1d.png"/>

***

$ gcc hello.c -> a.out으로 변하는데까지의 과정

<img width="100%" src="https://user-images.githubusercontent.com/86250281/131702233-0b6e36ce-97f5-4f4b-a6eb-7b854d0fac7a.png"/>

1. Preprocessing phase (전처리기 과정)
    
   * 원래의 c 코드에서 #으로 시작하는 statement 찾기 (ex. #define MAX 5) -> 코드에서 교체하는 작업 수행

2. Compilation phase(어셈블리로 바꾸기)

    * 컴파일러는 hello.i 파일을 텍스트파일 hello.s로 바꾸는 작업 수행 (어셈블리 언어 프로그램)
    
    * Assembly-language : readable한 표현방법 (인간이 이해하기 쉬움), ISA 메뉴얼 (명령어 집합구조)로 코드 규정

3. Assembly phase(기계어로 바꾸는 작업)

    * 어셈블리 (hello.s)파일을 기계어로 바꾸는 작업(object 파일 : hello.o)

    * object파일은 binary파일 이기 때문에 실행 안됨

4. Linking phase (연결작업)

    * 만약 코드에서 printf를 쓴경우 라이브러리 파일이기 떄문에 (주소를 아직모름) 기존 오브젝트 파일과 라이브러리 파일을 연결!-> 실행파일 (.exe)
