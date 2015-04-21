/*!
 *  @file	Futaba30xServo.cpp
 *  @brief	 
 *
 *  @date	2012/11/07
 *  @author	taki4416
 *
 */

#include <iostream>
#include <unistd.h>
#include "Futaba40xServo.hpp"
#include <stdio.h>
#include <string.h>

int Futaba40x::move ( short deg, unsigned short speed )
{
  unsigned char data[12];
    
  data[0]  = (unsigned char)0xFA;				    // ヘッダー1
  data[1]  = (unsigned char)0xAF;				    // ヘッダー2
  data[2]  = (unsigned char)id_;      			    // サーボID
  data[3]  = (unsigned char)0x00;				    // フラグ
  data[4]  = (unsigned char)0x1E;				    // アドレス(0x1E=30)
  data[5]  = (unsigned char)0x04;				    // 長さ(4byte)
  data[6]  = (unsigned char)0x01;				    // 個数
  data[7]  = (unsigned char)(deg&0x00FF);		    // 位置 sPosの下位8bitだけ残す
  data[8]  = (unsigned char)((deg&0xFF00)>>8);	    // 位置 sPosの上位8bitだけ残して、
                                                    //      右に8bitシフトする
  data[9]  = (unsigned char)(speed&0x00FF);	        // 時間
  data[10] = (unsigned char)((speed&0xFF00)>>8);	// 時間
  data[11] = (unsigned char)id_;

  // チェックサム
  for(int i = 3; i < 11; ++i ){
	data[11] = (unsigned char)(data[11] ^ data[i]);
  }
  // 送信
  return write(fd_, data, 12);
}

int Futaba40x::torque_on()
{
  unsigned char data[9];

  data[0] = (unsigned char)0xFA;				// ヘッダー1
  data[1] = (unsigned char)0xAF;				// ヘッダー2
  data[2] = (unsigned char)id_;     			// サーボID
  data[3] = (unsigned char)0x00;				// フラグ
  data[4] = (unsigned char)0x24;				// アドレス(0x24=36)
  data[5] = (unsigned char)0x01;				// 長さ(4byte)
  data[6] = (unsigned char)0x01;				// 個数
  data[7] = (unsigned char)0x01;            	// ON/OFFフラグ
  data[8] = (unsigned char)id_;

  // チェックサム
  for (int i = 3; i < 8; i++) {
	data[8] = (unsigned char)(data[8] ^ data[i]);
  }
  return write(fd_, data, 9);
}

int Futaba40x::torque_off()
{
  unsigned char data[9];

  data[0] = (unsigned char)0xFA;				// ヘッダー1
  data[1] = (unsigned char)0xAF;				// ヘッダー2
  data[2] = (unsigned char)id_;     			// サーボID
  data[3] = (unsigned char)0x00;				// フラグ
  data[4] = (unsigned char)0x24;				// アドレス(0x24=36)
  data[5] = (unsigned char)0x01;				// 長さ(4byte)
  data[6] = (unsigned char)0x01;				// 個数
  data[7] = (unsigned char)0x00;            	// ON/OFFフラグ
  data[8] = (unsigned char)id_;

  // チェックサム
  for (int i = 3; i < 8; i++) {
	data[8] = (unsigned char)(data[8] ^ data[i]);
  }
  return write(fd_, data, 9);
}

