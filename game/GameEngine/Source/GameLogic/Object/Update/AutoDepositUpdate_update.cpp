// cl: /O2 /DNDEBUG /MD /GX /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "string_base.h"
#include "Lib/Coord3D.h"
class UnicodeString : private StringBase<unsigned short> {
public:
 UnicodeString() : StringBase<unsigned short>() {}
 UnicodeString(const UnicodeString &s) : StringBase<unsigned short>(s) {}
 ~UnicodeString() {}
 void __cdecl format(UnicodeString, ...);
};
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef Int Color;

#define TRUE 1
#define FALSE 0
#define NULL 0

#define CONSTRUCTION_COMPLETE -1.0f
#define GameMakeColor(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

class ModuleData;
class UpgradeTemplate;
class ObjectFilter;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum KindOfType
{
	KINDOF_0A = 10
};

class GameTextInterface { public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
 virtual UnicodeString fetch(const char *label, Bool *exists);
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define IGUI_SLOTS10(n) virtual void s##n##0(); virtual void s##n##1(); virtual void s##n##2(); \
	virtual void s##n##3(); virtual void s##n##4(); virtual void s##n##5(); virtual void s##n##6(); \
	virtual void s##n##7(); virtual void s##n##8(); virtual void s##n##9();
	IGUI_SLOTS10(0) IGUI_SLOTS10(1) IGUI_SLOTS10(2) IGUI_SLOTS10(3) IGUI_SLOTS10(4)
	IGUI_SLOTS10(5) IGUI_SLOTS10(6) IGUI_SLOTS10(7) IGUI_SLOTS10(8)
#undef IGUI_SLOTS10
	virtual void s90(); virtual void s91(); virtual void s92(); virtual void s93();
	virtual void addFloatingText(const UnicodeString &text, const Coord3D *pos, Color color); 
};
extern InGameUI *TheInGameUI;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	 

private:
	char m_unknown00[0x3C];
	UnsignedInt m_frame; 
};
extern GameLogic *TheGameLogic;

class GameLogicPortraitShim { public: bool isInMultiplayerOrSkirmishGame(); };
class PlayerList
{
public:
	int unidentified_000df510(bool flag); 
};
extern PlayerList *ThePlayerList;

class Gen_00083240
{
public:
	float bfmeGet0(int slot) const; 
};

class GlobalData
{
public:
	char m_pad000[0xEE0];
	Gen_00083240 m_multiPlayMults; 
};
extern class GlobalData *TheWritableGlobalData;

class Money { public: void deposit(unsigned amount, bool flag); char m_pad[4]; };
class ScoreKeeper { public: void addMoneyEarned(int amount); char m_pad[4]; };
class Rva000C97C0PlayerThunk { public: int unidentified_00024938(int amount); };
class Player
{
public: 
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade); 
	Bool hasAnyObjects(const ObjectFilter *mustBePresent, Bool flag) const; 
	Color getPlayerColor() const { return m_color; }

	char m_pad000[0x48];
	Money m_money; 
	char m_pad04C[0x1C4 - 0x4C];
	Color m_color; 
	char m_pad1C8[0x348 - 0x1C8];
	ScoreKeeper m_scoreKeeper; 
};

class ExperienceTracker
{
public:
	Bool isAcceptingExperiencePoints() const; 
	void addExperiencePoints(Real experience, Bool flag1, Bool flag2, Bool flag3, Bool unused); 
};

template <int N> class BitFlags { public: bool test(int i) const { return m_bits.test(i); } private: _STL::bitset<N> m_bits; };
typedef BitFlags<304> ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS
#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS \
    const Coord3D *getPosition() const { return &m_cachedPos; } \
    const ModelConditionFlags &getModelConditionFlags() const { return m_modelConditionFlags; } \
    bool isNeutralControlled() const; \
    Real getConstructionPercent() const { return m_constructionPercent; } \
    Player *getControllingPlayer() const; \
    bool getAttributeModifierMultiplier(int type, Real *value) const; \
    ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
#include "../../Object/object.h"
#undef OBJECT_TU_MEMBERS

