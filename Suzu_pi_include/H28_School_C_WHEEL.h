
#pragma once

/*
	25ÇÃÉVÅ[ÉãÇ™ì\Ç¡ÇƒÇ†ÇÈï”ÇëOÇ∆ÇµÇƒÇ¢Ç‹Ç∑
*/

class C_WHEEL
{

private:
	
	U_WHEEL _mem_wheel;

public:

	C_WHEEL();

	void Write_1 (SIGNAL );
	void Write_2 (SIGNAL );
	void Write_3 (SIGNAL );
	void Write_4 (SIGNAL );

	void Write_num (unsigned int , SIGNAL );

	void Do_north();
	void Do_south();

	void Do_east();
	void Do_west();

	void Do_n_east();
	void Do_n_west();
	void Do_s_east();
	void Do_s_west();

	void Do (DIREC_X _arg_direc_x, DIREC_Y _arg_direc_y);

	void Do_turn_r();
	void Do_turn_l();

	void Out();

	void Stop();
};

C_WHEEL :: 
C_WHEEL ()
{
	_mem_wheel.Stop();
}

void 
C_WHEEL :: 
Write_1 (SIGNAL _arg_signal)
{
	_mem_wheel.Write_1(_arg_signal);
}

void 
C_WHEEL :: 
Write_2 (SIGNAL _arg_signal)
{
	_mem_wheel.Write_2(_arg_signal);
}

void 
C_WHEEL :: 
Write_3 (SIGNAL _arg_signal)
{
	_mem_wheel.Write_3(_arg_signal);
}

void 
C_WHEEL :: 
Write_4 (SIGNAL _arg_signal)
{
	_mem_wheel.Write_4(_arg_signal);
}


void 
C_WHEEL ::  
Write_num 
(
	const unsigned int _arg_num_wheel,
	const SIGNAL _arg_sig
)
{
	switch (_arg_num_wheel)
	{
		case 1:	_mem_wheel.Write_1(_arg_sig);	break;
		case 2:	_mem_wheel.Write_2(_arg_sig);	break;
		case 3:	_mem_wheel.Write_3(_arg_sig);	break;
		case 4:	_mem_wheel.Write_4(_arg_sig);	break;
		
		default:
		{
			printf("ERROR \n");	
			
			break;
		}
	}
}

void 
C_WHEEL :: 
Do_north ()
{
	_mem_wheel.Write_1(S_TRUE);
	_mem_wheel.Write_2(S_FALSE);
	_mem_wheel.Write_3(S_FALSE);
	_mem_wheel.Write_4(S_TRUE);
}

void 
C_WHEEL :: 
Do_south ()
{
	_mem_wheel.Write_1(S_FALSE);
	_mem_wheel.Write_2(S_TRUE);
	_mem_wheel.Write_3(S_TRUE);
	_mem_wheel.Write_4(S_FALSE);
}

void 
C_WHEEL :: 
Do_east ()
{
	_mem_wheel.Write_1(S_TRUE);
	_mem_wheel.Write_2(S_TRUE);
	_mem_wheel.Write_3(S_FALSE);
	_mem_wheel.Write_4(S_FALSE);
}

void 
C_WHEEL :: 
Do_west ()
{
	_mem_wheel.Write_1(S_FALSE);
	_mem_wheel.Write_2(S_FALSE);
	_mem_wheel.Write_3(S_TRUE);
	_mem_wheel.Write_4(S_TRUE);
}

void 
C_WHEEL :: 
Do_n_east ()
{
	_mem_wheel.Write_1(S_TRUE);
	_mem_wheel.Write_2(S_FREE);
	_mem_wheel.Write_3(S_FALSE);
	_mem_wheel.Write_4(S_FREE);
}

void 
C_WHEEL :: 
Do_n_west ()
{
	_mem_wheel.Write_1(S_FREE);
	_mem_wheel.Write_2(S_FALSE);
	_mem_wheel.Write_3(S_FREE);
	_mem_wheel.Write_4(S_TRUE);
}

void 
C_WHEEL :: 
Do_s_east ()
{
	_mem_wheel.Write_1(S_FREE);
	_mem_wheel.Write_2(S_TRUE);
	_mem_wheel.Write_3(S_FREE);
	_mem_wheel.Write_4(S_FALSE);
}

void 
C_WHEEL :: 
Do_s_west ()
{
	_mem_wheel.Write_1(S_FALSE);
	_mem_wheel.Write_2(S_FREE);
	_mem_wheel.Write_3(S_TRUE);
	_mem_wheel.Write_4(S_FREE);
}

void
C_WHEEL ::  
Do 
(
	DIREC_X _arg_direc_x, 
	DIREC_Y _arg_direc_y
)
{
	
}

void 
C_WHEEL :: 
Do_turn_r ()
{
	_mem_wheel.Write_1(S_TRUE);
	_mem_wheel.Write_2(S_TRUE);
	_mem_wheel.Write_3(S_TRUE);
	_mem_wheel.Write_4(S_TRUE);
}

void 
C_WHEEL :: 
Do_turn_l ()
{
	_mem_wheel.Write_1(S_FALSE);
	_mem_wheel.Write_2(S_FALSE);
	_mem_wheel.Write_3(S_FALSE);
	_mem_wheel.Write_4(S_FALSE);
}

void 
C_WHEEL :: 
Out ()
{
	nctrb_mc_io_driveWheel(_mem_wheel.Ret());
}

void 
C_WHEEL :: 
Stop ()
{
	_mem_wheel.Stop();
}

