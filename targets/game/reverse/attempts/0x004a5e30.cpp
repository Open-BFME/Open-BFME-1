// ?populateCommand@ControlBar@@IAEXPAVObject@@_N@Z
// partial score=0.965 date=2026-09-28
// Best current body for ?populateCommand@ControlBar@@IAEXPAVObject@@_N@Z.
// The matched caller at 0x0049E780 passes Object* and Bool through ILT 0x0000D495.
// This excerpt compiled in ControlBar.cpp and probed at 1345 of 1381 bytes (0.965).
// The separate TU changed STLport cleanup code, so keep this in the original TU context.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/controlbarlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

struct BfmePopulateCommandButtonView
{
	char pad00[ 0x10 ];
	int m_command;
	BfmePopulateCommandButtonView *m_next;
	UnsignedInt m_options;
	unsigned char m_unmodelled_01c[ 0x34 - 0x1c ];
	SpecialPowerTemplate *m_specialPower;
	unsigned char m_unmodelled_038[ 0x68 - 0x38 ];
	AsciiString m_text;
	unsigned char m_unmodelled_06c[ 0x84 - 0x6c ];
	std::vector<int> m_science;
	unsigned char m_unmodelled_090[ 0xa0 - 0x90 ];
	int m_specialIndex;
	unsigned char m_unmodelled_0a4[ 0x14d - 0xa4 ];
	unsigned char field14d;
	unsigned char m_unmodelled_14e[ 4 ];
	unsigned char field152;
	unsigned char field153;

	int getCommandType() const { return m_command; }
	UnsignedInt getOptions() const { return m_options; }
	SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	const std::vector<int> &getScienceVec() const { return m_science; }
	BfmePopulateCommandButtonView *getNext() const { return m_next; }
	void Rva0049BA80( Object *object, Bool refresh ) const;
	void bfmeCopyFrom( const BfmePopulateCommandButtonView *button, Bool dirty ) const;
};
#pragma comment(linker, "/alternatename:?Rva0049BA80@BfmePopulateCommandButtonView@@QBEXPAVObject@@_N@Z=?j_00006938@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeCopyFrom@BfmePopulateCommandButtonView@@QBEXPBV1@_N@Z=?j_00001947@@YAXXZ")

class BfmePopulateCommandSetLookupView
{
public:
	const CommandSet *findCommandSet( const AsciiString &name );
};
#pragma comment(linker, "/alternatename:?findCommandSet@BfmePopulateCommandSetLookupView@@QAEPBVCommandSet@@ABVAsciiString@@@Z=?j_00048cca@@YAXXZ")

class BfmePopulateCommandButtonLookupView
{
public:
	const CommandButton *getCommandButton( int index ) const;
};
#pragma comment(linker, "/alternatename:?getCommandButton@BfmePopulateCommandButtonLookupView@@QBEPBVCommandButton@@H@Z=?j_00003f80@@YAXXZ")

class BfmePopulateControlCommandView
{
public:
	void setControlCommand( GameWindow *window, const CommandButton *button );
};
#pragma comment(linker, "/alternatename:?setControlCommand@BfmePopulateControlCommandView@@QAEXPAVGameWindow@@PBVCommandButton@@@Z=?setControlCommand@ControlBar@@QAEXPAVGameWindow@@PBVCommandButton@@@Z")

class BfmePopulateRallyPointView
{
public:
	void showRallyPoint( const Coord3D *location );
};
#pragma comment(linker, "/alternatename:?showRallyPoint@BfmePopulateRallyPointView@@QAEXPBUCoord3D@@@Z=?showRallyPoint@ControlBar@@IAEXPBUCoord3D@@@Z")

class BfmePopulateButtonImageView
{
public:
	void setButtonImage( const Image *image ) const;
};
#pragma comment(linker, "/alternatename:?setButtonImage@BfmePopulateButtonImageView@@QBEXPBVImage@@@Z=?j_0002a7ed@@YAXXZ")

class BfmePopulateGameWindowCloseView
{
public:
	void bfmeClose( Bool hide );
};
#pragma comment(linker, "/alternatename:?bfmeClose@BfmePopulateGameWindowCloseView@@QAEX_N@Z=?j_00027f2a@@YAXXZ")

struct BfmePopulateControlBarView
{
	char pad00[ 0x28 ];
	BfmePopulateCommandButtonView *m_commandButtons;
	unsigned char m_unmodelled_02c[ 0xd4 ];
	GameWindow *m_commandWindows[ 20 ];
	unsigned char m_unmodelled_150[ 0x50 ];
	GameWindow *m_overlayWindows[ 20 ];
	unsigned char m_unmodelled_1f0[ 0x100 ];
	void *m_overlaySink;
};

struct BfmePopulateCommandSetOverride
{
	char pad[ 0x2c ];
	AsciiString m_commandSetName;
};

