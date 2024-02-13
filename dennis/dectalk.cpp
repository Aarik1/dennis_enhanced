// Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved \\

#include "dectalk.h"

#pragma warning(push)
#pragma warning(disable : 4005)
#include <windows.h>
#include <mmsystem.h>
#include "../dectalk/dapi/src/API/TTSAPI.H"
#pragma warning(pop)

#include "../public/utility.h"

#include "stdio.h"

void CDecTalk::initTTS() {
	char* path = new char[MAX_PATH];
	getEXEPath(MAX_PATH, path);

	strcat(path, "\\dtalk_us.dic");

	printf(path);

	if (!fileExists(path))
		Error("Failed to find DecTalk dictionary file. Please reinstall Dennis.");

	delete[] path;

	MMRESULT status;

	// Copied from say.c
	status = TextToSpeechStartup(NULL, &ttsHandle, WAVE_MAPPER, 0);
	if (status != MMSYSERR_NOERROR) {
		/* ETT 11/04/98: BATS #233:
		if nodriver is returned this means that there is no audio device.
			try starting TTS again with DO_NOT_USE_AUDIO_DEVICE. */
		if (status == MMSYSERR_NODRIVER)
		{
			status = TextToSpeechStartup(NULL, &ttsHandle, WAVE_MAPPER, DO_NOT_USE_AUDIO_DEVICE);
			if (status != MMSYSERR_NOERROR) {
				if (status == MMSYSERR_ERROR) {
					Error("DECtalk dictionary not found.\n");
					return;
				}
				if (status == MMSYSERR_ALLOCATED) {
					Error("No more DECtalk License units available.\n");
					return;
				}
				if (status == MMSYSERR_NOMEM) {
					Error("Memory allocation error.\n");
					return;
				}
			}
		}
		/* ETT 11/04/98: add meaningful exit error output. */
		if ((status == MMSYSERR_ERROR) || (status == MMSYSERR_INVALPARAM)) {
			Error("DECtalk dictionary not found.\n");
			return;
		}
		if (status == MMSYSERR_ALLOCATED) {
			Error("No more DECtalk License units available.\n");
			return;
		}
		if (status == MMSYSERR_NOMEM) {
			Error("Memory allocation error.\n");
			return;
		}
	}
}

void CDecTalk::shutdownTTS() {
	TextToSpeechShutdown(ttsHandle);
}

void CDecTalk::ttsSetVolume(unsigned int newVolume) {
	MMRESULT res = TextToSpeechSetVolume(ttsHandle, VOLUME_ATTENUATION, newVolume);

	if (res != MMSYSERR_NOERROR)
	{
		Error("DECtalk failed to set volume!");
		return;
	}
}

void CDecTalk::ttsSay(char* sayStr) {
	if (strlen(sayStr) < 0)
		return;

	MMRESULT res = TextToSpeechSpeak(ttsHandle, sayStr, TTS_FORCE);

	if (res != MMSYSERR_NOERROR)
	{
		Error("DECtalk failed to generate speech!");
		return;
	}
}