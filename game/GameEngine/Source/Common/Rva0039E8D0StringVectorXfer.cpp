// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define ASCIISTRING_H
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
#include <vector>
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
class Rva0039E8D0Xfer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void xferAsciiString(AsciiString *value); // +0x68
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78(int *value);
};

typedef _STL::vector<AsciiString> Rva0039E8D0StringVector;

// 0x0039E8D0, called twice from 0x003A01E0 for the record vectors at +0/+0x0C.
// This is the loading-only path: slot +0x78 fills the signed count.
// The owner is unknown. The callers and retail body establish only this
// Xfer/vector ABI; retain the address in the function name.
void __stdcall Rva0039E8D0StringVectorXfer(
	Rva0039E8D0Xfer *xfer, Rva0039E8D0StringVector *vector)
{
	int count;
	xfer->slot78(&count);

	AsciiString value;
	for (int i = 0; i < count; ++i)
	{
		xfer->xferAsciiString(&value);
		vector->push_back(value);
	}
}
