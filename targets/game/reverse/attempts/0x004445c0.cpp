// ?createMouseoverHint@InGameUI@@
// partial score=0.78 date=2026-09-25
// BANKED ATTEMPT (claude-opus-5-5, 2026-09-25) for InGameUI::createMouseoverHint
// at 0x004445C0 (2194 B, vtable 0x010F5B38 slot 30). Drop-in replacement for the
// ZH createMouseoverHint in Code/GameEngine/Source/GameClient/InGameUI.cpp (it
// relies on that TU's BfmeGameClientGarrisonView, BfmeMouseSetCursorView,
// BfmeUnicodeStringArg, bfmeMessageText and Rva002EE330PlayerList). Compiles; 2166 B
// against 2194, normalized instruction similarity 0.78. Open items, in order:
//  * frame is 0x54 not 0x58: retail keeps `player` in a stack slot ([esp+0x14])
//    and uses ebx for the EH-state constant 9; ours keeps player in ebx.
//  * the underWindow arrow+return block sits at +0x113 in retail (between the two
//    arms of `draw ? draw->object : NULL`); ours places it after the isEmpty block.
//  * by-value AsciiString args (fetch(label), fetch(txtTemp), format's "ThingTemplate:%s")
//    need an AsciiString twin of BfmeUnicodeStringArg for retail's EH saved-esp order;
//    the L"%s
%s" format arg likewise.
//  * esi/edi swapped in the SpecialDisguiseUpdate block (module vs local player).
// Unresolved REL32 names still needing pins before landing: the view spellings
// ?setCursorTooltip@BfmeHintMouseTooltipView@@... (ILT 0x000346E9),
// ?getPlayerDisplayName@BfmePlayerDisplayNameView@@QAE?AVUnicodeString@@XZ (0x00098FD0),
// ?rva004C15D0@Rva004C15D0ControlBar@@QAEXPAVBfmeHintRecordBase010EDAA0@@@Z
// (0x004C15D0, thiscall, ret 4, still a gen_asm dump); move the two record classes out
// of the anonymous namespace first or the parameter mangles with ?A0x...
//-------------------------------------------------------------------------------------------------
/** Details of what is mouse hovered over right now are in this message.  Terrain might result
	* in just a tooltip.  An object might get a tooltip and show its hit points.
 */
