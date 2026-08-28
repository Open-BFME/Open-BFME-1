// cl: /DNDEBUG /MD /EHsc

// W3DInGameUI's constructor, retail 0x006FBE10. InGameUI's constructor - a name
// the ledger already has - then two vftable pointers and two parallel arrays
// cleared together.
//
// The clear is one loop over twenty-five entries touching both arrays per turn:
// retail walks a single pointer and reaches the lower array through a negative
// displacement of 0x64, which is exactly the distance between them. That is one
// loop in the source, not two.
//
// The two dwords after the arrays, at +0x1474 and +0x1478, are cleared outside
// it.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	InGameUI();

	virtual void inGameUIAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

// The store at +0x08 is a MEMBER with a vftable, not a second base: retail
// writes it AFTER the class's own pointer at +0x00, which is member-construction
// order. A second base is written first instead.
class W3DInGameUIHelper
{
public:
	W3DInGameUIHelper() {}

	virtual void w3dInGameUIHelperAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DInGameUI.h
class W3DInGameUI : public InGameUI
{
public:
	W3DInGameUI();

private:
	W3DInGameUIHelper m_helper;				// +0x08
	unsigned char m_unmodelled_0C[ 0x13AC - 0x0C ];
	Int m_first[ 25 ];						// +0x13AC
	Int m_second[ 25 ];						// +0x1410
	Int m_unmodelled_1474;					// +0x1474
	Int m_unmodelled_1478;					// +0x1478
};

// ??0W3DInGameUI@@QAE@XZ
W3DInGameUI::W3DInGameUI()
{
	for( Int i = 0; i < 25; ++i )
	{
		m_first[ i ] = 0;
		m_second[ i ] = 0;
	}

	m_unmodelled_1474 = 0;
	m_unmodelled_1478 = 0;
}
