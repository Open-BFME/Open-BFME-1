// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: SpecialAbilityUpdate constructor, reconstructed from the retail
// field order and the module's recovered ABI.  The original class grew a few
// private flags between the public Generals header and the BFME build; the
// prefix view keeps those offsets local to this TU.

#include <list>

class Thing;
class ModuleData;
class Object;

class __declspec(novtable) ObjectModule
{
public:
	ObjectModule( Thing *, const ModuleData * );
	virtual void objectModuleAnchor();

private:
	unsigned int m_moduleData;
	Object *m_object;
};

// UpdateModule::setWakeFrame is the shared retail helper at ILT 0x000157DA.
class __declspec(novtable) UpdateModule : public ObjectModule
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}

protected:
	void setWakeFrame( Object *, unsigned int );
};

class SpecialAbilityUpdateBaseC
{
public:
	virtual void specialAbilityBaseCAnchor();
};

class SpecialAbilityUpdateBase10
{
public:
	virtual void specialAbilityBase10Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) SpecialAbilityUpdateBase20
{
public:
	virtual void specialAbilityBase20Anchor();
};

extern "C" char SpecialAbilityUpdateBase_vtbl20;

// The retail SpecialPowerUpdateModule constructor inlines UpdateModule and
// leaves this four-subobject prefix for the most-derived constructor to reset.
class __declspec(novtable) SpecialAbilityUpdateBase : public UpdateModule,
	public SpecialAbilityUpdateBaseC,
	public SpecialAbilityUpdateBase10,
	public SpecialAbilityUpdateBase20
{
public:
	__forceinline SpecialAbilityUpdateBase( Thing *thing, const ModuleData *moduleData )
		: UpdateModule( thing, moduleData )
	{
		unsigned char *whole = reinterpret_cast<unsigned char *>( this );
		*reinterpret_cast<unsigned int *>( whole + 0x18 ) = 0xffffffff;
		*reinterpret_cast<unsigned int volatile *>( whole + 0x14 ) = 0;
		*reinterpret_cast<unsigned int *>( whole + 0x1c ) = 0xffffffff;
		*reinterpret_cast<char *volatile *>( whole + 0x20 ) = &SpecialAbilityUpdateBase_vtbl20;
	}
	virtual ~SpecialAbilityUpdateBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS( void *, int );
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

// ??0SpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public SpecialAbilityUpdateBase
{
public:
	SpecialAbilityUpdate( Thing *, const ModuleData * );
	virtual void specialAbilityAnchor();

private:
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	AudioEventRTS m_prepSoundLoop;
	unsigned int m_prepFrames;
	unsigned int m_animFrames;
	unsigned int m_targetID;
	unsigned int m_targetX;
	unsigned int m_targetY;
	unsigned int m_targetZ;
	unsigned int m_locationCount;
	unsigned int m_preList0;
	unsigned int m_preList1;
	unsigned int m_preList2;
	_STL::list<int> m_specialObjectIDList;
	unsigned int m_specialObjectEntries;
	float m_captureFlashPhase;
	unsigned int m_packingState;
	unsigned char m_flag0;
	unsigned char m_flag1;
	unsigned char m_flag2;
	unsigned char m_flag3;
	unsigned char m_flag4;
	unsigned char m_flag5;
	unsigned char m_flag6;
	unsigned char m_flag7;
	unsigned char m_flag8;
	unsigned char m_flag9;
};

SpecialAbilityUpdate::SpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData )
	: SpecialAbilityUpdateBase( thing, moduleData ),
	  m_24( 0 ),
	  m_28( 0 ),
	  m_2c( 0 ),
	  m_30( 0 ),
	  m_prepSoundLoop( reinterpret_cast<void *>( 0x01336e50 ), 0 ),
	  m_prepFrames( 1 ),
	  m_animFrames( 0 ),
	  m_targetID( 0 ),
	  m_targetX( 0 ),
	  m_targetY( 0 ),
	  m_targetZ( 0 ),
	  m_locationCount( 0 ),
	  m_preList0( 0 ),
	  m_preList1( 0 ),
	  m_preList2( 0 ),
	  m_specialObjectIDList(),
	  m_specialObjectEntries( 0 ),
	  m_captureFlashPhase( 0.0f ),
	  m_packingState( 0 ),
	  m_flag0( 0 ),
	  m_flag1( 0 ),
	  m_flag2( 0 ),
	  m_flag3( 0 ),
	  m_flag4( 0 ),
	  m_flag5( 0 ),
	  m_flag6( 0 ),
	  m_flag7( 1 ),
	  m_flag8( 0 ),
	  m_flag9( 0 )
{
	setWakeFrame( *reinterpret_cast<Object **>( reinterpret_cast<unsigned char *>( this ) + 8 ),
		0x3fffffff );
}
