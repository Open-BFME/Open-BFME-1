// ?Rva004BCCE0@@YAXPAVGameWindow@@@Z
// partial score=0.99 date=2026-09-21
// Retail 0x004BCCE0, 402 bytes.
// Sits between the landed GadgetPushButtonSystem (0x004BCBB0,
// GadgetPushButtonBodies.cpp) and GadgetRadioButton.cpp's doRadioUnselect
// (0x004BCEE0); its identity stays address-derived (no named caller or
// callback-table row), but the call chain reuses the SAME InGameUI /
// Drawable pair already proven by the neighbouring Rva004BC8A0.cpp (which
// this file's InGameUI/Drawable declarations are copied from verbatim), plus
// the landed BfmeOwnerLU::bfmeTopLU (BfmeConv1789.cpp), BfmeThingUKD::bfmeGoUKD
// (BfmeConv1335.cpp), Rva0029BBC0::isEither (S2TwoValueStateTests.cpp),
// Object::getProductionUpdateInterface (ObjectFields.cpp),
// ControlBar::findContainedObject (ControlBar_findContainedObject.cpp) and
// GameWindow::winGetUserData (GadgetUserDataHelpers.cpp).
//
// Retail walks a window's push-button user data (+0x28 dirty flag routes
// through Rva004BC8A0; +0x14 is a command-button/BfmeOwnerLU pointer whose
// +0x10 field is a purpose code) and draws a progress "inverse clock" via
// GadgetButtonDrawInverseClock for whichever of three cases applies:
//   purpose == 3: walk the selected object's ProductionUpdateInterface list
//     (slot 0x48 = get-first, slot 0x4c = get-next) for the first entry whose
//     Rva0029BBC0::isEither() is true AND whose "BfmeCheckFH" facet accepts
//     the entry's +8 field, then draw with that entry's bfmeGoUKD() percent.
//   purpose == 5,6,7: walk the same list for the first entry whose +4 field
//     is 2 and whose +0xc field equals the command button's own +0x20 field,
//     then draw the same way.
//   no ProductionUpdateInterface at all: fall back to the selected object's
//     +0x1fc interface, gate on its slot 0xD4 against TheControlBar's
//     findContainedObject(window), then draw using slot 0x30's return as the
//     percent over the contained object's own +0x74 field.

class GameWindow;
class Object;
class BfmeThingLU;

class GameWindow
{
public:
	void *winGetUserData(void);
};

// Copied verbatim from Rva004BC8A0.cpp: same TheInGameUI global, same
// getFirstSelectedDrawable slot (65 filler slots then the real one, at
// vtable offset 0x104), same Drawable::m_object at +0xfc.
class InGameUI
{
public:
#define BFME_INGAME_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_INGAME_SLOT( 00 ) BFME_INGAME_SLOT( 01 ) BFME_INGAME_SLOT( 02 )
	BFME_INGAME_SLOT( 03 ) BFME_INGAME_SLOT( 04 ) BFME_INGAME_SLOT( 05 )
	BFME_INGAME_SLOT( 06 ) BFME_INGAME_SLOT( 07 ) BFME_INGAME_SLOT( 08 )
	BFME_INGAME_SLOT( 09 ) BFME_INGAME_SLOT( 10 ) BFME_INGAME_SLOT( 11 )
	BFME_INGAME_SLOT( 12 ) BFME_INGAME_SLOT( 13 ) BFME_INGAME_SLOT( 14 )
	BFME_INGAME_SLOT( 15 ) BFME_INGAME_SLOT( 16 ) BFME_INGAME_SLOT( 17 )
	BFME_INGAME_SLOT( 18 ) BFME_INGAME_SLOT( 19 ) BFME_INGAME_SLOT( 20 )
	BFME_INGAME_SLOT( 21 ) BFME_INGAME_SLOT( 22 ) BFME_INGAME_SLOT( 23 )
	BFME_INGAME_SLOT( 24 ) BFME_INGAME_SLOT( 25 ) BFME_INGAME_SLOT( 26 )
	BFME_INGAME_SLOT( 27 ) BFME_INGAME_SLOT( 28 ) BFME_INGAME_SLOT( 29 )
	BFME_INGAME_SLOT( 30 ) BFME_INGAME_SLOT( 31 ) BFME_INGAME_SLOT( 32 )
	BFME_INGAME_SLOT( 33 ) BFME_INGAME_SLOT( 34 ) BFME_INGAME_SLOT( 35 )
	BFME_INGAME_SLOT( 36 ) BFME_INGAME_SLOT( 37 ) BFME_INGAME_SLOT( 38 )
	BFME_INGAME_SLOT( 39 ) BFME_INGAME_SLOT( 40 ) BFME_INGAME_SLOT( 41 )
	BFME_INGAME_SLOT( 42 ) BFME_INGAME_SLOT( 43 ) BFME_INGAME_SLOT( 44 )
	BFME_INGAME_SLOT( 45 ) BFME_INGAME_SLOT( 46 ) BFME_INGAME_SLOT( 47 )
	BFME_INGAME_SLOT( 48 ) BFME_INGAME_SLOT( 49 ) BFME_INGAME_SLOT( 50 )
	BFME_INGAME_SLOT( 51 ) BFME_INGAME_SLOT( 52 ) BFME_INGAME_SLOT( 53 )
	BFME_INGAME_SLOT( 54 ) BFME_INGAME_SLOT( 55 ) BFME_INGAME_SLOT( 56 )
	BFME_INGAME_SLOT( 57 ) BFME_INGAME_SLOT( 58 ) BFME_INGAME_SLOT( 59 )
	BFME_INGAME_SLOT( 60 ) BFME_INGAME_SLOT( 61 ) BFME_INGAME_SLOT( 62 )
	BFME_INGAME_SLOT( 63 ) BFME_INGAME_SLOT( 64 )
	virtual class Drawable *getFirstSelectedDrawable( void ) = 0;
#undef BFME_INGAME_SLOT
};