//-------------------------------------------------------------------------------------------------
// Retail InGameUI::createMouseoverHint is InGameUI vtable slot 30 (+0x78 of
// table 0x010F5B38).  BFME keeps Zero Hour's skeleton but drops the mob-member
// and AI-debug branches, takes the disguise template from a module, gates the
// tooltip on shroud at either the object or the terrain under the mouse, and
// tells the control bar about locally owned structures.  Everything below is
// spelled at BFME's offsets through views.
namespace {

#define BFME_MOH_SLOT(n) virtual void bfmeSlot##n() = 0;

// GameWindow's slot 6 (+0x18): a window that stops the opaque-parent walk.
struct BfmeHintWindowView
{
	BFME_MOH_SLOT(0) BFME_MOH_SLOT(1) BFME_MOH_SLOT(2)
	BFME_MOH_SLOT(3) BFME_MOH_SLOT(4) BFME_MOH_SLOT(5)
	virtual Bool bfmeSlot6( void ) = 0;						///< +0x18
};

// ContainModuleInterface slots 2 (+0x08) and 15 (+0x3C).
struct BfmeHintContainView
{
	BFME_MOH_SLOT(0) BFME_MOH_SLOT(1)
	virtual Bool bfmeSlot2( void ) = 0;						///< +0x08
	BFME_MOH_SLOT(3) BFME_MOH_SLOT(4) BFME_MOH_SLOT(5) BFME_MOH_SLOT(6)
	BFME_MOH_SLOT(7) BFME_MOH_SLOT(8) BFME_MOH_SLOT(9) BFME_MOH_SLOT(10)
	BFME_MOH_SLOT(11) BFME_MOH_SLOT(12) BFME_MOH_SLOT(13) BFME_MOH_SLOT(14)
	virtual const Player *bfmeSlot15( const Player *viewer ) = 0;	///< +0x3C
};

// TheInGameUI slot 60 (+0xF0).
struct BfmeHintInGameUIView
{
	BFME_MOH_SLOT(0)  BFME_MOH_SLOT(1)  BFME_MOH_SLOT(2)  BFME_MOH_SLOT(3)
	BFME_MOH_SLOT(4)  BFME_MOH_SLOT(5)  BFME_MOH_SLOT(6)  BFME_MOH_SLOT(7)
	BFME_MOH_SLOT(8)  BFME_MOH_SLOT(9)  BFME_MOH_SLOT(10) BFME_MOH_SLOT(11)
	BFME_MOH_SLOT(12) BFME_MOH_SLOT(13) BFME_MOH_SLOT(14) BFME_MOH_SLOT(15)
	BFME_MOH_SLOT(16) BFME_MOH_SLOT(17) BFME_MOH_SLOT(18) BFME_MOH_SLOT(19)
	BFME_MOH_SLOT(20) BFME_MOH_SLOT(21) BFME_MOH_SLOT(22) BFME_MOH_SLOT(23)
	BFME_MOH_SLOT(24) BFME_MOH_SLOT(25) BFME_MOH_SLOT(26) BFME_MOH_SLOT(27)
	BFME_MOH_SLOT(28) BFME_MOH_SLOT(29) BFME_MOH_SLOT(30) BFME_MOH_SLOT(31)
	BFME_MOH_SLOT(32) BFME_MOH_SLOT(33) BFME_MOH_SLOT(34) BFME_MOH_SLOT(35)
	BFME_MOH_SLOT(36) BFME_MOH_SLOT(37) BFME_MOH_SLOT(38) BFME_MOH_SLOT(39)
	BFME_MOH_SLOT(40) BFME_MOH_SLOT(41) BFME_MOH_SLOT(42) BFME_MOH_SLOT(43)
	BFME_MOH_SLOT(44) BFME_MOH_SLOT(45) BFME_MOH_SLOT(46) BFME_MOH_SLOT(47)
	BFME_MOH_SLOT(48) BFME_MOH_SLOT(49) BFME_MOH_SLOT(50) BFME_MOH_SLOT(51)
	BFME_MOH_SLOT(52) BFME_MOH_SLOT(53) BFME_MOH_SLOT(54) BFME_MOH_SLOT(55)
	BFME_MOH_SLOT(56) BFME_MOH_SLOT(57) BFME_MOH_SLOT(58) BFME_MOH_SLOT(59)
	virtual Int bfmeSlot60( void ) = 0;						///< +0xF0
};

// TheTacticalView slot 89 (+0x164): screen point to terrain.
struct BfmeHintTacticalView
{
	BFME_MOH_SLOT(0)  BFME_MOH_SLOT(1)  BFME_MOH_SLOT(2)  BFME_MOH_SLOT(3)
	BFME_MOH_SLOT(4)  BFME_MOH_SLOT(5)  BFME_MOH_SLOT(6)  BFME_MOH_SLOT(7)
	BFME_MOH_SLOT(8)  BFME_MOH_SLOT(9)  BFME_MOH_SLOT(10) BFME_MOH_SLOT(11)
	BFME_MOH_SLOT(12) BFME_MOH_SLOT(13) BFME_MOH_SLOT(14) BFME_MOH_SLOT(15)
	BFME_MOH_SLOT(16) BFME_MOH_SLOT(17) BFME_MOH_SLOT(18) BFME_MOH_SLOT(19)
	BFME_MOH_SLOT(20) BFME_MOH_SLOT(21) BFME_MOH_SLOT(22) BFME_MOH_SLOT(23)
	BFME_MOH_SLOT(24) BFME_MOH_SLOT(25) BFME_MOH_SLOT(26) BFME_MOH_SLOT(27)
	BFME_MOH_SLOT(28) BFME_MOH_SLOT(29) BFME_MOH_SLOT(30) BFME_MOH_SLOT(31)
	BFME_MOH_SLOT(32) BFME_MOH_SLOT(33) BFME_MOH_SLOT(34) BFME_MOH_SLOT(35)
	BFME_MOH_SLOT(36) BFME_MOH_SLOT(37) BFME_MOH_SLOT(38) BFME_MOH_SLOT(39)
	BFME_MOH_SLOT(40) BFME_MOH_SLOT(41) BFME_MOH_SLOT(42) BFME_MOH_SLOT(43)
	BFME_MOH_SLOT(44) BFME_MOH_SLOT(45) BFME_MOH_SLOT(46) BFME_MOH_SLOT(47)
	BFME_MOH_SLOT(48) BFME_MOH_SLOT(49) BFME_MOH_SLOT(50) BFME_MOH_SLOT(51)
	BFME_MOH_SLOT(52) BFME_MOH_SLOT(53) BFME_MOH_SLOT(54) BFME_MOH_SLOT(55)
	BFME_MOH_SLOT(56) BFME_MOH_SLOT(57) BFME_MOH_SLOT(58) BFME_MOH_SLOT(59)
	BFME_MOH_SLOT(60) BFME_MOH_SLOT(61) BFME_MOH_SLOT(62) BFME_MOH_SLOT(63)
	BFME_MOH_SLOT(64) BFME_MOH_SLOT(65) BFME_MOH_SLOT(66) BFME_MOH_SLOT(67)
	BFME_MOH_SLOT(68) BFME_MOH_SLOT(69) BFME_MOH_SLOT(70) BFME_MOH_SLOT(71)
	BFME_MOH_SLOT(72) BFME_MOH_SLOT(73) BFME_MOH_SLOT(74) BFME_MOH_SLOT(75)
	BFME_MOH_SLOT(76) BFME_MOH_SLOT(77) BFME_MOH_SLOT(78) BFME_MOH_SLOT(79)
	BFME_MOH_SLOT(80) BFME_MOH_SLOT(81) BFME_MOH_SLOT(82) BFME_MOH_SLOT(83)
	BFME_MOH_SLOT(84) BFME_MOH_SLOT(85) BFME_MOH_SLOT(86) BFME_MOH_SLOT(87)
	BFME_MOH_SLOT(88)
	virtual void bfmeSlot89( const ICoord2D *screen, Coord3D *world, Int arg ) = 0;	///< +0x164
};

#undef BFME_MOH_SLOT

struct BfmeHintMessage
{
	UnsignedByte pad0[0x10];
	Int type;										///< +0x10
};

struct BfmeHintDrawable
{
	UnsignedByte pad0[0xfc];
	Object *object;									///< +0xFC
};

struct BfmeHintObject
{
	UnsignedByte pad0[0x38];
	Coord3D position;								///< +0x38
	UnsignedByte pad1[0x74 - 0x44];
	Int field74;									///< +0x74
	UnsignedByte pad2[0x1fc - 0x78];
	BfmeHintContainView *contain;					///< +0x1FC
};

struct BfmeHintPlayer
{
	UnsignedByte pad0[0x24];
	Int playerIndex;								///< +0x24
	UnsignedByte pad1[0x1c4 - 0x28];
	Color color;									///< +0x1C4
	UnsignedByte pad2[0x230 - 0x1c8];
	Team *defaultTeam;								///< +0x230
};

struct BfmeHintPlayerList
{
	UnsignedByte pad0[0xc];
	Player *local;									///< +0x0C
};

struct BfmeHintThingTemplate
{
	UnsignedByte pad0[0xc];
	UnicodeString displayName;						///< +0x0C
	UnsignedByte pad1[0x20 - 0x10];
	AsciiString name;								///< +0x20
};

struct BfmeHintWarehouse
{
	UnsignedByte pad0[0x88];
	Int boxesStored;								///< +0x88
};

struct BfmeHintGlobalData
{
	UnsignedByte pad0[0xa88];
	Int fieldA88;									///< +0xA88
	UnsignedByte pad1[0xb24 - 0xa8c];
	Int baseValuePerSupplyBox;						///< +0xB24
};

struct BfmeHintGameLogic
{
	UnsignedByte pad0[0x10c];
	Int field10C;									///< +0x10C
};

struct BfmeHintUI
{
	UnsignedByte pad0[0x820];
	Bool isScrolling;								///< +0x820
	Bool isSelecting;								///< +0x821
	UnsignedByte pad1[2];
	Int mouseMode;									///< +0x824
	Int mouseModeCursor;							///< +0x828
	DrawableID mousedOverDrawableID;				///< +0x82C
	UnsignedByte pad2[0x13a8 - 0x830];
	Int field13A8;									///< +0x13A8
};

// The record handed to the control bar: vtable 0x010F5738 over a base
// whose table 0x010EDAA0 has a destructor and three pure slots.
class BfmeHintRecordBase010EDAA0
{
public:
	virtual ~BfmeHintRecordBase010EDAA0() {}
	virtual void bfmeSlot1( void ) = 0;
	virtual void bfmeSlot2( void ) = 0;
	virtual void bfmeSlot3( void ) = 0;
};

class BfmeHintRecord010F5738 : public BfmeHintRecordBase010EDAA0
{
public:
	BfmeHintRecord010F5738( Int a, Int b ) : m_field4( a ), m_field8( b ) {}
	virtual ~BfmeHintRecord010F5738() {}
	virtual void bfmeSlot1( void );
	virtual void bfmeSlot2( void );
	virtual void bfmeSlot3( void );
	Int m_field4;
	Int m_field8;
};

static __forceinline void bfmeHintSetMouseCursor( BfmeHintUI *self, Mouse::MouseCursor c )
{
	if (!TheMouse)
		return;

	((BfmeMouseSetCursorView *)TheMouse)->setCursor(c);

	if (self->mouseMode == 2 /* MOUSEMODE_GUI_COMMAND */ && c != Mouse::ARROW && c != Mouse::SCROLL)
		self->mouseModeCursor = c;
}

}  // namespace

