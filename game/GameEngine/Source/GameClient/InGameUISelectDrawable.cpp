// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// InGameUI::selectDrawable (0x004462D0): slot 56 (+0xE0) of InGameUI's table
// 0x00CF5B38, next to deselectDrawable (slot 57, InGameUIDeselectDrawable.cpp).
// Zero Hour's body behind a BFME gate check: a drawable whose template carries
// kind-of bit 0x100 of the word at +0xD8 and whose object has a
// GateOpenAndCloseBehavior or GateProxyBehavior module asks that module first,
// and is not selected when it answers true. Then the same reset of the 25
// entries at this+0x44 as deselectDrawable.

#define _STLP_NO_EXCEPTIONS 1

#include <list>

class Drawable;

typedef _STL::list<Drawable *> BfmeDrawableList;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;							///< this+0x04
};

struct BfmeSelectTemplateView
{
	unsigned char m_unmodelled000[0xd8];
	unsigned int m_kindOfWordD8;							///< template+0xD8, tested for 0x100
};

class Module
{
public:
	virtual ~Module();
};

// The module both gate behaviours are asked through: Module at +4, and the
// query 0x001FCA90 under its address-derived ledger name.
class BfmeGateModuleBase
{
public:
	virtual ~BfmeGateModuleBase();
};

class Rva001FCA90Owner : public BfmeGateModuleBase, public Module
{
public:
	bool invoke();
};

class InGameUI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class InGameUI;

protected:
	Module *findModule( NameKeyType key ) const;
};

// Drawable: template at +0x04, object at +0xFC, selected flag at +0x3AC.
struct BfmeSelectDrawableView
{
	void *m_vtable;
	const Overridable *m_template;							///< this+0x04
	unsigned char m_unmodelled008[0xf4];
	Object *m_object;										///< this+0xFC
	unsigned char m_unmodelled100[0x2ac];
	bool m_selected;										///< this+0x3AC

	const BfmeSelectTemplateView *getTemplate() const
	{
		if( !m_template )
			return 0;
		return (const BfmeSelectTemplateView *)m_template->getFinalOverride();
	}
};

// friend_setSelected (0x0041BE30), under its ledger name.
class BfmeThingBXF
{
public:
	void bfmeGoBXF();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void onDrawableSelected( Drawable *draw );
};

extern ControlBar *TheControlBar;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void selectDrawable( Drawable *draw );

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

// ?selectDrawable@InGameUI@@UAEXPAVDrawable@@@Z
void InGameUI::selectDrawable( Drawable *draw )
{
	BfmeSelectDrawableView *view = (BfmeSelectDrawableView *)draw;

	// only if not selected already
	if( view->m_selected )
		return;

	unsigned int kindOfWordD8 = view->getTemplate()->m_kindOfWordD8;
	Object *obj;
	if( (kindOfWordD8 & 0x100) && (obj = view->m_object) != 0 )
	{
		static NameKeyType key_GateOpenAndCloseBehavior = TheNameKeyGenerator->nameToKey( "GateOpenAndCloseBehavior" );

		Rva001FCA90Owner *gate = static_cast<Rva001FCA90Owner *>( obj->findModule( key_GateOpenAndCloseBehavior ) );
		if( !gate )
			gate = static_cast<Rva001FCA90Owner *>( obj->findModule( TheNameKeyGenerator->nameToKey( "GateProxyBehavior" ) ) );
		if( gate && gate->invoke() )
			return;
	}

	m_frameSelectionChanged = TheGameLogic->getFrame();

	// set the selected bit on the drawable
	((BfmeThingBXF *)draw)->bfmeGoBXF();

	// add to our list of selected drawables
	m_selectedDrawables.push_front( draw );

	// keep our own internal count happy
	++m_selectCount;

	// evaluate whether our selection consists of exactly one angry mob
	evaluateSoloNexus( draw );

	// the control needs to update its context sensitive display now
	TheControlBar->onDrawableSelected( draw );

	for( int i = 0; i < 25; ++i )
		resetEntry044( i );
}
