// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The member at +0x30 is a WinInstanceData: retail 0x00479B80 calls
// WinInstanceData::getText (0x00479B00, via ILT 0x000424D3) and returns its
// UnicodeString through the hidden return pointer.
#include "unicode_string.h"

class WinInstanceData
{
public:
	UnicodeString getText();
};

class BfmeThingDPG
{
public:
	UnicodeString bfmeGoDPG();
	unsigned char m_bfmeHead[0x30];
	WinInstanceData m_bfmeSub;
};

UnicodeString BfmeThingDPG::bfmeGoDPG()
{
	return m_bfmeSub.getText();
}
