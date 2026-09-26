// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines: the
// call site encodes the base body at 0x00888400
// (??0?$StringBase@G@@AAE@ABV0@@Z). The delegation has to be visible here
// for this TU to encode the same call.
#include "string_base.h"

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();

	static UnicodeString TheEmptyString;

private:
	void *m_data;
};

class Rva00416BD0Src
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual UnicodeString getName();
};

class Rva00416BD0
{
	char m_pad[0x2D0];
	Rva00416BD0Src *m_2d0;

public:
	UnicodeString getName();
};

UnicodeString Rva00416BD0::getName()
{
	if (m_2d0)
		return m_2d0->getName();
	return UnicodeString::TheEmptyString;
}
