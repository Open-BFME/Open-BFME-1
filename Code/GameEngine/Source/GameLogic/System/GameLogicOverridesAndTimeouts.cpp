// cl: /DNDEBUG /MD /EHsc
// readable body of ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// readable body of ?initTimeOutValues@GameLogic@@QAEXXZ: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
//
// Two GameLogic bodies that read the object's own fields, and between them
// place two of them: the control-bar override map at +0x20 and the
// progress-complete timeout array at +0x128. Each file previously declared
// GameLogic as everything-up-to-the-one-field-it-needed, so the class existed
// twice, both times wrong about everything else.
//
// findControlBarOverride keys the map on the slot digit prefixed to the
// command set name. initTimeOutValues (retail 0x00383740, ZH GameLogic.cpp:1512)
// stamps timeGetTime into one timeout slot per network player: TheNetwork is
// 0x012F7714, getNumPlayers is vslot +0x94, and the timeout array is the same
// BFME field processProgressComplete uses. timeGetTime is the ILT at
// 0x000481E4, not the import.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36();
	virtual int getNumPlayers(void);
};

extern NetworkInterface *TheNetwork;

extern "C" unsigned long __stdcall bfme_timeGetTime(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	bool findControlBarOverride(const AsciiString &commandSetName, int slot,
		const CommandButton *&commandButton) const;
	void initTimeOutValues(void);

private:
	char m_pad00[0x20];
	// Modelled by its ABI only: these bodies reach it through _M_find, never
	// through its own fields.
	ControlBarOverrideMapABI m_controlBarOverrides;		// +0x020
	char m_pad21[0x128 - 0x21];
	unsigned int m_progressCompleteTimeout[8];		// +0x128
};

// ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z
bool GameLogic::findControlBarOverride(const AsciiString &commandSetName, int slot,
	const CommandButton *&commandButton) const
{
	char buffer[256];
	buffer[0] = '0' + slot;
	strcpy(&buffer[1], commandSetName.str());

	BfmeControlBarOverrideNode *entry;
	{
		AsciiString key(buffer);
		const ControlBarOverrideMapABI *map = &m_controlBarOverrides;
		entry = map->find(key);
	}
	if (entry)
	{
		commandButton = entry->button;
		return true;
	}
	return false;
}

// ?initTimeOutValues@GameLogic@@QAEXXZ
void GameLogic::initTimeOutValues(void)
{
	if (!TheNetwork)
		return;
	int i = 0;
	if (TheNetwork->getNumPlayers() <= 0)
		return;
	unsigned int *p = m_progressCompleteTimeout;
	do
	{
		*p = bfme_timeGetTime();
		++i;
		++p;
	} while (i < TheNetwork->getNumPlayers());
}
