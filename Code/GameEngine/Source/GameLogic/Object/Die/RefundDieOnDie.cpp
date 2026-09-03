// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned short WCHAR;

class Thing;
class ModuleData;
class DamageInfo;
class UpgradeTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	void add( const Coord3D *that )
	{
		x += that->x;
		y += that->y;
		z += that->z;
	}
};

class ObjectFilter
{
public:
	bool isValid() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	void deposit( UnsignedInt amount, bool playSound = true );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	void addMoneyEarned( int amount );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool hasUpgradeComplete( const UpgradeTemplate *upgrade );
	bool hasAnyObjects( const ObjectFilter *filter, bool includeDead ) const;

	Money *getMoney()
	{
		return (Money *)((unsigned char *)this + 0x48);
	}

	ScoreKeeper *getScoreKeeper()
	{
		return (ScoreKeeper *)((unsigned char *)this + 0x348);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;

	UnsignedInt getStatusBits() const
	{
		return *(const UnsignedInt *)((const unsigned char *)this + 0x90);
	}

	float getEstimatedConstructionCost() const
	{
		return *(const float *)((const unsigned char *)this + 0x258);
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &that );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase(
			*(const StringBase<WCHAR> *)&that );
	}
	~UnicodeString();
	void format( UnicodeString format, ... );

private:
	void *m_data;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0;
	virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0; virtual void slot65() = 0;
	virtual void slot66() = 0; virtual void slot67() = 0;
	virtual void slot68() = 0; virtual void slot69() = 0;
	virtual void slot70() = 0; virtual void slot71() = 0;
	virtual void slot72() = 0; virtual void slot73() = 0;
	virtual void slot74() = 0; virtual void slot75() = 0;
	virtual void slot76() = 0; virtual void slot77() = 0;
	virtual void slot78() = 0; virtual void slot79() = 0;
	virtual void slot80() = 0; virtual void slot81() = 0;
	virtual void slot82() = 0; virtual void slot83() = 0;
	virtual void slot84() = 0; virtual void slot85() = 0;
	virtual void slot86() = 0; virtual void slot87() = 0;
	virtual void slot88() = 0; virtual void slot89() = 0;
	virtual void slot90() = 0; virtual void slot91() = 0;
	virtual void slot92() = 0; virtual void slot93() = 0;
	virtual void addFloatingText( const UnicodeString &text, const Coord3D *position,
		UnsignedInt color ) = 0;
};

extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;

float ceil( float value );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class DieMuxData
{
public:
	bool isDieApplicable( const Object *object, const DamageInfo *damageInfo ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	DieMuxData m_dieMuxData;
};

class RefundDieModuleData
{
public:
	unsigned char m_dieModuleData[0x34];
	const UpgradeTemplate *m_upgradeRequired;
	// Volatile preserves retail's two-load x87 multiply instead of folding this into fmul [mem].
	volatile float m_refundPercent;
	ObjectFilter m_buildingRequired;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	const DieModuleData *getDieModuleData() const
	{
		return (const DieModuleData *)getModuleData();
	}

	bool isDieApplicable( const DamageInfo *damageInfo ) const
	{
		return getDieModuleData()->m_dieMuxData.isDieApplicable(getObject(), damageInfo);
	}
};

class RefundDie : public DieModule
{
public:
	virtual void onDie( const DamageInfo *damageInfo );
};

// ?onDie@RefundDie@@UAEXPBVDamageInfo@@@Z
void RefundDie::onDie( const DamageInfo *damageInfo )
{
	if( !isDieApplicable(damageInfo) )
		return;

	Object *object = getObject();
	if( object == 0 )
		return;

	UnsignedInt status = object->getStatusBits();
	if( (status & 0x4) != 0 || (status & 0x80000) != 0 )
		return;

	const RefundDieModuleData *data = (const RefundDieModuleData *)getModuleData();
	if( data == 0 )
		return;

	Player *player = object->getControllingPlayer();
	if( player == 0 )
		return;

	if( data->m_upgradeRequired != 0
		&& !player->hasUpgradeComplete(data->m_upgradeRequired) )
		return;

	if( data->m_buildingRequired.isValid()
		&& !player->hasAnyObjects(&data->m_buildingRequired, false) )
		return;

	int refund = fast_float2long_round(
		ceil(object->getEstimatedConstructionCost() * data->m_refundPercent));
	if( refund )
	{
		player->getMoney()->deposit(refund, true);
		player->getScoreKeeper()->addMoneyEarned(refund);

		UnicodeString moneyString;
		moneyString.format(TheGameText->fetch("GUI:AddCash"), refund);
		Coord3D position;
		position.zero();
		position.add(object->getPosition());
		position.z += 10.0f;
		TheInGameUI->addFloatingText(moneyString, &position, 0xffffff00);
	}
}
