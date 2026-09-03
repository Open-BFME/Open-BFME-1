// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1ShellMenuScheme@@QAE@XZ: Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp
// Open-BFME5: convert ShellMenuScheme::~ShellMenuScheme to clean C++.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned short UnsignedShort;

void __cdecl bfmeFreeScalar(void *block);

inline void __cdecl operator delete(void *block)
{
	bfmeFreeScalar(block);
}

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
	~AsciiString();

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeImage
{
	public:
	~ShellMenuSchemeImage()
	{
		m_image = 0;
	}

	AsciiString m_name;
	Int m_position[2];
	Int m_size[2];
	void *m_image;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeLine
{
	public:
	~ShellMenuSchemeLine()
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuScheme
{
public:
	~ShellMenuScheme();

	AsciiString m_name;
	typedef _STL::list<ShellMenuSchemeImage *> ShellMenuSchemeImageList;
	ShellMenuSchemeImageList m_imageList;
	typedef _STL::list<ShellMenuSchemeLine *> ShellMenuSchemeLineList;
	ShellMenuSchemeLineList m_lineList;
};

ShellMenuScheme::~ShellMenuScheme()
{
	ShellMenuSchemeImageList::iterator it = m_imageList.begin();
	while (it != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *it;
		it = m_imageList.erase(it);
		if (image)
			delete image;
	}

	ShellMenuSchemeLineList::iterator lineIt = m_lineList.begin();
	while (lineIt != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *lineIt;
		lineIt = m_lineList.erase(lineIt);
		if (line)
			delete line;
	}
}
