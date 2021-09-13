# Vi and GCC
vi 에디터 써보기 (improved 버전 : VIM)

vi는 3가지의 모드 있음
* command 모드 (vi시작하면 제일 처음상태)
* insert 모드
* last-line 모드

<img width="60%" src="https://user-images.githubusercontent.com/86250281/133089574-568eed56-7fdc-4e54-a694-de20ee881cf7.png"/> 

## insert monde
* a- 커서 다음에 글자 들어감
* i - 커서 왼쪽에 글자 포인트 들어감
* o - 새로운 line만들고 그 다음부터 타이핑

<img width="60%" src="https://user-images.githubusercontent.com/86250281/133090304-d6edb1ad-78fa-4829-a82c-67364e3b709e.png"/>

## Last-line mode

* '/' - 아래쪽으로 문자열 계속 검색
* '?' - 위쪽으로 문자열 계속 검색
* /문자열 - 커서가 위치한 라인 아래쪽으로 입력한 문자열 검색
* ?문자열 - 커서가 위치한 라인 위쪽으로 입력한 문자열 검색

***

* :w [name] - 지정한 파일명으로 저장
* :q - vi 에디터 종료
* :wq - 저장 후 에디터 좀료

* :set number or :se nu -> line number 보여주기
* :set autoindent or :se ai -> 들여쓰기
* :set tabstop=4 or se ts=4 -> tap 사이즈 조절

## Command Mode

insert 모드나 last-line 모드 아니면? 커맨드 모드

<img width="60%" src="https://user-images.githubusercontent.com/86250281/133091457-556e9079-7ace-4dfd-8c86-2cb11b4d8590.png"/>
이런게 있다

* 텍스트 지우기
    * x - 현재 char 삭제
    * dw - word 지우기
    * dd - line 지우기
* copying and pasting
    * yw - 현재 word 복사
    * yy - 현재 line 복사
    * p - 붙여넣기

    (5dd: 5 line 지우기, 2yy: 2line copy)

***

<img width="70%" src="https://user-images.githubusercontent.com/86250281/133092462-cb5d53b4-553f-4747-846a-c5888ea1f0c2.png"/>

(소수판별 코드)- 이 코드에는 몇가지의 버그 있음, 차차 수업하면서 고쳐 나갈 예정

* 배경지식
    * 루트 n까지만 검사해봐도 됌
    * ex) 101이 소수 인가?
        
        루트 101은 대략 10까지, 2, 3, 5, 7

        101은 2,3,5,7로 안나눠짐 -> 소수

## GCC(GNU Compiler Collection)

버전 보고싶으면 (gcc -v or gcc --version)

## Warning and Error Messages

* Errors (컴파일 불가능)
* Warnings (컴파일은 가능, 표준적인 문법 따르지 않았을 때)

* so, Warning은 내가 의도한대로 프로그램 동작하기 위해 미리 위험한 지점 체크할수 있게 알려줌!!

### Options

* -w: 경고 메세지 무시
* -Wall: 가능한 모든 경고메세지 알려줌
* -Werror: 에러로 되어 컴파일 중단

## 다른 자잘한 옵션
* C 언어 버전 확인
    * -std=VER(c11, c17...)
* 최적화 레벨
    * -On(n=0,1,2,3)
    * O0 (최적화 X)
    * O1 or -O
    * O2
    * O3 

* -m32 or m-64 (32bit 코드 생성 가능)

* -g, -g1, -g2, -g3(-ggdb3)
    * 점점 디버깅 수준 up (볼수있는 정보 많아짐)

* -Dname[=definition] 
    *  외부에서 매크로 define 가능