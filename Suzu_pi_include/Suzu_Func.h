
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
	//テスト
	//return(0);	//固定値を返していただけ、ライブラリのテスト用

	//メカコンボードのスレーブアドレスをセット
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0)
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//スタートボタンの状態はメカコンI2Cのバイト6に格納される
	//バイト6から1バイトリードを行うことにより、その情報を得る
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
	//メカコンボードのスレーブアドレスをセット
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) {
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//ラインセンサーの状態はメカコンI2Cのバイト3に格納される
	//バイト3から1バイトリードを行うことにより、その情報を得る
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
	//メカコンボードのスレーブアドレスをセット
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0)
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	 //ホイール駆動データはメカコンI2Cの0バイトに書き込めばよい
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
	//	ポートの情報：
	//		メカコン基板の機構部向け信号 入力 ポート
	//		IN15 14 ... 01 00 の16本の信号線がある
	//		  
	//		各信号は下記コネクタに接続されている
	//
	//		・入力コネクタ
	//		　□ CN_IN15-8, □ CN_IN7-0
	//			IN15 ... 00 の 16本 の信号が接続されている
	//			信号入力と対応するビットの状態
	//			5V を入力	→	1 が入力される
	//			0V を入力	→	0 が入力される
	//			なお、それぞれの入力信号は
	//			抵抗器(1kohm)によってプルアップされている
	//			(詳細についてはメカコン基板の回路図を参照)
	//	
	//		☆重要☆要注意☆
	//		全16ビット(15-00)のうち次の4ビットは
	//		I2C通信用として別で使用しているため
	//		入力ポートとしては使用不可である
	//
	//		BIT 12, 11, 04, 03	←　使用不可！！！要注意！！！
	//
	//		1     0 
	//		5432109876543210	
	//	   	   xx      xx		←	xは使用不可
	//
	//		Memo:
	//		コネクタに何も接続されていない場合は
	//		プルアップ抵抗とI2C通信信号部分の関係で
	//		読み取り値は0xE7E7(=0b1110_0111_1110_0111)となる
	//
	//----------------------------------------------
  
	//メカコンボードのスレーブアドレスをセット
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) {
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//PortIN(機構部向け入力、16bit)の状態はメカコンI2Cのバイト 4, 5 に格納される
	//バイト4から2バイトリードを行うことにより、その情報を得る
	if ( i2cread(0x04, _glo_buf, 2) ){
		printf("Error: i2c read(). \n");
		exit(1);
	}

	//i2cリード成功
	//使用不可のビットを0として(~0x1818とand)、結果を返す
	return( ( (~0x1818) & ((_glo_buf[00] << 8) + _glo_buf[01])) );  
}

void 
nctrb_mc_io_writePortOUT1500 (WORD value)
{
	//----------------------------------------------
	//	ポートの情報：
	//		メカコン基板の機構部向け信号 出力 ポート
	//		OUT15 14 ... 01 00 の16本の信号線がある
	//		  
	//		メカコン基板の電源投入直後や、
	//		リセット時には各ポートは0(L,0V)出力となる
	//		(注意：オープンコレクタ出力部を除く)
	//		(Dラッチ入力部に1kohmプルダウン抵抗あり)
	//	
	//		なお、16本の信号線は下記 3 種類のコネクタ、
	//		モータードライバーで信号を共有しているので、
	//		取り扱い時は注意のこと
	//		(詳細についてはメカコン基板の回路図を参照)
	//	
	//		・出力コネクタ
	//		　□ CN_OUT15-8, □ CN_OUT7-0
	//			OUT15 ... 00 の 16本 の信号を出力
	//			対応するビット
	//			1 を設定　→	5V が出力される
	//			0 を設定　→	0V が出力される
	//			(Dラッチ使用、トーテムポール出力)
	//	
	//		・オープンコレクタ(Open Collector)出力コネクタ
	//		　□ CN_OUT15-8(OC)
	//			OUT15 ... 08 の 8本 の信号をOC出力
	//			通常出力コネクタとは動作、
	//			論理が異なるので注意のこと
	//			対応するビット
	//			1 を設定　→	OC On (0Vとなる)
	//			0 を設定　→	OC Off(Hi-Z)
	//			(Hi-Z→ハイインピーダンス状態、出力不定)
	//			(Trアレイ使用、定格50V/500mA程度)
	//	
	//		・機構部向けモーター駆動出力
	//			OUT07 ... 00 の 8本 の信号を使用し、
	//			モーターを駆動するためのコネクタ
	//			各信号とコネクタの対応
	//		　	□ CN_MOTOR3,  □ CN_MOTOR2,  □ CN_MOTOR1, □ CN_MOTOR0
	//			   OUT07,06		  OUT05,04		 OUT03,02	   OUT01,00
	//	
	//----------------------------------------------
	
	//メカコンボードのスレーブアドレスをセット
	if (ioctl(_glo_fd, I2C_SLAVE, 0x18) < 0) 
	{
		printf("Error: Unable to get bus access to talk to slave.\n");
		exit(1);
	}

	//PortOUT(機構部向け出力)はメカコンI2Cの 1, 2 バイトに書き込めばよい
	_glo_buf[00]	= 0x01;						//メカコンI2Cの書き込み先アドレス
	_glo_buf[01]	= (0xFF & (value >> 8));	//書き込むデータ 1byte目
	_glo_buf[02]	= (0xFF & (value >> 0));	//書き込むデータ 2byte

	if (i2cwrite(_glo_buf, 3))
	{
		printf("Error: i2c write(). \n");
		exit(1);
	}

	return (void)0;
}
