// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistringsetoutofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME5: clean C++ reconstruction of InGameUI::canSelectedObjectsEffectivelyUseWeapon.

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D;
class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON,
	TERTIARY_WEAPON,
	WEAPONSLOT_COUNT
};

enum CommandOption
{
	NEED_TARGET_ENEMY_OBJECT = 0x00000001,
	NEED_TARGET_NEUTRAL_OBJECT = 0x00000002,
	NEED_TARGET_ALLY_OBJECT = 0x00000004,
	NEED_TARGET_POS = 0x00000020,
	COMMAND_OPTION_NEED_OBJECT_TARGET =
		NEED_TARGET_ENEMY_OBJECT | NEED_TARGET_NEUTRAL_OBJECT | NEED_TARGET_ALLY_OBJECT
};

#define BitTest(value, mask) (((value) & (mask)) != 0)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
private:
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_options;
	unsigned char m_unreconstructed_1c[0x50];
	WeaponSlotType m_weaponSlot;

public:
	UnsignedInt getOptions() const { return m_options; }
	WeaponSlotType getWeaponSlot() const { return m_weaponSlot; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
private:
	unsigned char m_unreconstructed_00[0xfc];
	Object *m_object;

public:
	Object *getObject() { return m_object; }
	const Object *getObject() const { return m_object; }
};

typedef std::list<Drawable *> DrawableList;
typedef std::list<Drawable *>::const_iterator DrawableListCIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
    enum SelectionRules
    {
        SELECTION_ANY,
        SELECTION_ALL
    };
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(2A) BFME_UI_SLOT(2B)
	BFME_UI_SLOT(2C) BFME_UI_SLOT(2D) BFME_UI_SLOT(2E) BFME_UI_SLOT(2F)
	BFME_UI_SLOT(30) BFME_UI_SLOT(31) BFME_UI_SLOT(32) BFME_UI_SLOT(33)
	BFME_UI_SLOT(34) BFME_UI_SLOT(35) BFME_UI_SLOT(36) BFME_UI_SLOT(37)
	BFME_UI_SLOT(38) BFME_UI_SLOT(39) BFME_UI_SLOT(3A) BFME_UI_SLOT(3B)
	BFME_UI_SLOT(3C) BFME_UI_SLOT(3D) BFME_UI_SLOT(3E) BFME_UI_SLOT(3F)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(4A)
	virtual const DrawableList *getAllSelectedDrawables() const;
	Bool canSelectedObjectsEffectivelyUseWeapon( const CommandButton *command,
		const Object *objectToInteractWith, const Coord3D *position, SelectionRules rule ) const;
#undef BFME_UI_SLOT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	Bool canFireWeaponAtLocation( const Object *obj, const Coord3D *loc,
		CommandSourceType commandSource, const WeaponSlotType slot,
		const Object *objectInWay );
	Bool canFireWeaponAtObject( const Object *obj, const Object *target,
		CommandSourceType commandSource, const WeaponSlotType slot );
	Bool canFireWeapon( const Object *obj, const WeaponSlotType slot,
		CommandSourceType commandSource );
};

extern InGameUI *TheInGameUI;
extern ActionManager *TheActionManager;

// ?canSelectedObjectsEffectivelyUseWeapon@InGameUI@@QBE_NPBVCommandButton@@PBVObject@@PBUCoord3D@@W4SelectionRules@1@@Z
Bool InGameUI::canSelectedObjectsEffectivelyUseWeapon( const CommandButton *command,
	const Object *objectToInteractWith, const Coord3D *position, SelectionRules rule ) const
{
	//Get the special power template.
	WeaponSlotType slot = command->getWeaponSlot();

	//Order of precendence:
	//1) NO TARGET OR POS
	//2) COMMAND_OPTION_NEED_OBJECT_TARGET
	//3) NEED_TARGET_POS
	Bool doAtPosition = BitTest( command->getOptions(), NEED_TARGET_POS );
	Bool doAtObject = BitTest( command->getOptions(), COMMAND_OPTION_NEED_OBJECT_TARGET );

	//Sanity checks
	if( doAtObject && !objectToInteractWith )
	{
		return false;
	}
	if( doAtPosition && !position )
	{
		return false;
	}

	// get selected list of drawables
	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();

	// set up counters for rule checking
	Int count = 0;
	Int qualify = 0;

	// loop through all the selected drawables
	Drawable *other;
	for( DrawableListCIt it = selected->begin(); it != selected->end(); ++it )
	{
		// get this drawable
		other = *it;
		count++;

		if( !doAtObject && !doAtPosition )
		{
			if( TheActionManager->canFireWeapon( other->getObject(), slot, CMD_FROM_PLAYER ) )
			{
				//This is the no target version
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
		else if( doAtObject )
		{
			if( TheActionManager->canFireWeaponAtObject( other->getObject(), objectToInteractWith, CMD_FROM_PLAYER, slot ) )
			{
				//This requires a object target
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
		else if( doAtPosition )
		{
			if( TheActionManager->canFireWeaponAtLocation( other->getObject(), position, CMD_FROM_PLAYER, slot, objectToInteractWith ) )
			{
				//This requires a valid location.
				if( rule == SELECTION_ANY )
				{
					return true;
				}
				qualify++;
			}
		}
	}
	if( rule == SELECTION_ALL && count > 0 && qualify == count )
	{
		return true;
	}
	return false;
}
