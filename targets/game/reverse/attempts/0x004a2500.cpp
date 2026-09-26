// ?evaluateContextUI@ControlBar@@IAEXXZ
// partial score=0.8 date=2026-09-26
// Banked attempt for ?evaluateContextUI@ControlBar@@IAEXXZ (0x004A2500, 1571 B), 2026-09-26,
// claude-opus-5-5. Splice into ControlBar.cpp: the old Zero Hour evaluateContextUI
// near line 1720 is removed and the BFME body is appended at the END of the file (after
// switchToContext, so VC7.1 inlines switchToContext for the multi-select (7) and OCL-timer
// (10) arms exactly as retail does); BfmeContextSwitchInGameUI slots 60/63/66 are named
// getSelectCount/getAllSelectedDrawables/getSoloNexusSelectedDrawableID. Probe: 1561/1571.
// Residue: retail keeps selectedDrawables in edi (push edi before the 0xfc call, two
// separate early-return epilogues) and materialises constant 1 in ebx (cmp eax,ebx for
// count>1, winHide(TRUE) pushes, static-guard or); ours spills the list and puts constant
// 0 in ebx instead, which shifts registers through the inlined arms.
// Rename in BfmeContextSwitchInGameUI: slot60 -> virtual Int getSelectCount(void), slot63 ->
// virtual const DrawableList *getAllSelectedDrawables(void), slot66 -> virtual DrawableID
// getSoloNexusSelectedDrawableID(void).

//-------------------------------------------------------------------------------------------------
/** Given the drawables that we have selected into our context sensitive UI, evaluate
	* and perform all UI manipulations to make the GUI show to the user what we want them
	* to see */
//-------------------------------------------------------------------------------------------------
// ?evaluateContextUI@ControlBar@@IAEXXZ -- retail 0x004A2500, 1571 bytes.
//
// Zero Hour's evaluateContextUI (callers: ControlBar::update twice), reshaped
// by BFME: no unconditional switch to the empty context up front, each early
// exit switches to it instead; a non-controllable selection falls through to
// the normal evaluation; and the under-construction test became three checks.
// switchToContext above is expanded in place by the compiler for the
// multi-select and OCL-timer arms, as retail has it.

// ControlBar+0x24 holds the UI dirty flag in BFME.
struct BfmeEvaluateContextControlBarView
{
	char pad00[0x24];
	Bool uiDirty;
};

// The purchase-science window singleton, its visible byte at +0x259
// (ControlBarPurchaseScience.cpp reads the same byte).
struct BfmeEvaluatePurchaseScienceWindow
{
	unsigned char pad000[0x259];
	Bool visible;
};

// BFME Object fields read directly: the contain module at +0x1fc and the team
// at +0x23c.
struct BfmeEvaluateObjectView
{
	unsigned char pad000[0x1fc];
	class BfmeEvaluateContain *contain;
	unsigned char pad200[0x23c - 0x200];
	Team *team;
};

// Player+4 is the player template; PlayerTemplate+0xe4 the beacon template name.
struct BfmeEvaluatePlayerView
{
	unsigned char pad00[4];
	struct BfmeEvaluatePlayerTemplateView *playerTemplate;
};

struct BfmeEvaluatePlayerTemplateView
{
	unsigned char pad00[0xe4];
	AsciiString beaconTemplate;
};

struct BfmeEvaluateThingTemplateView
{
	unsigned char pad00[0x20];
	AsciiString name;
};

// The contain module interface as BFME's vtable lays it out.
class BfmeEvaluateContain
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual Bool isGarrisonable(void) const = 0;						// +0x08
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const = 0;	// +0x3c
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual Int getContainMax(void) const = 0;							// +0x5c
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual Bool slot49(void) = 0;										// +0xc4
	virtual void slot50(void) = 0;
	virtual Player *slot51(void) = 0;									// +0xcc
};

// The interface the object accessor behind ILT 0x000351D9 returns.
class BfmeEvaluateCompletionInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual Bool slot10(void) = 0;										// +0x28
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual Bool slot13(void) = 0;										// +0x34
};

