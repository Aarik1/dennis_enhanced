#ifndef DECTALK_H
#define DECTALK_H

class CDecTalk {
public:
	void initTTS();
	void shutdownTTS();

	void ttsSetVolume(unsigned int newVolume);

	void ttsSay(char* sayStr);

private:
	void* ttsHandle = nullptr;
};

#endif // DECTALK_H