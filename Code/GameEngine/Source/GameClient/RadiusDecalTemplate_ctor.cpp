// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0RadiusDecalTemplate@@: Code/GameEngine/Source/GameClient/RadiusDecal.cpp

// RadiusDecalTemplate's constructor, retail 0x00458830.
//
// A fresh translation unit rather than the vendored RadiusDecal.cpp, because
// BFME's template is not Zero Hour's: it carries a SECOND AsciiString at +0x04
// and four more dwords at +0x20 through +0x2C, and its throb time is a float
// rather than an UnsignedInt frame count.
//
// Both strings are copy constructed from AsciiString::TheEmptyString at
// 0x01336E50 through StringBase<char>'s private copy constructor, which is what
// puts the exception frame on the function. The defaults that follow are the
// shadow style 0x20, one for each of the two opacities, a thousand for the
// throb time, no colour, and visible to the owning player only.
#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();

private:
	AsciiString m_name;						// +0x00
	AsciiString m_secondName;				// +0x04
	int m_shadowType;						// +0x08
	float m_minOpacity;						// +0x0C
	float m_maxOpacity;						// +0x10
	float m_opacityThrobTime;				// +0x14
	unsigned int m_color;					// +0x18
	bool m_onlyVisibleToOwningPlayer;		// +0x1C
	unsigned int m_unmodelled_20;			// +0x20
	unsigned int m_unmodelled_24;			// +0x24
	unsigned int m_unmodelled_28;			// +0x28
	unsigned int m_unmodelled_2C;			// +0x2C
};

// ??0RadiusDecalTemplate@@QAE@XZ
RadiusDecalTemplate::RadiusDecalTemplate()
	: m_name( AsciiString::TheEmptyString ),
		m_secondName( AsciiString::TheEmptyString ),
		m_shadowType( 0x20 ),
		m_minOpacity( 1.0f ),
		m_maxOpacity( 1.0f ),
		m_opacityThrobTime( 1000.0f ),
		m_color( 0 ),
		m_onlyVisibleToOwningPlayer( true ),
		m_unmodelled_20( 0 ),
		m_unmodelled_24( 0 ),
		m_unmodelled_28( 0 ),
		m_unmodelled_2C( 0 )
{
}
