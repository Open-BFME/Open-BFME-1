// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: SpecialAbilityUpdate::createSpecialObject, retail 0x002A7540.
// The BFME ThingFactory ABI carries the default ObjectStatusMaskType through
// a four-slot call: the mask is a const reference followed by its hidden zero
// slot.  Keeping the mask as the real BitFlags temporary preserves that ABI
// and the retail MSVC 7.1 instruction order.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>

typedef unsigned int UnsignedInt;

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker
{
public:
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Team *getTeam() const { return m_team; }
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>( this ) + 0x38 );
	}
	void setPosition( const Coord3D *position );

	unsigned char m_unmodelled_00[0x74];
	UnsignedInt m_id;
	unsigned char m_unmodelled_78[0x210 - 0x78];
	ExperienceTracker *m_experienceTracker;
	unsigned char m_unmodelled_214[0x23c - 0x214];
	Team *m_team;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
	Object *newObject( ThingTemplate *, Team *,
		const volatile ObjectStatusMaskType &, void * );
};

extern ThingFactory *TheThingFactory;
extern void j_000434c3();
extern void j_0004494a();
extern void j_0001e9d4();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1e0];
	AsciiString m_specialObjectName;
	unsigned char m_unmodelled_1e1[0x218 - 0x1e1];
	UnsignedInt m_maxSpecialObjects;
	unsigned char m_unmodelled_21c[0x241 - 0x21c];
	unsigned char m_specialObjectsPersistent;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	Object *createSpecialObject();
	Object *getObject() const { return m_object; }

private:
	void killSpecialObjects();

	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_00c[0xcc - 0x0c];
	_STL::list<UnsignedInt> m_specialObjectIDList;
	UnsignedInt m_specialObjectEntries;
};

typedef void (__fastcall *SpecialAbilityCleanupCall)( SpecialAbilityUpdate * );
typedef Object *(__fastcall *ThingFactoryNewObjectCall)( ThingFactory *,
	ObjectStatusMaskType *, ThingTemplate *, Team *,
	const volatile ObjectStatusMaskType &, void * );
typedef void (__fastcall *ExperienceSinkCall)( ExperienceTracker *, Object *,
	UnsignedInt );

// ?createSpecialObject@SpecialAbilityUpdate@@QAEPAVObject@@XZ
Object *SpecialAbilityUpdate::createSpecialObject()
{
	SpecialAbilityUpdateModuleData *data = m_moduleData;
	Object *specialObject = 0;

	if ( m_specialObjectEntries == data->m_maxSpecialObjects )
	{
		if ( data->m_specialObjectsPersistent )
			return 0;
		((SpecialAbilityCleanupCall)j_000434c3)( this );
	}

	ThingTemplate *thingTemplate = TheThingFactory->findTemplate(
		data->m_specialObjectName );
	if ( thingTemplate )
	{
		ObjectStatusMaskType statusMask;
		specialObject = ((ThingFactoryNewObjectCall)j_0004494a)(
			TheThingFactory, &statusMask, thingTemplate,
			getObject()->getTeam(), statusMask, 0 );
		if ( specialObject )
		{
			UnsignedInt specialObjectID = specialObject->m_id;
			m_specialObjectIDList.push_back( specialObjectID );
			++m_specialObjectEntries;
			specialObject->setPosition( m_object->getPosition() );
			ExperienceTracker *tracker = specialObject->m_experienceTracker;
			if ( tracker )
				((ExperienceSinkCall)j_0001e9d4)( tracker, m_object,
					m_object->m_id );
		}
	}
	return specialObject;
}
