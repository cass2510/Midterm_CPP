# SQLite User Database Program

## 소개
이 프로그램은 C++과 SQLite3를 사용하여 사용자 정보를 데이터베이스에 저장하고, 저장된 데이터를 출력하는 간단한 콘솔 애플리케이션입니다.  
프로그램은 사용자로부터 ID, 이름, 나이를 입력받아 `user.db` 파일에 저장하고, 저장된 내용을 조회하여 출력합니다.

## 주요 기능
- SQLite 데이터베이스(`user.db`) 생성 및 연결
- `users` 테이블이 이미 존재할 경우 삭제 후 새로 생성
- 사용자 정보(ID, 이름, 나이) 5명 입력 및 저장
- 저장 완료 메시지 출력
- 저장된 모든 사용자 데이터 조회 및 출력

## 사용한 헤더 및 라이브러리
- `<iostream>`: 표준 입출력 사용
- `<string>`: 문자열 처리
- `<sqlite3.h>`: SQLite3 데이터베이스 연동

> **외부 라이브러리**  
> - **SQLite3**: 경량의 관계형 데이터베이스 엔진  
>   (필요 파일: `sqlite3.lib`, `sqlite3.dll` 등 프로젝트에 추가)

## 코드 흐름
1. **데이터베이스 연결**:  
   `sqlite3_open()` 함수를 통해 `user.db` 파일을 열거나 생성합니다.

2. **테이블 준비**:  
   - 기존 `users` 테이블이 있다면 삭제합니다. (`DROP TABLE IF EXISTS users;`)
   - 새로운 `users` 테이블을 생성합니다. (`CREATE TABLE users (id INTEGER, name TEXT, age INTEGER);`)

3. **사용자 입력 및 저장**:  
   - 5명의 사용자로부터 `ID`, `이름`, `나이`를 입력받습니다.
   - 입력된 데이터를 `INSERT INTO` 쿼리를 통해 데이터베이스에 삽입합니다.

4. **모든 사용자 출력**:  
   - `SELECT id, name, age FROM users;` 쿼리 실행
   - 저장된 사용자 정보를 콘솔에 출력합니다.

5. **자원 정리**:  
   - 준비된 SQL 문장(`sqlite3_stmt`) 해제
   - 데이터베이스 연결 종료(`sqlite3_close()`)

## 빌드 방법
1. **필수 조건**
   - C++17 이상 지원 컴파일러
   - SQLite3 라이브러리 설치 및 프로젝트에 연동

2. **Visual Studio 설정 예시**
   - `sqlite3.lib` 추가 (`링커 -> 입력 -> 추가 종속성`)
   - `sqlite3.dll` 파일을 실행 파일과 같은 폴더에 배치
   - `sqlite3.h` 및 관련 파일을 포함 디렉터리에 추가 (`C/C++ -> 일반 -> 추가 포함 디렉터리`)

## 예시 실행 화면
```bash
1번째 사용자 입력 (ID 이름 나이): 1 Alice 30
2번째 사용자 입력 (ID 이름 나이): 2 Bob 25
...
모든 사용자 저장 완료

Users 테이블 데이터:
ID: 1, Name: Alice, Age: 30
ID: 2, Name: Bob, Age: 25
...
```

