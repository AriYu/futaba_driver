cmake_minimum_required(VERSION 2.8)
project( futaba_servo )

ADD_DEFINITIONS(
-g
-O0
-Wall
-std=c++11
)

add_executable(futaba_servo 
  ./src/Futaba40xServo.cpp
  ./src/futaba_servo.cpp) 
target_link_libraries(futaba_servo)
