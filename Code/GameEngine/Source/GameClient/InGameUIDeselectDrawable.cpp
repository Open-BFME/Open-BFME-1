// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// InGameUI::deselectDrawable (0x00446490): slot 57 (+0xE4) of InGameUI's table
// 0x00CF5B38, the slot InGameUIDeselectAllDrawables.cpp and
// Drawable::setSelectable call it through. Zero Hour's body, then a BFME-only
// reset of the 25 entries at this+0x44.

#include <list>
#include <algorithm>

class Drawable;

typedef _STL::list<Drawable *> BfmeDrawableList;

// Drawable+0x3AC is the selected flag; the out-of-line clear (0x00417240,
// carved as Rva00417240::run) tests and clears the same byte.
struct BfmeSelectedDrawable
{
	unsigned char m_unmodelled000[0x3ac];
	bool m_selected;										///< this+0x3AC
};

class Rva00417240
{
public:
	void run();
};

// TheControlBar's onDrawableDeselected (0x0049CBB0), under its ledger name.
class BfmeA993
{
public:
	void bfmeGo993A(int draw);
};

extern BfmeA993 *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }

private:
	unsigned char m_unmodelled000[0x3c];
	unsigned int m_frame;									///< this+0x3C
};

extern GameLogic *TheGameLogic;

struct BfmeInGameUIEntry44
{
	int m_value;											///< entry+0x00
	bool m_flag;											///< entry+0x04
	unsigned char m_unmodelled05[0x0f];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void deselectDrawable( Drawable *draw );

protected:
	void evaluateSoloNexus( Drawable *newlyAddedDrawable = 0 );

	// Index-checked: retail tests (unsigned)i < 25 on every pass of the loop.
	void resetEntry044( int i )
	{
		if( (unsigned int)i < 25 )
		{
			m_entries044[i].m_value = 0;
			m_entries044[i].m_flag = true;
		}
	}

private:
	unsigned char m_unmodelled004[0x14];
	BfmeDrawableList m_selectedDrawables;					///< this+0x18
	unsigned char m_unmodelled01C[0x28];
	BfmeInGameUIEntry44 m_entries044[25];					///< this+0x44
	unsigned char m_unmodelled238[0x31c];
	int m_selectCount;										///< this+0x554
	unsigned char m_unmodelled558[0x4];
	unsigned int m_frameSelectionChanged;					///< this+0x55C
};

// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z
void InGameUI::deselectDrawable( Drawable *draw )
{
	if( ((BfmeSelectedDrawable *)draw)->m_selected )
	{
		m_frameSelectionChanged = TheGameLogic->getFrame();

		// clear the selected bit out of the drawable
		((Rva00417240 *)draw)->run();

		// find the drawable entry in our list and remove it
		BfmeDrawableList::iterator findIt = _STL::find( m_selectedDrawables.begin(),
														m_selectedDrawables.end(),
														draw );
		m_selectedDrawables.erase( findIt );

		// keep out own internal count happy
		--m_selectCount;

		// evaluate whether our selection consists of exactly one angry mob
		evaluateSoloNexus();

		// the control needs to update its context sensitive display now
		TheControlBar->bfmeGo993A( (int)draw );

		for( int i = 0; i < 25; ++i )
			resetEntry044( i );
	}
}
