#define EPSON_ARM7
#define BLD_DECTALK_DLL
#define ARM7
#define ACNA
#define i386
#define ARM7_NOSWI
#define ENGLISH
#define ENGLISH_US

#include "epsonapi.h"

const unsigned char sp_main_dict[]= 
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00};

void sp_lts_loop_2(LPTTS_HANDLE_T phTTS,unsigned short *input)
{
}

int sp_lts_main(LPTTS_HANDLE_T phTTS)
{
	return(0);
}
