// Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved \\

#include "dectalk.h"
#include "dennis.h"
#include "windows.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	CDecTalk* dectalk = new CDecTalk;
	dectalk->initTTS();

	CDennis* dennis = new CDennis;
	dennis->initDennis(dectalk);

	return 0;

}