class Drawable
{
	char m_pad[ 0xfc ];

public:
	Object *m_object;
};

extern InGameUI *TheInGameUI;

// Rva0029BBC0 (S2TwoValueStateTests.cpp): its own m_state test lives at +4,
// which matches this body's list entries; +8 and +0xc are this body's own
// evidence, read as raw fields rather than declared members of that class.
class Rva0029BBC0
{
public:
	int isEither() const;
};

// BfmeConv1335.cpp: thiscall, no args, returns the entry's clock percent.
class BfmeThingUKD
{
public:
	int bfmeGoUKD();
};

// The item's "availability" facet at the retail call site 0x0003E80B; still
// an unmatched dump (pinned), called here only for its ABI.
class BfmeCheckFH
{
public:
	char bfmeCheckFH( void *a );
};

// ProductionUpdateInterface, extended two slots past Rva004BC8A0.cpp's copy:
// slot18 (offset 0x48, no args) is the list's get-first, slot19 (offset
// 0x4c, one arg) is get-next.
class ProductionUpdateInterface
{
public:
#define BFME_PUI_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_PUI_SLOT( 00 ) BFME_PUI_SLOT( 01 ) BFME_PUI_SLOT( 02 )
	BFME_PUI_SLOT( 03 ) BFME_PUI_SLOT( 04 ) BFME_PUI_SLOT( 05 )
	BFME_PUI_SLOT( 06 ) BFME_PUI_SLOT( 07 ) BFME_PUI_SLOT( 08 )
	BFME_PUI_SLOT( 09 ) BFME_PUI_SLOT( 10 ) BFME_PUI_SLOT( 11 )
	BFME_PUI_SLOT( 12 ) BFME_PUI_SLOT( 13 ) BFME_PUI_SLOT( 14 )
	virtual void *slot15( BfmeThingLU *thing ) = 0;
	BFME_PUI_SLOT( 16 )
	virtual void *slot17( void *mask ) = 0;
	virtual Rva0029BBC0 *slot18( void ) = 0;
	virtual Rva0029BBC0 *slot19( Rva0029BBC0 *cur ) = 0;
#undef BFME_PUI_SLOT
};

class Object
{
public:
	ProductionUpdateInterface *getProductionUpdateInterface();
};

