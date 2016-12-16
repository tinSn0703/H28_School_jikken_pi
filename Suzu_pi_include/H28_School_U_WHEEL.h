#pragma once

/*
 *	é‘ó÷ÇÃÉfÅ[É^ÇàµÇ§ÇΩÇﬂÇÃå^
 */
union U_WHEEL
{

private:

	struct S_WHEEL
	{
		SIGNAL _wheel_3 :2;
		SIGNAL _wheel_4 :2;
		SIGNAL _wheel_2 :2;
		SIGNAL _wheel_1 :2;
	};

	S_WHEEL _bit;
	BYTE _all :8;

public:
	
	void Write (const BYTE );

	void Write_num(const unsigned int , const SIGNAL );
	
	void Write_1(const SIGNAL );
	void Write_2(const SIGNAL );
	void Write_3(const SIGNAL );
	void Write_4(const SIGNAL );

	BYTE Ret ();

	SIGNAL Ret_num (const unsigned int );

	SIGNAL Ret_1 ();
	SIGNAL Ret_2 ();
	SIGNAL Ret_3 ();
	SIGNAL Ret_4 ();

	void Stop();
};

void 
U_WHEEL :: 
Write (const BYTE _arg_data)
{
	_all = _arg_data;
}

void 
U_WHEEL ::  
Write_num 
(
	const unsigned int _arg_num_wheel,
	const SIGNAL _arg_sig
)
{
	switch (_arg_num_wheel)
	{
		case 2:	_bit._wheel_2 = _arg_sig;	break;
		case 1:	_bit._wheel_1 = _arg_sig;	break;
		case 4:	_bit._wheel_4 = _arg_sig;	break;
		case 3:	_bit._wheel_3 = _arg_sig;	break;
		
		default:
		{
			printf("ERROR \n");	
			
			break;
		}
	}
}

void 
U_WHEEL :: 
Write_1 (const SIGNAL _arg_sig)
{
	_bit._wheel_1 = _arg_sig;
}

void 
U_WHEEL :: 
Write_2 (const SIGNAL _arg_sig)
{
	_bit._wheel_2 = _arg_sig;
}

void 
U_WHEEL :: 
Write_3 (const SIGNAL _arg_sig)
{
	_bit._wheel_3 = _arg_sig;
}

void 
U_WHEEL :: 
Write_4 (const SIGNAL _arg_sig)
{
	_bit._wheel_4 = _arg_sig;
}

BYTE 
U_WHEEL :: 
Ret ()
{
	return _all;
}

SIGNAL 
U_WHEEL :: 
Ret_num (const unsigned int _arg_num_wheel)
{
	switch (_arg_num_wheel)
	{
		case 2:	return _bit._wheel_2;
		case 1:	return _bit._wheel_1;
		case 4:	return _bit._wheel_4;
		case 3:	return _bit._wheel_3;
		
		default:
		{
			printf("ERROR \n");	
			
			break;
		}
	}

	return S_FREE;
}

SIGNAL 
U_WHEEL :: 
Ret_1 ()
{
	return _bit._wheel_1;
}

SIGNAL 
U_WHEEL :: 
Ret_2 ()
{
	return _bit._wheel_2;
}

SIGNAL 
U_WHEEL :: 
Ret_3 ()
{
	return _bit._wheel_3;
}

SIGNAL 
U_WHEEL :: 
Ret_4 ()
{
	return _bit._wheel_4;
}

void 
U_WHEEL :: 
Stop ()
{
	_all = 0x00;
}
