// Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved \\

#include "dennis.h"

#include "Windows.h"
#include <ctime>
#include <random>

void CDennis::initDennis(CDecTalk* decTalk) {
	srand(clock());

	decTalkPtr = decTalk;

	decTalkPtr->ttsSetVolume(25);

	dennisActive = true;

	mainLoop();
}

void CDennis::shutdownDennis() {
	decTalkPtr->shutdownTTS();

	dennisActive = false;
}

void CDennis::say(char* message) {
	if (strlen(message) < 0)
		return;

	decTalkPtr->ttsSay(message);

}

void CDennis::mainLoop() {
	while (dennisActive) {
		// If we don't sleep we use up around 8% of cpu
		Sleep(100);

		if (clock() > nextSayTime) {

			if (calcRandom(100, 10)) {
				say("[:nd]bitch.");
				setNextSayTime(rand() % (120 - 60 + 1) + 60);
				continue;
			}

			// It is intentional that it doesnt continue here
			if (calcRandom(100, 1)) {
				say("[:nd]slig-it.");
			}

			decTalkPtr->ttsSay("[:nd]dennis.");

			setNextSayTime(rand() % (120 - 60 + 1) + 60);
		}
	}
}

void CDennis::setNextSayTime(unsigned long nextTime) {
	nextSayTime = clock() + nextTime * 1000;
}

bool CDennis::calcRandom(unsigned int roof, unsigned int chance) {
	if (rand() % roof < chance) {
		return true;
	}
	else {
		return false;
	}
}