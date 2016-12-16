

#pragma once

//�w�b�_�t�@�C����
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#if defined(__WRITE__)
#	define I2C_SLAVE 0
int  write(int a, BYTE b[], int c)	{	return (b[a] & c);		}
int  read(int a, BYTE b[], int c)	{	return (b[a] & c);		}
int	 ioctl(int a, int b, int c)		{	return ((a >> b) & c);	}
char open(char a[], int b)			{	return a[b];			}
void sleep (double a)				{							}	
#else
#	include <linux/i2c-dev.h>
#	include <sys/ioctl.h>
#	include <unistd.h>
#	include <termios.h>
#endif

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//#define	SLAVE_ADDRESS	0x08
#define	SLAVE_ADDRESS	0x10

#define BYTE unsigned char
#define WORD unsigned short
#define sWORD short

//printf("sizeof short -> %02d", sizeof(short));
//���ʂ�2byte


//--------------------------------------------------------------------
//--------------------------------------------------------------------
int 		_glo_fd;
//char *_glo_i2cdev = "/dev/i2c-0";
char 		*_glo_i2cdev = "/dev/i2c-1";
//unsigned char buf[16];
BYTE 		_glo_buf[100];


//--------------------------------------------------------------------
//--------------------------------------------------------------------
#ifdef _COMMENT_PICMICON_INFO
//--------------------------------------------------------------------
//I2C�ʐM�֌W
//PIC�}�C�R���\�[�X�t�@�C�����\��t���A�Q�Ɨp
//--------------------------------------------------------------------
//--------------------------------------
/*
  I2C_SLAVE_ADDR		7bit�̐���(0x00 - 0x7F)
						SSPADD�ɃZ�b�g����Ƃ��ɂ�
						1�r�b�g�V�t�g���K�v�Ȃ̂Œ���

*/
#define		I2C_SLAVE_ADDR		0x18
//--------------------------------------

//--------------------------------------
/*
  

 */
//--------------------------------------
BYTE		i2cDataIsRWAddr;
BYTE		i2cCurrentAddr;
BYTE		i2cRWAddrEnd		= 0x0F;

BYTE		i2cRWBuf[]			= { 0xFF,	//[0]	RW	�I���j�z�C�[���쓮�p�A0xFF -> �u���[�L��� 

									0X00,	//[1]	RW	�@�\�������o��[15-08]
									0X00,	//[2]	RW	�@�\�������o��[07-00]

									0x00,	//[3]	R	���C���Z���T�[�@��������(��)�őΉ�����r�b�g��1��Ԃ�

									0x00,	//[4]	R	�@�\����������[15-08]
									0x00,	//[5]	R	�@�\����������[07-00]
											//�S16�r�b�g�̂���(15-00)����4�r�b�g��I2C�ʐM�s�����ߎg�p�s�ł���
											//
											//	BIT 12, 11, 04, 03	���@�g�p�s�I�I�I�v���ӁI�I�I
											//

									0x00	//[6]	R	�X�^�[�g�X�C�b�`	������1�A����ȊO��0
};
//--------------------------------------------------------------------
#endif
//--------------------------------------------------------------------
//--------------------------------------------------------------------



//----------------------------------------------------------
//----------------------------------------------------------
int myReturn(int ret)
{
//	exit(ret);
	return(ret);
}
//----------------------------------------------------------


//----------------------------------------------------------
int i2cwrite(BYTE *buf, int len)
{
	if (write(_glo_fd, buf, len) != len)
	{
		printf("Err:- i2cwrite\n");

		return 1;
	}

	return 0;
}
//----------------------------------------------------------


//----------------------------------------------------------
int i2cread(int offset, BYTE *buf, int len)
{
	*buf = (char)offset;

	if (i2cwrite(buf,1))	return 1;
	
	if (read(_glo_fd, buf, len) != len) 
	{
		printf("Err:- i2cread\n");
		myReturn(1);
	}
	
	return 0;
}
//------------------------------------------------------------------------------