// Object::testStatus(int) at ILT 0x000016A4, under its pinned view name.
class BFMEActionObject
{
public:
	Bool testStatus(Int bit) const;
};

// bit-array test at Object+0x110 (0x000D3F10), under its pinned Bool view.
class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

// Calls reached only through their incremental-link thunks: the selection
// controllability test on TheInGameUI (0x0043EC00), Object's attribute
// modifier multiplier (0x001BFDD0) and the object accessor at 0x001BF670.
extern void j_000221e2(void);
extern void j_0002abf8(void);
extern void j_000351d9(void);
class BfmeEvaluateContextCalls
{
public:
	__forceinline Bool areSelectedObjectsControllable(void) {
		typedef Bool (BfmeEvaluateContextCalls::*Method)(void);
		union { void (*raw)(void); Method member; } call;
		call.raw = j_000221e2;
		return (this->*call.member)();
	}
	__forceinline Bool getAttributeModifierMultiplier(Int type, Real *value) {
		typedef Bool (BfmeEvaluateContextCalls::*Method)(Int, Real *);
		union { void (*raw)(void); Method member; } call;
		call.raw = j_0002abf8;
		return (this->*call.member)(type, value);
	}
	__forceinline BfmeEvaluateCompletionInterface *getCompletionInterface(void) {
		typedef BfmeEvaluateCompletionInterface *(BfmeEvaluateContextCalls::*Method)(void);
		union { void (*raw)(void); Method member; } call;
		call.raw = j_000351d9;
		return (this->*call.member)();
	}
};

// Compares the controlling player's beacon template name with the object's
// template name; retail reads the player template before the thing template.
static __forceinline Int bfmeCompareBeaconTemplate(Object *obj)
{
	const AsciiString &beacon = ((BfmeEvaluatePlayerView *)obj->getControllingPlayer())->playerTemplate->beaconTemplate;
	return beacon.compare(((const BfmeEvaluateThingTemplateView *)obj->getTemplate())->name);
}

