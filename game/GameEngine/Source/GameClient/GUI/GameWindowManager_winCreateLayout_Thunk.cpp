// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?winCreateLayout@GameWindowManager@@UAEPAVWindowLayout@@VAsciiString@@@Z: game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp
// Retail RVA 0x004889A0, 257 bytes (ret 4): BFME's winCreateLayout. Zero Hour
// newed a WindowLayout and let it load the file; BFME loads a WindowLayoutInfo
// first (WindowLayoutInfo::load, 0x00487870), returns NULL when that fails,
// hands the info to its +0x10 create callback inside try/catch(...) when one is
// set (a __stdcall pointer: retail pops no argument), and otherwise news a
// 0x24-byte WindowLayout and passes it the info
// (0x00497CE0 through ILT 0x0000C0A4, pinned under an address-derived name).
// Layout of WindowLayoutInfo follows WindowLayoutInfoConstructor.cpp.

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class WindowLayout;
class WindowLayoutInfo;

typedef WindowLayout *(__stdcall *WindowLayoutCreateFunc)(WindowLayoutInfo *info);

class WindowLayoutInfo
{
public:
	WindowLayoutInfo();
	~WindowLayoutInfo();
	bool load(AsciiString filename);

	unsigned int version;
	void *init;
	void *update;
	void *shutdown;
	WindowLayoutCreateFunc _bfme_unk_10;
	AsciiString initNameString;
	AsciiString updateNameString;
	AsciiString shutdownNameString;
	AsciiString _bfme_unk_20;
	AsciiString _bfme_unk_24;
	void *windows;
};

class WindowLayout
{
public:
	WindowLayout();

private:
	unsigned char m_unmodelled[0x24];
};

// 0x00497CE0, reached through ILT 0x0000C0A4 and pinned there under this name.
class BfmeQuickMatchScreenBase
{
	friend class GameWindowManager;
private:
	void bfmeAttach(void *info);
};

class GameWindowManager
{
public:
	virtual WindowLayout *winCreateLayout(AsciiString filename);
};

// ?winCreateLayout@GameWindowManager@@UAEPAVWindowLayout@@VAsciiString@@@Z
WindowLayout *GameWindowManager::winCreateLayout(AsciiString filename)
{
	WindowLayoutInfo info;
	if (!info.load(filename))
		return 0;

	WindowLayout *layout;
	if (info._bfme_unk_10)
	{
		try
		{
			layout = info._bfme_unk_10(&info);
		}
		catch (...)
		{
			return 0;
		}
	}
	else
	{
		layout = new WindowLayout;
		((BfmeQuickMatchScreenBase *)layout)->bfmeAttach(&info);
	}
	return layout;
}
