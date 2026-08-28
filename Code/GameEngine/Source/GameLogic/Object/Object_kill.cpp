// cl: /DNDEBUG /MD /EHsc
// readable body of ?kill@Object@@QAEXW4DamageType@@W4DeathType@@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::kill, retail 0x001C30F0. Zero Hour's body unchanged: build a
// DamageInfo, fill it with unmodifiable damage equal to the object's maximum
// health, mark it a kill, and put it through attemptDamage.
//
// The layout comes out of the stores. DamageInfo is 0x5C bytes with its input
// half at the front - source id at +0x08, damage type at +0x10, death type at
// +0x18, amount at +0x1C and the kill flag at +0x20 - and its constructor is
// out of line. The body module is at object+0x200 with getMaxHealth at +0x18 of
// its vtable, and attemptDamage is the object's own virtual at +0x34.
//
// Retail writes the two type fields before the sourceID and the flag last,
// which is scheduling: the source order is Zero Hour's.

typedef float Real;
typedef bool Bool;

enum DamageType {};
enum DeathType {};
enum ObjectID { INVALID_ID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfoInput
{
	unsigned char m_unmodelled_00[ 8 ];
	ObjectID m_sourceID;					// +0x08
	unsigned char m_unmodelled_0C[ 4 ];
	DamageType m_damageType;				// +0x10
	unsigned char m_unmodelled_14[ 4 ];
	DeathType m_deathType;					// +0x18
	Real m_amount;							// +0x1C
	Bool m_kill;							// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	DamageInfo();							// ILT thunk at 0x0002C9D5

	DamageInfoInput in;
	unsigned char m_unmodelled_24[ 0x5C - 0x24 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleAnchor00();
	virtual void bodyModuleAnchor04();
	virtual void bodyModuleAnchor08();
	virtual void bodyModuleAnchor0C();
	virtual void bodyModuleAnchor10();
	virtual void bodyModuleAnchor14();
	virtual Real getMaxHealth() const;		// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void kill( DamageType damageType, DeathType deathType );

	virtual void objectAnchor00();
	virtual void objectAnchor04();
	virtual void objectAnchor08();
	virtual void objectAnchor0C();
	virtual void objectAnchor10();
	virtual void objectAnchor14();
	virtual void objectAnchor18();
	virtual void objectAnchor1C();
	virtual void objectAnchor20();
	virtual void objectAnchor24();
	virtual void objectAnchor28();
	virtual void objectAnchor2C();
	virtual void objectAnchor30();
	virtual void attemptDamage( DamageInfo *damageInfo );	// +0x34

private:
	BodyModuleInterface *getBodyModule() const
	{
		return m_body;
	}

	unsigned char m_unmodelled_004[ 0x200 - 4 ];
	BodyModuleInterface *m_body;			// +0x200
};

// ?kill@Object@@QAEXW4DamageType@@W4DeathType@@@Z
void Object::kill( DamageType damageType, DeathType deathType )
{
	DamageInfo damageInfo;

	// Do unmodifiable damage equal to their max health to kill.
	damageInfo.in.m_damageType = damageType;
	damageInfo.in.m_deathType = deathType;
	damageInfo.in.m_sourceID = INVALID_ID;
	damageInfo.in.m_amount = getBodyModule()->getMaxHealth();
	damageInfo.in.m_kill = true;			// Triggers object to die no matter what.
	attemptDamage( &damageInfo );
}
