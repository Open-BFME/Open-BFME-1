// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: thiscall wrapper that feeds a C string to Debug::ExecCommand
// as a [start, end) pair, measuring the end in place. ecx is live this, so
// the inlined length scan uses ebx for the current byte.

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
	void ExecCommand(const char *cmdstart, const char *cmdend);

public:
	void Command(const char *cmd);
};

// ?Command@Debug@@QAEXPBD@Z
void Debug::Command(const char *cmd)
{
	if (cmd)
		ExecCommand(cmd, cmd + strlen(cmd));
}
