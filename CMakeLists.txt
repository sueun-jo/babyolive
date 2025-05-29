cmake_minimum_required(VERSION 3.10)
project(BabyOlive)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 소스 파일들을 변수에 저장
file(GLOB SOURCES "src/*.cpp")

# 헤더 파일 디렉토리 추가
include_directories(${PROJECT_SOURCE_DIR}/include)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# 데이터 디렉토리 경로를 매크로로 정의
add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data") 