// The fallback facet at Object+0x1fc when there is no ProductionUpdateInterface:
// slot12 (offset 0x30, one int arg) computes the percent, slot53 (offset
// 0xD4, one Object* arg) is the availability gate. Neither name is proven.
class SpecialInterface
{
public:
#define BFME_SPECIAL_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_SPECIAL_SLOT( 00 ) BFME_SPECIAL_SLOT( 01 ) BFME_SPECIAL_SLOT( 02 )
	BFME_SPECIAL_SLOT( 03 ) BFME_SPECIAL_SLOT( 04 ) BFME_SPECIAL_SLOT( 05 )
	BFME_SPECIAL_SLOT( 06 ) BFME_SPECIAL_SLOT( 07 ) BFME_SPECIAL_SLOT( 08 )
	BFME_SPECIAL_SLOT( 09 ) BFME_SPECIAL_SLOT( 10 ) BFME_SPECIAL_SLOT( 11 )
	virtual int slot12( int value ) = 0;
	BFME_SPECIAL_SLOT( 13 ) BFME_SPECIAL_SLOT( 14 ) BFME_SPECIAL_SLOT( 15 )
	BFME_SPECIAL_SLOT( 16 ) BFME_SPECIAL_SLOT( 17 ) BFME_SPECIAL_SLOT( 18 )
	BFME_SPECIAL_SLOT( 19 ) BFME_SPECIAL_SLOT( 20 ) BFME_SPECIAL_SLOT( 21 )
	BFME_SPECIAL_SLOT( 22 ) BFME_SPECIAL_SLOT( 23 ) BFME_SPECIAL_SLOT( 24 )
	BFME_SPECIAL_SLOT( 25 ) BFME_SPECIAL_SLOT( 26 ) BFME_SPECIAL_SLOT( 27 )
	BFME_SPECIAL_SLOT( 28 ) BFME_SPECIAL_SLOT( 29 ) BFME_SPECIAL_SLOT( 30 )
	BFME_SPECIAL_SLOT( 31 ) BFME_SPECIAL_SLOT( 32 ) BFME_SPECIAL_SLOT( 33 )
	BFME_SPECIAL_SLOT( 34 ) BFME_SPECIAL_SLOT( 35 ) BFME_SPECIAL_SLOT( 36 )
	BFME_SPECIAL_SLOT( 37 ) BFME_SPECIAL_SLOT( 38 ) BFME_SPECIAL_SLOT( 39 )
	BFME_SPECIAL_SLOT( 40 ) BFME_SPECIAL_SLOT( 41 ) BFME_SPECIAL_SLOT( 42 )
	BFME_SPECIAL_SLOT( 43 ) BFME_SPECIAL_SLOT( 44 ) BFME_SPECIAL_SLOT( 45 )
	BFME_SPECIAL_SLOT( 46 ) BFME_SPECIAL_SLOT( 47 ) BFME_SPECIAL_SLOT( 48 )
	BFME_SPECIAL_SLOT( 49 ) BFME_SPECIAL_SLOT( 50 ) BFME_SPECIAL_SLOT( 51 )
	BFME_SPECIAL_SLOT( 52 )
	virtual bool slot53( Object *obj ) = 0;
#undef BFME_SPECIAL_SLOT
};

class BfmeOwnerLU
{
public:
	BfmeThingLU *bfmeTopLU( void );
};

class ControlBar
{
public:
	Object *findContainedObject( GameWindow *win );
};

extern ControlBar *TheControlBar;

extern void Rva004BC8A0( GameWindow *window );
extern void GadgetButtonDrawInverseClock( GameWindow *g, int percent, int color );

void Rva004BCCE0( GameWindow *window )
{
	if( window == 0 )
		return;

	void *userData = window->winGetUserData();
	if( userData == 0 )
		return;

	if( *( (unsigned char *)userData + 0x28 ) != 0 )
		Rva004BC8A0( window );

	Drawable *drawable = TheInGameUI->getFirstSelectedDrawable();
	if( drawable == 0 )
		return;

	Object *object = drawable->m_object;
	if( object == 0 )
		return;

	userData = window->winGetUserData();
	if( userData == 0 )
		return;

	BfmeOwnerLU *command = *(BfmeOwnerLU **)( (char *)userData + 0x14 );
	if( command == 0 )
		return;

	ProductionUpdateInterface *pui = object->getProductionUpdateInterface();
	if( pui != 0 )
	{
		int purpose = *(int *)( (char *)command + 0x10 );

		if( purpose == 3 )
		{
			BfmeCheckFH *thing = (BfmeCheckFH *)command->bfmeTopLU();

			Rva0029BBC0 *item = pui->slot18();
			while( item != 0 )
			{
				if( (char)item->isEither() )
				{
					if( thing->bfmeCheckFH( *(void **)( (char *)item + 8 ) ) )
					{
						GadgetButtonDrawInverseClock( window, ( (BfmeThingUKD *)item )->bfmeGoUKD(), 0x80FFFFFF );
						return;
					}
				}
				item = pui->slot19( item );
			}
			return;
		}
		else if( purpose == 5 || purpose == 6 || purpose == 7 )
		{
			void *compareKey = *(void **)( (char *)command + 0x20 );

			Rva0029BBC0 *item = pui->slot18();
			while( item != 0 )
			{
				if( *(int *)( (char *)item + 4 ) == 2 )
				{
					if( compareKey == *(void **)( (char *)item + 0xc ) )
					{
						GadgetButtonDrawInverseClock( window, ( (BfmeThingUKD *)item )->bfmeGoUKD(), 0x80FFFFFF );
						return;
					}
				}
				item = pui->slot19( item );
			}
			return;
		}

		return;
	}

	SpecialInterface *special = *(SpecialInterface **)( (char *)object + 0x1fc );
	if( special == 0 )
		return;

	Object *contained = TheControlBar->findContainedObject( window );
	if( contained == 0 )
		return;

	if( !special->slot53( contained ) )
		return;

	int scaled = *(int *)( (char *)contained + 0x74 );
	GadgetButtonDrawInverseClock( window, special->slot12( scaled ), 0x94FFCD6C );
}
