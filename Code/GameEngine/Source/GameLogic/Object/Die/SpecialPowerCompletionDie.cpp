// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;
class DamageInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

protected:
	// The eight bytes this class used to carry unnamed. onDie reads both:
	// getObject() is [this-8] off the DieModuleInterface subobject, which is
	// object+0x08, and the module data is object+0x04.
	Object *getObject( void ) const { return m_obj; }
	const ModuleData *getModuleData( void ) const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;			///< retail this+0x04
	Object *m_obj;							///< retail this+0x08
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



// Reached as moduleData+0x08. Only the one member function is named; the
// DieModule::isDieApplicable wrapper below is inlined into onDie, which is why
// the receiver arrives as an `add ecx,8` on the module data rather than a call.
class DieMuxData
{
public:
	bool isDieApplicable( const Object *obj, const DamageInfo *damageInfo ) const;	///< ILT 0x000357D8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	DieMuxData m_dieMuxData;				///< retail moduleData+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	const DieModuleData *getDieModuleData( void ) const
	{
		return (const DieModuleData *)getModuleData();
	}

	// Not a separate body in retail -- it inlines into onDie, and it is what
	// makes onDie materialise the object base in a register instead of indexing
	// off the DieModuleInterface subobject it is entered with.
	bool isDieApplicable( const DamageInfo *damageInfo ) const
	{
		return getDieModuleData()->m_dieMuxData.isDieApplicable(getObject(), damageInfo);
	}

	DieModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData ),
		  m_deathType( 0 ),
		  m_isActive( false )
	{
	}

private:
	unsigned int m_deathType;
	bool m_isActive;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerCompletionDie.h
class SpecialPowerCompletionDie : public DieModule
{
public:
	SpecialPowerCompletionDie( Thing *, const ModuleData * );

	void notifyScriptEngine( void );		///< ILT 0x00017981

	virtual void onDie( const DamageInfo *damageInfo );
};

SpecialPowerCompletionDie::SpecialPowerCompletionDie(
	Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}

// ?onDie@SpecialPowerCompletionDie@@UAEXPBVDamageInfo@@@Z
// Retail 0x00256070. `this` arrives as the DieModuleInterface subobject at
// object+0x10 -- the body opens `lea esi,[ecx-0x10]` -- and DieModule's
// isDieApplicable wrapper is inlined away into the one call it makes.
void SpecialPowerCompletionDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;
	notifyScriptEngine();
}
