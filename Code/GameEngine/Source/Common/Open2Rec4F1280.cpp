// Retail 0x004F1280: default constructor for the three-string, ten-word
// record paired with the copy constructor recovered at 0x004F1120.
//
// The record is kept local to this conversion until its original public type
// is recovered.  Its layout and initialization order are constrained by the
// neighboring retail copy body and by the WOL lobby construction sites.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "Common/AsciiString.h"

class Open2Rec4F1280
{
public:
	Open2Rec4F1280();

	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};

// @??0Open2Rec4F1280@@QAE@XZ 0x004F1280
Open2Rec4F1280::Open2Rec4F1280()
	: m_at00(), m_at04(), m_at08()
{
	m_at00 = m_at04 = m_at08 = AsciiString::TheEmptyString;
	m_at28 = m_at0c = m_at10 = m_at1c = m_at2c = m_at30 = m_at14 = m_at18 = 0;
	m_at20 = m_at24 = -1;
}
