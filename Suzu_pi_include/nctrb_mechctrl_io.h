
#ifndef _NCTRB_MECHCTRL_IO_H
#define _NCTRB_MECHCTRL_IO_H

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
  
  	ファイル名：	nctrb_mechctrl_io.h

	内容：			nctrb-01メカコンボード制御ライブラリ
					ヘッダファイル


 */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
  型定義
												10進数での	16進数での
												値の範囲	値の範囲	
  BYTE		バイト型	 8bit	符号なし整数	0 - 255		  0x00 	-   0xFF
  WORD		ワード型	16bit	符号なし整数	0 - 65535	0x0000	- 0xFFFF

*/
typedef	unsigned char BYTE;
typedef unsigned short WORD;
typedef short sWORD;

/*
	論理のための型
*/
enum BOOL
{
	FALSE = 0,
	TRUE  = 1
};

inline BOOL
operator ~ (BOOL _arg_bool)
{
	return (BOOL)((~(int)_arg_bool) & 1);
}

inline BOOL
operator &
(
	BOOL _arg_bool_0,
	BOOL _arg_bool_1
)
{
	return (BOOL)(((int)_arg_bool_0 & (int)_arg_bool_1) & 1);
}

inline BOOL
operator |
(
	BOOL _arg_bool_0,
	BOOL _arg_bool_1
)
{
	return (BOOL)(((int)_arg_bool_0 | (int)_arg_bool_1) & 1);
}

/*
	モータの動作を表す型
*/
enum SIGNAL
{
	S_FREE  = 0x00,
	S_TRUE  = 0x01,
	S_FALSE = 0x02,
	S_BREAK = 0x03
};

enum DIREC_X
{
	D_ZEROX	= 0,
	D__EAST	= 1,
	D__WEST	= 2,
};

enum DIREC_Y
{
	D_ZEROY = 0,
	D_NORTH = 1,	
	D_SOUTH = 2,
};

//配布された関数の宣言

void nctrb_mc_io_initialize();
BYTE nctrb_mc_io_readStartButton();
BYTE nctrb_mc_io_readLineSensor();
void nctrb_mc_io_driveWheel(BYTE value);
WORD nctrb_mc_io_readPortIN1500();
void nctrb_mc_io_writePortOUT1500(WORD value);

//自作関数

inline void F_Init_machine()		{				nctrb_mc_io_initialize();				}
inline BOOL F_Read_startbutton ()	{	return (nctrb_mc_io_readLineSensor ? TRUE : FALSE);	}

#include "Suzu_Func_i2c.h"
#include "Suzu_Func.h"

//#ifdef __WRITE__
#include "H28_School_U_LINE.h"
#include "H28_School_U_WHEEL.h"
#include "H28_School_C_WHEEL.h"
//#endif

#endif