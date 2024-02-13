// Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved \\

#ifndef DENNIS_H
#define DENNIS_H

#include "dectalk.h"

class CDennis {
public:
	void initDennis(CDecTalk* decTalk);
	void shutdownDennis();

	bool calcRandom(unsigned int roof, unsigned int chance);

	void setNextSayTime(unsigned long time);

	void say(char* message);

	void mainLoop();
private:
	long nextSayTime = 0;

	bool dennisActive;

	CDecTalk* decTalkPtr;

};

#endif // DENNIS_H