class BfmePopulateObjectOverrideView
{
public:
	BfmePopulateCommandSetOverride *getOverride();
};
#pragma comment(linker, "/alternatename:?getOverride@BfmePopulateObjectOverrideView@@QAEPAUBfmePopulateCommandSetOverride@@XZ=?j_0002bf85@@YAXXZ")

class BfmePopulateObjectStore
{
public:
	const Image *getImage( int index );
	const ThingTemplate *getTemplate( int index );
};
#pragma comment(linker, "/alternatename:?getImage@BfmePopulateObjectStore@@QAEPBVImage@@H@Z=?j_0004a66f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getTemplate@BfmePopulateObjectStore@@QAEPBVThingTemplate@@H@Z=?j_00002135@@YAXXZ")

struct BfmePopulatePlayerView
{
	char pad[ 0x684 ];
	BfmePopulateObjectStore m_objectStore;
};

class BfmePopulateCommandTextView
{
public:
	Bool take( AsciiString &text );
};
#pragma comment(linker, "/alternatename:?take@BfmePopulateCommandTextView@@QAE_NAAVAsciiString@@@Z=?j_00046c18@@YAXXZ")

class BfmePopulatePlayerListView
{
public:
	unsigned char isLocalAlliedWith( Object *object );
	char pad[ 0x0c ];
	Player *m_localPlayer;
};
#pragma comment(linker, "/alternatename:?isLocalAlliedWith@BfmePopulatePlayerListView@@QAEGPAUObject@@@Z=?j_00003a85@@YAXXZ")

class BfmePopulateOpenContain
{
};

class BfmePopulateContainView
{
public:
	virtual BfmePopulateOpenContain *asOpenContain();
	virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual Bool slot45();
};

struct BfmePopulateObjectContainView
{
	unsigned char pad00[ 0x1fc ];
	BfmePopulateContainView *m_contain;

	BfmePopulateContainView *getContain() const { return m_contain; }
};

class BfmePopulateExitInterfaceView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual const Coord3D *slot08();
};

class BfmePopulateGlobalsView
{
public:
	void updateContext();
	void updateObject( Object *object );
};
#pragma comment(linker, "/alternatename:?updateContext@BfmePopulateGlobalsView@@QAEXXZ=?j_0003367c@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateObject@BfmePopulateGlobalsView@@QAEXPAVObject@@@Z=?j_0001f0d7@@YAXXZ")

class BfmePopulateControlBarContextCommandView
{
public:
	void call();
};
#pragma comment(linker, "/alternatename:?call@BfmePopulateControlBarContextCommandView@@QAEXXZ=?j_0003672d@@YAXXZ")

class BfmePopulateClearAt004B1720
{
public:
	void clear();
};
#pragma comment(linker, "/alternatename:?clear@BfmePopulateClearAt004B1720@@QAEXXZ=?j_00033f19@@YAXXZ")

class Rva004B19E0
{
public:
	void apply( void *windows );
};

class Rva004A4090WindowVec : public std::vector<GameWindow *>
{
public:
	void reserve20( unsigned count );
};
#pragma comment(linker, "/alternatename:?reserve20@Rva004A4090WindowVec@@QAEXI@Z=?j_00046f4c@@YAXXZ")

#define m_commandButtons (((BfmePopulateControlBarView *)this)->m_commandButtons)
#define m_commandWindows (((BfmePopulateControlBarView *)this)->m_commandWindows)
#define field1a0 (((BfmePopulateControlBarView *)this)->m_overlayWindows)
#define field2f0 ((Rva004B19E0 *)((BfmePopulateControlBarView *)this)->m_overlaySink)

