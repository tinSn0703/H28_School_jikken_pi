
#pragma once

void 
nctrb_mc_io_initialize ()
{  
	printf("NCTRB-01 MechCtrl IO Initializing... ");

	if ((_glo_fd = open(_glo_i2cdev, O_RDWR)) < 0) 
	{
		printf("\nError: Can't open i2c.\n");
		exit(1);
	}
	
	printf(" OK(Done).\n");
	printf("Ready to Access.\n");
}

BYTE 
nctrb_mc_io_readStartButton ()
{
	//�e�X�g
	//return(0);	//�Œ�l��Ԃ��Ă��������A���C�u�����̃e�X�g�p

	//���J�R���{�[�h�̃X���[�u�A�h���X���Z�b�g
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0)
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//�X�^�[�g�{�^���̏�Ԃ̓��J�R��I2C�̃o�C�g6�Ɋi�[�����
	//�o�C�g6����1�o�C�g���[�h���s�����Ƃɂ��A���̏��𓾂�
	if ( i2cread(0x06, _glo_buf, 1) )
	{
		printf("Error: i2c read(). \n");
		exit(1);
	}
  
	return _glo_buf[00];
}

BYTE 
nctrb_mc_io_readLineSensor ()
{
	//���J�R���{�[�h�̃X���[�u�A�h���X���Z�b�g
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) {
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//���C���Z���T�[�̏�Ԃ̓��J�R��I2C�̃o�C�g3�Ɋi�[�����
	//�o�C�g3����1�o�C�g���[�h���s�����Ƃɂ��A���̏��𓾂�
	if ( i2cread(0x03, _glo_buf, 1) )
	{
		printf("Error: i2c read(). \n");
		exit(1);
	}
	
	return( _glo_buf[00] );
}

void 
nctrb_mc_io_driveWheel (BYTE value)
{  
	//���J�R���{�[�h�̃X���[�u�A�h���X���Z�b�g
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0)
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	 //�z�C�[���쓮�f�[�^�̓��J�R��I2C��0�o�C�g�ɏ������߂΂悢
	_glo_buf[00]	= 0x00;
	_glo_buf[01]	= value;

	if (i2cwrite(_glo_buf, 2))
	{
		printf("Error: i2c write(). \n");
		exit(1);
	}

	return (void)0;
}

WORD 
nctrb_mc_io_readPortIN1500 ()
{
	//----------------------------------------------
	//	�|�[�g�̏��F
	//		���J�R����̋@�\�������M�� ���� �|�[�g
	//		IN15 14 ... 01 00 ��16�{�̐M����������
	//		  
	//		�e�M���͉��L�R�l�N�^�ɐڑ�����Ă���
	//
	//		�E���̓R�l�N�^
	//		�@�� CN_IN15-8, �� CN_IN7-0
	//			IN15 ... 00 �� 16�{ �̐M�����ڑ�����Ă���
	//			�M�����͂ƑΉ�����r�b�g�̏��
	//			5V �����	��	1 �����͂����
	//			0V �����	��	0 �����͂����
	//			�Ȃ��A���ꂼ��̓��͐M����
	//			��R��(1kohm)�ɂ���ăv���A�b�v����Ă���
	//			(�ڍׂɂ��Ă̓��J�R����̉�H�}���Q��)
	//	
	//		���d�v���v���Ӂ�
	//		�S16�r�b�g(15-00)�̂�������4�r�b�g��
	//		I2C�ʐM�p�Ƃ��ĕʂŎg�p���Ă��邽��
	//		���̓|�[�g�Ƃ��Ă͎g�p�s�ł���
	//
	//		BIT 12, 11, 04, 03	���@�g�p�s�I�I�I�v���ӁI�I�I
	//
	//		1     0 
	//		5432109876543210	
	//	   	   xx      xx		��	x�͎g�p�s��
	//
	//		Memo:
	//		�R�l�N�^�ɉ����ڑ�����Ă��Ȃ��ꍇ��
	//		�v���A�b�v��R��I2C�ʐM�M�������̊֌W��
	//		�ǂݎ��l��0xE7E7(=0b1110_0111_1110_0111)�ƂȂ�
	//
	//----------------------------------------------
  
	//���J�R���{�[�h�̃X���[�u�A�h���X���Z�b�g
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) {
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//PortIN(�@�\���������́A16bit)�̏�Ԃ̓��J�R��I2C�̃o�C�g 4, 5 �Ɋi�[�����
	//�o�C�g4����2�o�C�g���[�h���s�����Ƃɂ��A���̏��𓾂�
	if ( i2cread(0x04, _glo_buf, 2) ){
		printf("Error: i2c read(). \n");
		exit(1);
	}

	//i2c���[�h����
	//�g�p�s�̃r�b�g��0�Ƃ���(~0x1818��and)�A���ʂ�Ԃ�
	return( ( (~0x1818) & ((_glo_buf[00] << 8) + _glo_buf[01])) );  
}

