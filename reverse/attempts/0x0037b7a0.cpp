// ??0EmotionNugget@@QAE@XZ
// partial score=0.98 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"
#include <string.h>

typedef int Int;
typedef unsigned char Bool;

struct ZeroTwenty
{
	ZeroTwenty() { memset( value, 0, sizeof( value ) ); }
	Int value[20];
};

class EmotionNugget
{
public:
	EmotionNugget();

private:
	AsciiString m_name;             // +0x00
	Int m_04;
	Bool m_08;
	Bool m_09;
	unsigned char m_pad0A[2];
	Int m_0C;
	Int m_10;
	Int m_14;
	Int m_18;
	Int m_1C;
	Int m_20;
	Int m_24;
	Int m_28;
	Bool m_2C;
	Bool m_2D;
	unsigned char m_pad2E[2];
	Int m_30;
	Int m_34;
	Int m_38;
	AsciiString m_3C;
	Int m_40;
	Bool m_44;
	unsigned char m_pad45[3];
	Int m_48;
	Int m_4C;
	Int m_50;
	ZeroTwenty m_54;
	ZeroTwenty m_A4;
	AsciiString m_F4;
};

EmotionNugget::EmotionNugget()
	: m_name( AsciiString::TheEmptyString ),
	  m_04( -1 ),
	  m_08( 0 ),
	  m_09( 0 ),
	  m_0C( 0 ),
	  m_10( 0 ),
	  m_14( 0 ),
	  m_18( 0 ),
	  m_2C( 0 ),
	  m_2D( 0 ),
	  m_30( 0 ),
	  m_34( 0 ),
	  m_38( 0 ),
	  m_3C( AsciiString::TheEmptyString ),
	  m_40( 0 ),
	  m_44( 0 ),
	  m_48( -1 ),
	  m_4C( -1 ),
	  m_50( 0 ),
	  m_54(),
	  m_A4(),
	  m_F4( AsciiString::TheEmptyString )
{
	m_24 = 0;
	m_1C = 0;
	m_28 = -1;
	m_20 = -1;
}