void ControlBar::populateCommand( Object *object, Bool refresh )
{
	Player *player = object->getControllingPlayer();
	resetContainData();
	const CommandSet *commandSet = ((BfmePopulateCommandSetLookupView *)TheControlBar)->findCommandSet( object->getCommandSetString() );
	BfmePopulateCommandSetOverride *overrideRecord = ((BfmePopulateObjectOverrideView *)object)->getOverride();
	if( overrideRecord )
		commandSet = ((BfmePopulateCommandSetLookupView *)TheControlBar)->findCommandSet( overrideRecord->m_commandSetName );
	if( !commandSet )
	{
		if( Glo012F4B98 )
			((BfmePopulateGlobalsView *)Glo012F4B98)->updateContext();
		return;
	}
	int i;
	for( i = 0; i < 20; ++i )
	{
		if( m_commandWindows[ i ] )
		{
			const CommandButton *button = ((const BfmePopulateCommandButtonLookupView *)commandSet)->getCommandButton( i );
			if( !button )
				((BfmePopulateGameWindowCloseView *)m_commandWindows[ i ])->bfmeClose( true );
			else
				((BfmePopulateCommandButtonView *)button)->Rva0049BA80( object, false );
			((BfmePopulateControlCommandView *)this)->setControlCommand( m_commandWindows[ i ], button );
		}
	}
	BfmePopulateContainView *contain = ((BfmePopulateObjectContainView *)object)->getContain();
	if( contain && contain->slot45() )
		doTransportInventoryUI( object, commandSet );
	int specialIndex = 0;
	for( i = 0; i < 20; ++i )
	{
		const CommandButton *button = ((const BfmePopulateCommandButtonLookupView *)commandSet)->getCommandButton( i );
		BfmePopulateCommandButtonView *b = (BfmePopulateCommandButtonView *)button;
		if( !b || !b->field152 )
			continue;
		if( b->getOptions() & 0x80000 )
		{
			if( m_commandWindows[ i ] )
				((BfmePopulateGameWindowCloseView *)m_commandWindows[ i ])->bfmeClose( true );
			continue;
		}
		if( contain && b->field153 )
		{
			BfmePopulateOpenContain *open = contain->asOpenContain();
			if( open && !*((const unsigned char *)open + 0xb6) )
				continue;
		}
		if( b->getCommandType() == 0x2c )
		{
			if( !((BfmePopulatePlayerListView *)ThePlayerList)->isLocalAlliedWith( object ) )
			{
				((BfmePopulateGameWindowCloseView *)m_commandWindows[ i ])->bfmeClose( true );
				continue;
			}
			const Image *image = ((BfmePopulatePlayerView *)player)->m_objectStore.getImage( specialIndex );
			BfmePopulateCommandTextView *textTemplate = (BfmePopulateCommandTextView *)((BfmePopulatePlayerView *)player)->m_objectStore.getTemplate( specialIndex );
			if( image && textTemplate )
			{
				((BfmePopulateButtonImageView *)button)->setButtonImage( image );
				AsciiString text;
				if( textTemplate->take( text ) )
					b->m_text = text;
				if( m_commandWindows[ i ] )
					((BfmePopulateControlCommandView *)this)->setControlCommand( m_commandWindows[ i ], button );
				b->m_text.clear();
				b->m_specialIndex = specialIndex;
			}
			else
				b->m_specialIndex = -1;
			++specialIndex;
		}
		if( b->getCommandType() == 0xf )
			continue;
		if( m_commandWindows[ i ] )
		{
			((BfmePopulateGameWindowCloseView *)m_commandWindows[ i ])->bfmeClose( false );
			m_commandWindows[ i ]->winEnable( true );
			if( b->field14d )
				m_commandWindows[ i ]->winSetStatus( 0x4000000U );
			else
				m_commandWindows[ i ]->winClearStatus( 0x4000000U );
		}
		if( ( b->getOptions() & 0x80 ) && b->getSpecialPowerTemplate() )
		{
			SpecialPowerTemplate *power = b->getSpecialPowerTemplate();
			if( power->getRequiredScience() != -1 )
			{
				if( !player->hasScience( (ScienceType)power->getRequiredScience() ) )
				{
					if( m_commandWindows[ i ] )
						((BfmePopulateGameWindowCloseView *)m_commandWindows[ i ])->bfmeClose( true );
				}
				else
				{
					int bestIndex = -1;
					ScienceType science;
					for( unsigned scienceIndex = 0; scienceIndex < b->getScienceVec().size(); ++scienceIndex )
					{
						science = (ScienceType)b->getScienceVec()[ scienceIndex ];
						if( player->hasScience( science ) )
							bestIndex = scienceIndex;
						else
						break;
					}
					if( bestIndex != -1 )
					{
						science = (ScienceType)b->getScienceVec()[ bestIndex ];
						for( BfmePopulateCommandButtonView *candidate = m_commandButtons; candidate; candidate = candidate->getNext() )
						{
							if( candidate->getCommandType() == 0x18 && !candidate->getScienceVec().empty() && candidate->getScienceVec()[ 0 ] == science )
								((BfmePopulateCommandButtonView *)button)->bfmeCopyFrom( candidate, true );
						}
					}
				}
			}
		}
	}
	if( object->isLocallyControlled() || !((BfmePopulatePlayerListView *)ThePlayerList)->m_localPlayer->isPlayerActive() )
	{
		BfmePopulateExitInterfaceView *exitInterface = (BfmePopulateExitInterfaceView *)object->getObjectExitInterface();
		if( exitInterface )
			((BfmePopulateRallyPointView *)this)->showRallyPoint( exitInterface->slot08() );
	}
	((BfmePopulateControlBarContextCommandView *)this)->call();
	((BfmePopulateGlobalsView *)Glo012F4B98)->updateObject( object );
	if( field2f0 )
	{
		if( !object->isLocallyControlled() && ((BfmePopulatePlayerListView *)ThePlayerList)->m_localPlayer->isPlayerActive() )
		{
			((BfmePopulateClearAt004B1720 *)field2f0)->clear();
			return;
		}
		Rva004A4090WindowVec windows;
		windows.reserve20( 20U );
		for( int k = 0; k < 20; ++k )
		{
			GameWindow *window = field1a0[ k ];
			if( window )
				windows.push_back( window );
		}
		((Rva004B19E0 *)field2f0)->apply( &windows );
	}
}


#undef field2f0
#undef field1a0
#undef m_commandWindows
#undef m_commandButtons
