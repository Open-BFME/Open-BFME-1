// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x003A95D0, 249 bytes. Its only caller is
// BfmeLwcmPointerVectorOwner::applyFound (0x003B8260), which looks up a
// BfmeLwcmFindResult through the campaign manager and hands this body each
// 4-byte entry of its own vector by address -- the ILT 0x00026EA9 pin in
// symbols.csv calls it applyPointer and types it void, but the body returns a
// bool in AL, so the body keeps an address-derived name instead.
//
// It is BfmeLivingWorldCampaignManager::findArmy with a different record: a
// vector at +0x0C of 0xDC-byte records (the 0x094F2095 reciprocal with sar 3),
// each asked for its name through ILT 0x0000CA95 -- pinned as
// Glo012F1024Item::name003A72F0 -- and compared with the argument; it answers
// whether any record carries that name.
#include "PreRTS.h"
#include <vector>

class Glo012F1024Item
{
public:
	AsciiString name003A72F0();

private:
	char m_unmodelled[ 0xDC ];
};

class BfmeLwcmFindResult
{
public:
	Bool containsName003A95D0( const AsciiString &name );

private:
	char m_unmodelled[ 0x0C ];
	std::vector<Glo012F1024Item> m_items;
};

// ?containsName003A95D0@BfmeLwcmFindResult@@QAE_NABVAsciiString@@@Z
Bool BfmeLwcmFindResult::containsName003A95D0( const AsciiString &name )
{
	for( UnsignedInt i = 0; i < m_items.size(); ++i )
	{
		if( m_items[ i ].name003A72F0().compare( name ) == 0 )
			return TRUE;
	}

	return FALSE;
}
