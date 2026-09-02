// cl: /DNDEBUG /MD /EHsc
// readable body of ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
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

struct BfmeControlBarOverrideNode
{
	void *next;
	AsciiString key;
	const CommandButton *button;
};

class ControlBarOverrideMapABI
{
public:
	BfmeControlBarOverrideNode *_M_find(const AsciiString &key) const;
	BfmeControlBarOverrideNode *find(const AsciiString &key) const
	{
		return _M_find(key);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
private:
	char pad[0x20];
	ControlBarOverrideMapABI controlBarOverrides;

public:
	bool findControlBarOverride(const AsciiString &commandSetName, int slot,
		const CommandButton *&commandButton) const;
};

bool GameLogic::findControlBarOverride(const AsciiString &commandSetName, int slot,
	const CommandButton *&commandButton) const
{
	char buffer[256];
	buffer[0] = '0' + slot;
	strcpy(&buffer[1], commandSetName.str());

	BfmeControlBarOverrideNode *entry;
	{
		AsciiString key(buffer);
		const ControlBarOverrideMapABI *map = &controlBarOverrides;
		entry = map->find(key);
	}
	if (entry)
	{
		commandButton = entry->button;
		return true;
	}
	return false;
}
