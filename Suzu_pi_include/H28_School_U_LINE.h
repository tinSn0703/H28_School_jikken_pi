
#pragma once

/*
 *  ���C���Z���T�[����̒l���󂯎�邽�߂̌^
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

	void In();
};

void 
U_LINE :: 
In ()
{
	_all = nctrb_mc_io_readLineSensor();
}


