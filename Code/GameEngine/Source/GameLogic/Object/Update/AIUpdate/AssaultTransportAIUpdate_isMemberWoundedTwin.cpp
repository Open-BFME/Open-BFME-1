// cl: /DNDEBUG /MD /EHsc
// readable body of ?isMemberWounded@AssaultTransportAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp
// Open-BFME: AssaultTransportAIUpdate::isMemberWounded, retail 0x002B47A0.
//
// Layout twin: the tracked AssaultTransportAIUpdate.cpp definition (marked
// present-unmatched) uses the ZH getAssaultTransportAIUpdateModuleData()/
// getBodyModule() offsets, which come out 0x08, 0x194, and BodyModuleInterface
// vtable slots 0xc/0x10 in this build.  Retail's bytes want the module-data
// pointer at this+0x04, Object's body-module pointer at member+0x200,
// BodyModuleInterface::getHealth at vtable+0x10, getMaxHealth at vtable+0x18,
// and the ratio field at moduleData+0x64 -- all read directly off the retail
// disassembly (build/neardiff.py), not yet modelled by the shared headers.
// Kept self-contained so it does not touch AssaultTransportAIUpdate.cpp or
// any shared shim.

typedef int Real_i; // unused placeholder to keep includes minimal
typedef float Real;
typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0C() = 0;
	virtual Real getHealth() const = 0;			///< vtable +0x10
	virtual void bfmeSlot14() = 0;
	virtual Real getMaxHealth() const = 0;		///< vtable +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface * const *)((const char *)this + 0x200);
	}

private:
	char m_pad00[0x200];
	BodyModuleInterface *m_bodyModule;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h
struct AssaultTransportAIUpdateModuleData
{
	char m_pad00[0x64];
	Real m_membersGetHealedAtLifeRatio;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h
class AssaultTransportAIUpdate
{
public:
	virtual ~AssaultTransportAIUpdate() {}	// vtable ptr at +0x00 pushes m_moduleData to +0x04
	Bool isMemberWounded( const Object *member ) const;

private:
	const AssaultTransportAIUpdateModuleData *m_moduleData;	///< +0x04
};

// ?isMemberWounded@AssaultTransportAIUpdate@@QBE_NPBVObject@@@Z
Bool AssaultTransportAIUpdate::isMemberWounded( const Object *member ) const
{
	const AssaultTransportAIUpdateModuleData *data = m_moduleData;
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		Real ratio = body->getHealth() / body->getMaxHealth();
		if( ratio < data->m_membersGetHealedAtLifeRatio )
		{
			return true;
		}
	}
	return false;
}
