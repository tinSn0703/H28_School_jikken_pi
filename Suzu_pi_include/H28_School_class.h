#pragma once

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

/*
 *  ラインセンサーからの値を受け取るための型
 */
union U_LINE
{
	struct S_LINE
	{
		BOOL _sensor_1 :1;
		BOOL _sensor_2 :1;
		BOOL _sensor_3 :1;
		BOOL _sensor_4 :1;
		BOOL _sensor_5 :1;
		BOOL _sensor_6 :1;
		BOOL _sensor_7 :1;
		BOOL _sensor_8 :1;
	};

	S_LINE _bit;
	BYTE _all :8;
};