void ControlBar::evaluateContextUI( void )
{
	((BfmeEvaluateContextControlBarView *)this)->uiDirty = FALSE;

	// if our purchase science window is up, we will want to update it by repopulating it.
	if (g_obj12F4C38 && ((BfmeEvaluatePurchaseScienceWindow *)g_obj12F4C38)->visible)
		showPurchaseScience();

	// sanity, nothing selected
	if( BFME_CONTEXT_INGAME_UI->getSelectCount() == 0 )
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		return;
	}

	// get the list of drawable IDs from the in game UI
	const DrawableList *selectedDrawables = BFME_CONTEXT_INGAME_UI->getAllSelectedDrawables();

	// sanity
	if( selectedDrawables->empty() == TRUE )
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		return;
	}

	if( !((BfmeEvaluateContextCalls *)TheInGameUI)->areSelectedObjectsControllable() )
	{
		Drawable *draw = selectedDrawables->front();
		if( !draw )
		{
			switchToContext( CB_CONTEXT_NONE, NULL );
			return;
		}
		Object *obj = (Object *)((BfmeContextSwitchDrawableView *)draw)->object;
		if( !obj )
		{
			switchToContext( CB_CONTEXT_NONE, NULL );
			return;
		}

		if( obj->getControllingPlayer()
			&& ((BfmeEvaluatePlayerView *)obj->getControllingPlayer())->playerTemplate
			&& bfmeCompareBeaconTemplate( obj ) == 0 )
		{
			switchToContext( (ControlBarContext)5, draw );
		}
		else
		{
			BfmeEvaluateContain *contain = ((BfmeEvaluateObjectView *)obj)->contain;
			if( contain && contain->getContainMax() > 0 )
			{
				switchToContext( (ControlBarContext)4, draw );

				Player *localPlayer = (Player *)((BfmeShortcutPlayerList *)ThePlayerList)->getLocalPlayer();
				if( contain->slot49() && contain->slot51() == localPlayer )
				{
					switchToContext( (ControlBarContext)3, draw );
					return;
				}

				const Player *otherPlayer = contain->getApparentControllingPlayer( localPlayer );
				if( !otherPlayer )
					otherPlayer = obj->getControllingPlayer();
				if( !((BfmeShortcutPlayerList *)ThePlayerList)->getLocalPlayer() || !otherPlayer )
				{
					switchToContext( CB_CONTEXT_NONE, NULL );
					return;
				}
			}
		}
	}

	Drawable *drawToEvaluateFor = NULL;
	Bool multiSelect = FALSE;

	if( BFME_CONTEXT_INGAME_UI->getSelectCount() > 1 )
	{
		drawToEvaluateFor = ((BFMEGameClientDrawables *)TheGameClient)->findDrawableByID( BFME_CONTEXT_INGAME_UI->getSoloNexusSelectedDrawableID() );
		multiSelect = ( drawToEvaluateFor == NULL );
	}
	else
		drawToEvaluateFor = selectedDrawables->front();

	if( multiSelect )
	{
		switchToContext( (ControlBarContext)7, NULL );
		return;
	}

	if( !drawToEvaluateFor )
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		return;
	}

	Object *obj = (Object *)((BfmeContextSwitchDrawableView *)drawToEvaluateFor)->object;
	if( obj == NULL || ((BFMEActionObject *)obj)->testStatus( 0x13 ) )
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		return;
	}

	static const NameKeyType key_OCLUpdate = NAMEKEY( "OCLUpdate" );
	OCLUpdate *update = (OCLUpdate*)obj->findUpdateModule( key_OCLUpdate );

	if( obj->isKindOf( (KindOfType)0x95 ) )
	{
		Real multiplier = 0.0f;
		if( ((BfmeEvaluateContextCalls *)obj)->getAttributeModifierMultiplier( 3, &multiplier ) && multiplier == 0.0f )
		{
			switchToContext( (ControlBarContext)6, drawToEvaluateFor );
			return;
		}
	}
	if( ((BFMESelectionStatusBits *)obj)->test( 0xd0 ) )
	{
		switchToContext( (ControlBarContext)6, drawToEvaluateFor );
		return;
	}
	if( ((BFMEActionObject *)obj)->testStatus( 2 ) )
	{
		BfmeEvaluateCompletionInterface *completion = ((BfmeEvaluateContextCalls *)obj)->getCompletionInterface();
		if( completion && ( completion->slot13() || completion->slot10() ) )
		{
			switchToContext( (ControlBarContext)6, drawToEvaluateFor );
			return;
		}
	}
	else
	{
		BfmeEvaluateCompletionInterface *completion = ((BfmeEvaluateContextCalls *)obj)->getCompletionInterface();
		if( completion && completion->slot10() )
		{
			switchToContext( (ControlBarContext)6, drawToEvaluateFor );
			return;
		}
	}

	BfmeEvaluateContain *cmi = ((BfmeEvaluateObjectView *)obj)->contain;
	if( cmi && cmi->isGarrisonable() && obj->getCommandSetString().isEmpty() )
	{
		Relationship relationship = ((Player *)((BfmeShortcutPlayerList *)ThePlayerList)->getLocalPlayer())->getRelationship( ((BfmeEvaluateObjectView *)obj)->team );
		if( obj->isLocallyControlled() == TRUE || relationship == NEUTRAL )
			switchToContext( (ControlBarContext)2, drawToEvaluateFor );
	}
	else if( update )
	{
		switchToContext( (ControlBarContext)10, drawToEvaluateFor );
	}
	else if( obj->getCommandSetString().isEmpty() == FALSE )
	{
		switchToContext( (ControlBarContext)1, drawToEvaluateFor );
	}
	else if( obj->getControllingPlayer()
			&& ((BfmeEvaluatePlayerView *)obj->getControllingPlayer())->playerTemplate
			&& bfmeCompareBeaconTemplate( obj ) == 0 )
	{
		switchToContext( (ControlBarContext)5, drawToEvaluateFor );
	}
	else
		switchToContext( CB_CONTEXT_NONE, drawToEvaluateFor );

}  // end evaluateContextUI