// Out-of-line BFME helpers reached through ILT thunks; names are the ledger's.
class Rva0036CA00Str;
struct Rva00415A60
{
	bool take( Rva0036CA00Str &label );				///< 0x00415A60, on the drawable
};

struct Rva000D3F10
{
	Int test( UnsignedInt bit );					///< 0x000D3F10, on the object
};

struct BfmeThing78F
{
	void *reg25C( void );							///< 0x002678F0, on the disguise module
};

struct Gen_005B53D0
{
	UnsignedByte bfmeExpired( void );				///< 0x005B53D0, on TheLookAtTranslator
};

// 0x004C15D0, thiscall on TheControlBar with the record, ret 4.
struct Rva004C15D0ControlBar
{
	void rva004C15D0( BfmeHintRecordBase010EDAA0 *record );
};

// Mouse::setCursorTooltip with its by-value text through the TU's
// BfmeUnicodeStringArg view (retail 0x005A56F0 via ILT 0x004346E9).
struct BfmeHintMouseTooltipView
{
	void setCursorTooltip( BfmeUnicodeStringArg tooltip, Int tooltipDelay = -1, const RGBColor *color = NULL, Real width = 1.0f );
};

// Player::getPlayerDisplayName is out of line in BFME (0x00098FD0); the
// vendored header inlines it, so the call goes through this view.
struct BfmePlayerDisplayNameView
{
	UnicodeString getPlayerDisplayName( void );
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;
extern PartitionManager *TheShroudManager;				///< retail 0x012ED5BC

// ?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z
void InGameUI::createMouseoverHint( const GameMessage *msg )
{
	BfmeHintUI *self = reinterpret_cast<BfmeHintUI *>( this );

	if (self->isScrolling || self->isSelecting)
		return; // no mouseover for you

	GameWindow *window = NULL;
	const MouseIO *io = reinterpret_cast<const MouseIO *>( reinterpret_cast<UnsignedByte *>( TheMouse ) + 0x4d10 );
	Bool underWindow = false;
	if (io && TheWindowManager)
		window = TheWindowManager->getWindowUnderCursor(io->pos.x, io->pos.y);

	while (window)
	{
		if (reinterpret_cast<BfmeHintWindowView *>( window )->bfmeSlot6()) {
			underWindow = false;
			break;
		}

		// check to see if it or any of its parents are opaque.  If so, we can't select anything.
		if (!BitTest( window->winGetStatus(), 0x10000 ) && !BitTest( window->winGetStatus(), 0x200 ))
		{
			underWindow = true;
			break;
		}

		window = window->winGetParent();
	}
	if (underWindow)
	{
		bfmeHintSetMouseCursor(self, Mouse::ARROW); // regardless of m_mouseMode
		return;
	}

	DrawableID oldID = self->mousedOverDrawableID;

	if (reinterpret_cast<const BfmeHintMessage *>( msg )->type == 0x94)	// BFME MSG_MOUSEOVER_DRAWABLE_HINT
	{
		reinterpret_cast<BfmeHintMouseTooltipView *>( TheMouse )->setCursorTooltip( UnicodeString::TheEmptyString );
		self->mousedOverDrawableID = INVALID_DRAWABLE_ID;
		Drawable *draw = ((BfmeGameClientGarrisonView *)TheGameClient)->findDrawableByID(msg->getArgument(0)->drawableID);
		Object *obj = draw ? reinterpret_cast<BfmeHintDrawable *>( draw )->object : NULL;
		if( obj )
		{
			if (!obj->isKindOf( (KindOfType)0x2f ))
				self->mousedOverDrawableID = draw->getID();

			const Player* player = NULL;
			const ThingTemplate *thingTemplate = obj->getTemplate();

			BfmeHintContainView *contain = reinterpret_cast<BfmeHintObject *>( obj )->contain;
			if( contain )
				player = contain->bfmeSlot15(reinterpret_cast<BfmeHintPlayerList *>( Rva002EE330ThePlayers )->local);

			if (player == NULL)
				player = obj->getControllingPlayer();

			Bool disguised = false;
			if( (UnsignedByte)reinterpret_cast<Rva000D3F10 *>( obj )->test( 0x10b ) )
			{
				static NameKeyType key_disguise = TheNameKeyGenerator->nameToKey( "SpecialDisguiseUpdate" );
				BfmeThing78F *update = (BfmeThing78F *)obj->findUpdateModule( key_disguise );
				if( update )
				{
					Player *clientPlayer = reinterpret_cast<BfmeHintPlayerList *>( Rva002EE330ThePlayers )->local;
					if( player->getRelationship( reinterpret_cast<BfmeHintPlayer *>( clientPlayer )->defaultTeam ) != ALLIES && clientPlayer->isPlayerActive() )
					{
						const ThingTemplate *disguisedTemplate = (const ThingTemplate *)update->reg25C();
						if( disguisedTemplate )
						{
							thingTemplate = disguisedTemplate;
							disguised = true;
						}
					}
				}
			}

			AsciiString label;
			UnicodeString str = reinterpret_cast<const BfmeHintThingTemplate *>( thingTemplate )->displayName;
			if( reinterpret_cast<Rva00415A60 *>( draw )->take( *reinterpret_cast<Rva0036CA00Str *>( &label ) ) )
				str = TheGameText->fetch( label );
			UnicodeString displayName = str;
			if( reinterpret_cast<StringBase<WideChar> &>( str ).isEmpty() )
			{
				AsciiString txtTemp;
				txtTemp.format("ThingTemplate:%s", bfmeMessageText( reinterpret_cast<const BfmeHintThingTemplate *>( obj->getTemplate() )->name ));
				str = TheGameText->fetch(txtTemp);
			}

			UnicodeString warehouseFeedback;
			// Add on dollar amount of warehouse contents so people don't freak out until the art is hooked up
			static const NameKeyType warehouseModuleKey = TheNameKeyGenerator->nameToKey( "SupplyWarehouseDockUpdate" );
			BfmeHintWarehouse *warehouseModule = (BfmeHintWarehouse *)obj->findUpdateModule( warehouseModuleKey );
			if( warehouseModule != NULL )
			{
				Int boxes = warehouseModule->boxesStored;
				Int value = boxes * reinterpret_cast<const BfmeHintGlobalData *>( TheGlobalData )->baseValuePerSupplyBox;
				warehouseFeedback.format(TheGameText->fetch("TOOLTIP:SupplyWarehouse"), value);
				reinterpret_cast<StringBase<WideChar> &>( str ).concat( reinterpret_cast<StringBase<WideChar> &>( warehouseFeedback ) );
			}

			if (player)
			{
				UnicodeString tooltip;
				if (TheRecorder->isMultiplayer() && reinterpret_cast<BfmeHintGameLogic *>( TheGameLogic )->field10C != 6 && player->isPlayableSide())
					tooltip.format(L"%s\n%s", bfmeMessageText( str ), bfmeMessageText( reinterpret_cast<BfmePlayerDisplayNameView *>( (Player *)player )->getPlayerDisplayName() ));
				else
					tooltip = str;

				Int localPlayerIndex = Rva002EE330ThePlayers ? reinterpret_cast<BfmeHintPlayer *>( reinterpret_cast<BfmeHintPlayerList *>( Rva002EE330ThePlayers )->local )->playerIndex : 0;

				Coord3D pos;
				pos.x = 0.0f;
				pos.y = 0.0f;
				pos.z = 0.0f;
				if( io )
					reinterpret_cast<BfmeHintTacticalView *>( TheTacticalView )->bfmeSlot89( &io->pos, &pos, 0 );
				if( TheShroudManager->getShroudStatusForPlayer(localPlayerIndex, &reinterpret_cast<BfmeHintObject *>( obj )->position) == CELLSHROUD_CLEAR ||
						( obj->isKindOf( (KindOfType)0x5d ) && TheShroudManager->getShroudStatusForPlayer(localPlayerIndex, &pos) == CELLSHROUD_CLEAR ) )
				{
					RGBColor rgb;
					if( disguised )
					{
						rgb.setFromInt( reinterpret_cast<const BfmeHintPlayer *>( player )->color );
					}
					else
					{
						rgb.setFromInt(reinterpret_cast<BfmeHintDrawable *>( draw )->object->getIndicatorColor());

						// Unless this is a stealth garrisoned building,
						// Let's not use the contained's housecolor
						const Object *obj = reinterpret_cast<BfmeHintDrawable *>( draw )->object;
						if ( obj )
						{
							BfmeHintContainView *contain = reinterpret_cast<const BfmeHintObject *>( obj )->contain;
							if ( contain && contain->bfmeSlot2() )
							{
								const Player *play = contain->bfmeSlot15( reinterpret_cast<BfmeHintPlayerList *>( Rva002EE330ThePlayers )->local );
								if ( play )
									rgb.setFromInt( reinterpret_cast<const BfmeHintPlayer *>( play )->color );
							}
						}

					}

					//Object:Prop is a blank string... but we don't want to show
					//any popup box at all if that is the case!
					if( reinterpret_cast<StringBase<WideChar> &>( displayName ).compare( reinterpret_cast<const StringBase<WideChar> &>( TheGameText->fetch( "OBJECT:Prop" ) ) ) )
					{
						Bool showTooltip = TRUE;
						Player *owner;
						if( TheControlBar && (owner = obj->getControllingPlayer()) != NULL && owner->isLocalPlayer() &&
								( obj->isKindOf( (KindOfType)9 ) || obj->isKindOf( (KindOfType)8 ) || obj->isKindOf( (KindOfType)0xb ) ||
									obj->isKindOf( (KindOfType)0xa ) || obj->isKindOf( (KindOfType)7 ) ) )
						{
							{
								BfmeHintRecord010F5738 record( reinterpret_cast<BfmeHintObject *>( obj )->field74, self->field13A8 );
								reinterpret_cast<Rva004C15D0ControlBar *>( TheControlBar )->rva004C15D0( &record );
							}
							if( !reinterpret_cast<const BfmeHintGlobalData *>( TheGlobalData )->fieldA88 && warehouseModule == NULL )
								showTooltip = FALSE;
						}
						if( showTooltip )
							reinterpret_cast<BfmeHintMouseTooltipView *>( TheMouse )->setCursorTooltip( tooltip, -1, &rgb );
					}
				}
			}
		}

	}
	else
	{
		self->mousedOverDrawableID = INVALID_DRAWABLE_ID;
	}

	if (oldID != self->mousedOverDrawableID)
	{
		//DEBUG_LOG(("Resetting tooltip delay\n"));
		TheMouse->resetTooltipDelay();
	}

	if (self->mouseMode == MOUSEMODE_DEFAULT && !self->isScrolling && !self->isSelecting && !reinterpret_cast<BfmeHintInGameUIView *>( TheInGameUI )->bfmeSlot60() && (TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || reinterpret_cast<Gen_005B53D0 *>( TheLookAtTranslator )->bfmeExpired()))
	{
		if( self->mousedOverDrawableID != INVALID_DRAWABLE_ID )
		{
			Drawable *draw = ((BfmeGameClientGarrisonView *)TheGameClient)->findDrawableByID(self->mousedOverDrawableID);

			//Add basic logic to determine if we can select a unit (or hint)
			const Object *obj = draw ? reinterpret_cast<BfmeHintDrawable *>( draw )->object : NULL;
			Bool drawSelectable = CanSelectDrawable(draw, FALSE);
			if( !obj )
			{
				drawSelectable = false;
			}

			if( drawSelectable && obj->isLocallyControlled() )
			{
				bfmeHintSetMouseCursor(self, (Mouse::MouseCursor)0xd);
			}
			else
			{
				bfmeHintSetMouseCursor(self, Mouse::ARROW);
			}
		}
		else
		{
			bfmeHintSetMouseCursor(self, Mouse::ARROW);
		}
	}
	else if (self->mouseMode != MOUSEMODE_DEFAULT)
	{
		setMouseCursor((Mouse::MouseCursor)self->mouseModeCursor);
	}
}
