#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include <stdexcept>
#include <chrono>

enum MsgBoxType {
	MSGBOX_NORMAL = MB_OK,
	MSGBOX_INFO = MB_OK | MB_ICONINFORMATION,
	MSGBOX_WARN = MB_OK | MB_ICONWARNING,
	MSGBOX_ERROR = MB_OK | MB_ICONERROR
};

inline void MsgBox(const char* msg, const char* title, MsgBoxType type, ...) {
	if (msg == NULL)
		return;

	if (strlen(msg) <= 0)
		return;

	// funny
	char* buffer = new char[8196];
	va_list args;
	va_start(args, type);
	vsnprintf(buffer, 8196, msg, args);
	MessageBox(NULL, buffer, title, type);
	delete[] buffer;
}

#define Error(_MSG, ...) \
	_Error(_MSG, __LINE__, __FILE__, __VA_ARGS__ );


// This looks like ass
inline void _Error( const char* msg, unsigned int line, const char* fileName ... )
	
{
	// funny
	char* buffer = new char[4096];
	va_list args;
	va_start(args, msg);
	vsnprintf(buffer, 4096, msg, args);
	va_end(args);
	MsgBox(
		"Dennis Error!\n\nFile: %s\nLine: %u\n\n%s",
		"Dennis Error",
		MSGBOX_ERROR,
		fileName,
		line,
		buffer
	);
	DebugBreak();
	
	throw std::runtime_error(msg);

	delete[] buffer;
}

// PATH STUFF
inline void getEXEPath(int size, char* buffer) {
	GetCurrentDirectory(size, buffer);
}

inline bool fileExists(char* filePath) {
	if (FILE* file = fopen(filePath, "r"))
		return true;
	else
		return false;
}

long double curtime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}

#endif // UTILITY_H