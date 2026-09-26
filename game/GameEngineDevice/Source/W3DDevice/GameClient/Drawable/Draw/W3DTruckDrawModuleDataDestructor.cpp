// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DTruckDrawModuleData destructor.  The matched module-data factory at
// 0x006BF4F0 allocates 0x1C4 bytes and calls the constructor at 0x0077F830.
// Retail's destructor at 0x0077F920 tears down the 21 consecutive strings at
// +0x15C..+0x1AC in reverse declaration order, then destroys the +0 base.

#include "ascii_string.h"

class S4Base0077C1F0
{
public:
	virtual ~S4Base0077C1F0();

private:
	char m_fields[ 0x158 ];
};

class W3DTruckDrawModuleData : public S4Base0077C1F0
{
public:
	virtual ~W3DTruckDrawModuleData();

private:
	AsciiString m_string00;
	AsciiString m_string01;
	AsciiString m_string02;
	AsciiString m_string03;
	AsciiString m_string04;
	AsciiString m_string05;
	AsciiString m_string06;
	AsciiString m_string07;
	AsciiString m_string08;
	AsciiString m_string09;
	AsciiString m_string10;
	AsciiString m_string11;
	AsciiString m_string12;
	AsciiString m_string13;
	AsciiString m_string14;
	AsciiString m_string15;
	AsciiString m_string16;
	AsciiString m_string17;
	AsciiString m_string18;
	AsciiString m_string19;
	AsciiString m_string20;
	char m_tail[ 0x14 ];
};

W3DTruckDrawModuleData::~W3DTruckDrawModuleData()
{
}
