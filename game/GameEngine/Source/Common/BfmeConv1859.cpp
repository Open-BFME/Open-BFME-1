// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// The room record is StringBase<char>-compatible.  Retail's twelve-byte
// element stride plus the copy this body performs at both of its return paths
// pin the shape: 0x00887B60 is
// ??0?$StringBase@D@@AAE@ABV0@@Z, the out-of-line StringBase copy
// constructor, and retail enters it directly (ECX = the hidden return slot,
// one stack argument = the source), so the record copy touches only the
// four-byte base and not the eight bytes behind it.
class BfmeRoomYF : public AsciiString
{
public:
	BfmeRoomYF(const AsciiString &other) : AsciiString(other) {}

	unsigned char m_bfmeBytesYF[8];
};

class BfmeOwnerYF
{
public:
	virtual void bfmeO00YF();
	virtual void bfmeO01YF();
	virtual void bfmeO02YF();
	virtual void bfmeO03YF();
	virtual void bfmeO04YF();
	virtual void bfmeO05YF();
	virtual void bfmeO06YF();
	virtual void bfmeO07YF();
	virtual void bfmeO08YF();
	virtual void bfmeO09YF();
	virtual void bfmeO10YF();
	virtual void bfmeO11YF();
	virtual void bfmeO12YF();
	virtual void bfmeO13YF();
	virtual void bfmeO14YF();
	virtual void bfmeO15YF();
	virtual void bfmeO16YF();
	virtual void bfmeO17YF();
	virtual void bfmeO18YF();
	virtual void bfmeO19YF();
	virtual void bfmeO20YF();
	virtual void bfmeO21YF();
	virtual void bfmeO22YF();
	virtual void bfmeO23YF();
	virtual void bfmeO24YF();
	virtual void bfmeO25YF();
	virtual void bfmeO26YF();
	virtual void bfmeO27YF();
	virtual void bfmeO28YF();
	virtual void bfmeO29YF();
	virtual void bfmeO30YF();
	virtual void bfmeO31YF();
	virtual void bfmeO32YF();
	virtual void bfmeO33YF();
	virtual void bfmeO34YF();
	virtual void bfmeO35YF();
	virtual void bfmeO36YF();
	virtual void bfmeO37YF();
	virtual void bfmeO38YF();
	virtual void bfmeO39YF();
	virtual void bfmeO40YF();
	virtual void bfmeO41YF();
	virtual void bfmeO42YF();
	virtual void bfmeO43YF();
	virtual void bfmeO44YF();
	virtual void bfmeO45YF();
	virtual bool bfmeReadyYF(int what);

	BfmeRoomYF bfmeGetYF(unsigned int index);

	unsigned char m_bfmeHeadYF[0x650];
	BfmeRoomYF m_bfmeRoomsYF[64];
	unsigned int m_bfmeCountYF;
};

BfmeRoomYF BfmeOwnerYF::bfmeGetYF(unsigned int index)
{
	if (bfmeReadyYF(4) && index < m_bfmeCountYF)
		return BfmeRoomYF(static_cast<const AsciiString &>(m_bfmeRoomsYF[index]));

	// retail 0x01336E50: AsciiString::TheEmptyString, the shared default the
	// miss path copies through the same StringBase constructor.
	return BfmeRoomYF(AsciiString::TheEmptyString);
}
