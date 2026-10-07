// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: the anonymous retail destructor at 0x002DE780, 89 bytes,
// converted from the game/gen_asm naked dump to real C++.
//
// The class is NOT identified and the earlier SubObjectsUpgradeModuleData lead
// was refuted (that name is already claimed at 0x002D8A60 by a 343-byte body
// destroying five 12-byte members).  What the bytes do fix is the ABI:
// a polymorphic base whose virtual destructor is the body behind the thunk at
// 0x0004A430 (retail 0x002DAB10), sized 0x60, followed by exactly two 4-byte
// AsciiString members at this+0x60 and this+0x64, both released through
// 0x00887940.  The name here is address-derived on purpose -- it disclaims
// identity rather than asserting one.

#include "ascii_string.h"

// The base dtor (ILT 0x4A430) is the matched ??1Mem002DAB10@@QAE@XZ
// (Mem002DAB10Destructor.cpp): polymorphic through anchor(), non-virtual dtor.
class __declspec(novtable) Mem002DAB10
{
public:
	virtual void anchor();
	~Mem002DAB10();

private:
	char m_opaque[0x5C];
};

class __declspec(novtable) Gen_002de780 : public Mem002DAB10
{
public:
	virtual ~Gen_002de780();

private:
	AsciiString m_60;
	AsciiString m_64;
};

Gen_002de780::~Gen_002de780()
{
}