class AutoDepositUpdateModuleData
{
public:
	char m_unknown00[0x08];
	UnsignedInt m_depositFrame; 
	Int m_depositAmount; 
	Int m_initialCaptureBonus; 
	const UpgradeTemplate *m_upgrade; 
	Real m_upgradeBonusPercent; 
	char m_upgradeMustBePresent[4]; 
	Bool m_giveNoXP; 
	Bool m_onlyWhenGarrisoned; 
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AutoDepositUpdate : public UpdateModule
{
public:
	
	virtual UpdateSleepTime update();

protected:
	const AutoDepositUpdateModuleData *getAutoDepositUpdateModuleData() const
	{
		return (const AutoDepositUpdateModuleData *)m_moduleData;
	}

	UnsignedInt m_nextFireFrame; 
	Bool m_awardInitialCaptureBonus; 
	Bool m_initialized; 
};

// Open BFME 2: Code/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdateUpdate.cpp
UpdateSleepTime AutoDepositUpdate::update( void )
{
	if( TheGameLogic->getFrame() >= m_nextFireFrame )
	{
		if (!m_initialized) {

			m_awardInitialCaptureBonus = TRUE;
			m_initialized = TRUE;
		}
		m_nextFireFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;

		if( getObject()->isNeutralControlled() || getAutoDepositUpdateModuleData()->m_depositAmount <= 0 )
			return UPDATE_SLEEP_NONE;

		if( getObject()->getConstructionPercent() != CONSTRUCTION_COMPLETE )
			return UPDATE_SLEEP_NONE;

		
		Bool condition05 = getObject()->getModelConditionFlags().test( 5 );
		Bool condition58 = getObject()->getModelConditionFlags().test( 58 );
		Bool condition59 = getObject()->getModelConditionFlags().test( 59 );
		if( condition05 || condition58 || condition59 )
			return UPDATE_SLEEP_NONE;

		Real multiplier = 1.0f;
		getObject()->getAttributeModifierMultiplier( 12, &multiplier );

		Player *player = getObject()->getControllingPlayer();
		const UpgradeTemplate *upgrade = getAutoDepositUpdateModuleData()->m_upgrade;
		if( upgrade && player && player->hasUpgradeComplete( upgrade )
			&& player->hasAnyObjects( (const ObjectFilter *)getAutoDepositUpdateModuleData()->m_upgradeMustBePresent, false ) )
			multiplier *= getAutoDepositUpdateModuleData()->m_upgradeBonusPercent;

		UnsignedInt moneyAmount = (UnsignedInt)( getAutoDepositUpdateModuleData()->m_depositAmount * multiplier );
		if( ((GameLogicPortraitShim *)TheGameLogic)->isInMultiplayerOrSkirmishGame() )
		{
			Real moneyMult = TheWritableGlobalData->m_multiPlayMults.bfmeGet0( ThePlayerList->unidentified_000df510( false ) );
			moneyAmount = (UnsignedInt)( moneyAmount * moneyMult );
		}
		moneyAmount = ((Rva000C97C0PlayerThunk *)player)->unidentified_00024938( moneyAmount );
		player->m_money.deposit( moneyAmount, true );
		player->m_scoreKeeper.addMoneyEarned(moneyAmount);

		ExperienceTracker *xp = getObject()->getExperienceTracker();
		if( xp && xp->isAcceptingExperiencePoints() )
			xp->addExperiencePoints( getAutoDepositUpdateModuleData()->m_depositAmount * multiplier, true, true, true, false );

		if( getAutoDepositUpdateModuleData()->m_depositAmount > 0 )
		{
			UnicodeString moneyString;
			moneyString.format( TheGameText->fetch( "GUI:AddCash", NULL ), moneyAmount );
			Coord3D pos;
			pos.x = getObject()->getPosition()->x;
			pos.y = getObject()->getPosition()->y;
			pos.z = getObject()->getPosition()->z;
			pos.z += 10.0f; 

			Color color = getObject()->getControllingPlayer()->getPlayerColor() | GameMakeColor( 0, 0, 0, 230 );
			TheInGameUI->addFloatingText( moneyString, &pos, color );
		}
	}

	return UPDATE_SLEEP_NONE;
}
