// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring8outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?findScreenByFilename@Shell@@QAEPAVWindowLayout@@VAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define NULL 0

template <typename T>
class StringBase
{
public:
	Int compareNoCase(const StringBase<T> &that) const throw();

private:
	void *m_data;
};

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_len == 0;
	}

	Int compareNoCase(const AsciiString &that) const throw()
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&that);
	}

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	AsciiString getFilename(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	enum { MAX_SHELL_STACK = 16 };
	WindowLayout *findScreenByFilename(AsciiString filename);

protected:
	char m_bfmeBase[8];
	WindowLayout *m_screenStack[16];
};

// ?findScreenByFilename@Shell@@QAEPAVWindowLayout@@VAsciiString@@@Z
WindowLayout *Shell::findScreenByFilename(AsciiString filename)
{
	if (filename.isEmpty())
		return NULL;

	WindowLayout *screen;
	Int i;
	for (i = 0; i < MAX_SHELL_STACK; i++)
	{
		screen = m_screenStack[i];
		if (screen && filename.compareNoCase(screen->getFilename()) == 0)
			return screen;
	}

	return NULL;
}
