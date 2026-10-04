// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x004498D0 (302 B), reached from BfmeSinkBL::bfmeSubmitBL through ILT 0x00043603; owner stays address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "Common/AsciiString.h"
#include "GameClient/ClientRandomValue.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class Rva004498D0Client
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual UnsignedInt getFrame();
};

struct Rva004498D0GlobalData
{
	char m_padding[0xdd8];
	GameClientRandomVariable m_particleCursorBurstFactor;
};

class GameClient;
class GlobalData;
extern GameClient *TheGameClient;
extern GlobalData *TheWritableGlobalData;

// List payload: a frame number and a name, copied into each 16-byte STLport node.
struct Rva004498D0Entry
{
	Int m_frame;
	AsciiString m_name;
};

typedef _STL::list<Rva004498D0Entry, _STL::allocator<Rva004498D0Entry> > Rva004498D0List;

// Four random variables, then the list at +0x30 (the same layout the 0x00449790 constructor builds).
class Rva004488B0FourBlockRecord
{
public:
	void rva004498d0(AsciiString name, UnsignedInt count);

private:
	GameClientRandomVariable m_first;
	GameClientRandomVariable m_second;
	GameClientRandomVariable m_third;
	GameClientRandomVariable m_fourth;
	Rva004498D0List m_list;
};

void Rva004488B0FourBlockRecord::rva004498d0(AsciiString name, UnsignedInt count)
{
	Int total = (Int)(((Rva004498D0GlobalData *)TheWritableGlobalData)->m_particleCursorBurstFactor.getValue() * count + 0.5f);
	for (Int i = 0; i < total; ++i)
	{
		Rva004498D0Entry entry;
		entry.m_frame = (Int)(((Rva004498D0Client *)TheGameClient)->getFrame() + m_first.getValue());
		entry.m_name = name;
		m_list.push_front(entry);
	}
}
