/*!
 *  @file	Futaba30xServo.hpp -> Futaba40xServo.hpp
 *  @brief	 
 *
 *  @date	2012/11/07 -> 2015/04/21
 *  @author	taki4416 , Ariyu
 *
 */

#ifndef FUTABA40XSERVO_HPP_
#define FUTABA40XSERVO_HPP_

class Futaba40x {
public:
	Futaba40x ( int fd, unsigned char id )
			: fd_(fd), id_(id)
	{
	}
  int move ( short deg, unsigned short speed );
  int torque_on();
  int torque_off();
private:
	int fd_;
	unsigned char id_;
};

#endif /* FUTABA40XSERVO_HPP_ */
