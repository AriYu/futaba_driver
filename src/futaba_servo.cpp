#include "Futaba40xServo.hpp"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

#include <iostream>
#include <cmath>

class FutabaDriver
{
private:
  Futaba40x servo_;

public:
  FutabaDriver(int fd)
	: servo_(fd, 1) 
  {
  }
  ~FutabaDriver()
  {
  }
  void run(int deg)
  {
	int ret = 0;
	ret = servo_.torque_on();
	if(ret < 0)
	  {
		std::cout << "Error : fail to torque on" << std::endl;
	  }
	unsigned short speed = 1; // 小さいほうが早い
    ret = servo_.move( deg, speed);
	if(ret < 0)
	  {
		std::cout << "Error : fail to move" << std::endl;
	  }
	std::cout << "Wating ..." << std::endl;
	sleep(1);
	servo_.torque_off();
  }

};

int main(int argc, char **argv)
{

  struct termios oldtio, newtio;

  int servo_id = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
  if(servo_id < 0)
	{
	  std::cout << "Error : fail to open" << std::endl;
	}
  ioctl(servo_id, TCGETS, &oldtio);
  newtio = oldtio;

  newtio.c_cc[VMIN] = 1;
  newtio.c_cc[VTIME] = 0;

  newtio.c_cflag = CS8 | CREAD | CLOCAL;

  newtio.c_iflag = IGNBRK | IGNPAR;
  int ret = cfsetspeed(&newtio, B115200);
  if(ret < 0)
	{
	  std::cout << "Error in cfsetspeed" << std::endl;
	  close(servo_id);
	  return 1;
	}
  ioctl(servo_id, TCSETS, &newtio);
  
  FutabaDriver futaba_driver(servo_id);
  for(int i = 0; i < 10; i++){
	futaba_driver.run(short(500*pow(-1, i)));
  }
  return 0;
}