void 
nctrb_mc_io_writePortOUT1500 (WORD value)
{
	//----------------------------------------------
	//	�|�[�g�̏��F
	//		���J�R����̋@�\�������M�� �o�� �|�[�g
	//		OUT15 14 ... 01 00 ��16�{�̐M����������
	//		  
	//		���J�R����̓d�����������A
	//		���Z�b�g���ɂ͊e�|�[�g��0(L,0V)�o�͂ƂȂ�
	//		(���ӁF�I�[�v���R���N�^�o�͕�������)
	//		(D���b�`���͕���1kohm�v���_�E����R����)
	//	
	//		�Ȃ��A16�{�̐M�����͉��L 3 ��ނ̃R�l�N�^�A
	//		���[�^�[�h���C�o�[�ŐM�������L���Ă���̂ŁA
	//		��舵�����͒��ӂ̂���
	//		(�ڍׂɂ��Ă̓��J�R����̉�H�}���Q��)
	//	
	//		�E�o�̓R�l�N�^
	//		�@�� CN_OUT15-8, �� CN_OUT7-0
	//			OUT15 ... 00 �� 16�{ �̐M�����o��
	//			�Ή�����r�b�g
	//			1 ��ݒ�@��	5V ���o�͂����
	//			0 ��ݒ�@��	0V ���o�͂����
	//			(D���b�`�g�p�A�g�[�e���|�[���o��)
	//	
	//		�E�I�[�v���R���N�^(Open Collector)�o�̓R�l�N�^
	//		�@�� CN_OUT15-8(OC)
	//			OUT15 ... 08 �� 8�{ �̐M����OC�o��
	//			�ʏ�o�̓R�l�N�^�Ƃ͓���A
	//			�_�����قȂ�̂Œ��ӂ̂���
	//			�Ή�����r�b�g
	//			1 ��ݒ�@��	OC On (0V�ƂȂ�)
	//			0 ��ݒ�@��	OC Off(Hi-Z)
	//			(Hi-Z���n�C�C���s�[�_���X��ԁA�o�͕s��)
	//			(Tr�A���C�g�p�A��i50V/500mA���x)
	//	
	//		�E�@�\���������[�^�[�쓮�o��
	//			OUT07 ... 00 �� 8�{ �̐M�����g�p���A
	//			���[�^�[���쓮���邽�߂̃R�l�N�^
	//			�e�M���ƃR�l�N�^�̑Ή�
	//		�@	�� CN_MOTOR3,  �� CN_MOTOR2,  �� CN_MOTOR1, �� CN_MOTOR0
	//			   OUT07,06		  OUT05,04		 OUT03,02	   OUT01,00
	//	
	//----------------------------------------------
	
	//���J�R���{�[�h�̃X���[�u�A�h���X���Z�b�g
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) 
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//PortOUT(�@�\�������o��)�̓��J�R��I2C�� 1, 2 �o�C�g�ɏ������߂΂悢
	_glo_buf[00]	= 0x01;						//���J�R��I2C�̏������ݐ�A�h���X
	_glo_buf[01]	= (0xFF & (value >> 8));	//�������ރf�[�^ 1byte��
	_glo_buf[02]	= (0xFF & (value >> 0));	//�������ރf�[�^ 2byte

	if (i2cwrite(_glo_buf, 3))
	{
		printf("Error: i2c write(). \n");
		exit(1);
	}

	return (void)0;
}
