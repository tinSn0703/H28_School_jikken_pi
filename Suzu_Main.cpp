
#define __WRITE__ 1 //ƒvƒƒOƒ‰ƒ€ì¬—p

#include "Suzu_pi_include/nctrb_mechctrl_io.h"

int main (void)
{
	U_LINE _line;
	
	C_WHEEL _wheel;

	F_Init_machine();

	do
	{
		static unsigned int _count = 1;

		_line.In();

		if (_count <= 42)
		{
			_wheel.Stop();
		}
		else
		{
			if (_line._bit._sensor_1 )
			{
				_wheel.Do_n_west();
			}
			else if (_line._bit._sensor_2 )
			{
				_wheel.Do_n_east();
			}
			else
			{
				_wheel.Do_north();
			}
		}

		_wheel.Out();

		_count ++;

		if (_count >= 50)	_count = 1;
	}
	while (F_Read_startbutton() != TRUE);
	
	printf("END");

	_wheel.Stop();

	_wheel.Out();

	return 0;
}