// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoPickUpUpdate module-data constructor.
//
// The named factory at retail 0x00119B30 allocates 0x48 bytes and calls this
// body. The matched destructor at 0x00282A80 independently fixes the policy at
// +0x2C and twelve-byte owned member at +0x30.

#include <string.h>

struct AutoPickUpSixWords
{
	AutoPickUpSixWords()
	{
		memset( m_words, 0, sizeof( m_words ) );
	}

	unsigned int m_words[ 6 ];
};

struct RespawnPolicy
{
	unsigned int values[ 6 ];
};

class RespawnPolicyMember
{
public:
	RespawnPolicyMember();
	~RespawnPolicyMember();
	void setPolicies( RespawnPolicy first, RespawnPolicy second );

private:
	unsigned int m_value;
};

// The default policy is retail's global at 0x012ED8B8, which KindOf.cpp owns as
// `const BitFlags<192> KINDOFMASK_NONE`. This TU's RespawnPolicy is only a
// six-word view of that object, so the canonical extern is forward declared here
// and the view is cast at the use below. BitFlags is a class template, so its
// forward declaration mangles KINDOFMASK_NONE as
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B -- the one symbol KindOf.cpp defines.
template <int NUMBITS> class BitFlags;
extern const BitFlags<192> KINDOFMASK_NONE;

class AutoPickUpUpdateModuleDataMemberB
{
public:
	AutoPickUpUpdateModuleDataMemberB()
		: m_begin( 0 ), m_end( 0 ), m_capacity( 0 )
	{
	}
	~AutoPickUpUpdateModuleDataMemberB();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class __declspec(novtable) AutoPickUpUpdateModuleDataBase
{
public:
	virtual ~AutoPickUpUpdateModuleDataBase();

protected:
	unsigned int m_moduleData;
};

class AutoPickUpUpdateModuleData : public AutoPickUpUpdateModuleDataBase
{
public:
	AutoPickUpUpdateModuleData();
	virtual ~AutoPickUpUpdateModuleData();

private:
	unsigned int m_pickupCount;
	AutoPickUpSixWords m_searchValues;
	float m_pickupRadius;
	unsigned char m_enabled;
	unsigned char m_pad29[ 3 ];
	RespawnPolicyMember m_policy;
	AutoPickUpUpdateModuleDataMemberB m_ownedValues;
	unsigned char m_flag3C;
	unsigned char m_flag3D;
	unsigned char m_pad3E[ 2 ];
	unsigned int m_value40;
	unsigned char m_flag44;
	unsigned char m_pad45[ 3 ];
};

// ??0AutoPickUpUpdateModuleData@@QAE@XZ
AutoPickUpUpdateModuleData::AutoPickUpUpdateModuleData()
{
	m_pickupCount = 5;
	m_pickupRadius = 300.0f;
	m_enabled = 0;
	m_policy.setPolicies( *(const RespawnPolicy *)&KINDOFMASK_NONE,
	                      *(const RespawnPolicy *)&KINDOFMASK_NONE );
	m_flag3C = 0;
	m_flag3D = 0;
	m_value40 = 0;
	m_flag44 = 0;
}
