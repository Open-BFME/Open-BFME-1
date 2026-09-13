// readable body of ?setControlBarOverride@GameLogic@@QAEXABVAsciiString@@HPBVCommandButton@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
#include <string.h>

class CommandButton;

extern const char g_NAMEKEY_empty_string;

struct BfmeAsciiStringBuffer
{
	char header[8];
	char data[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

	const char *str() const
	{
		return buffer != 0 ? buffer->data : &g_NAMEKEY_empty_string;
	}

private:
	BfmeAsciiStringBuffer *buffer;
};

class ControlBarOverrideMapABI
{
public:
	const CommandButton *&findOrInsert(const AsciiString &key);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
private:
	char pad[0x20];
	ControlBarOverrideMapABI controlBarOverrides;

public:
	void setControlBarOverride(const AsciiString &commandSetName, int slot,
		const CommandButton *commandButton);
};

void GameLogic::setControlBarOverride(const AsciiString &commandSetName, int slot,
	const CommandButton *commandButton)
{
	char buffer[256];
	buffer[0] = '0' + slot;
	strcpy(&buffer[1], commandSetName.str());
	AsciiString key(buffer);
	controlBarOverrides.findOrInsert(key) = commandButton;
}
