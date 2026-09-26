// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttributeModifierAuraUpdate module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0011A950 allocates 0xA8
// bytes and calls this constructor. The matched destructor at 0x00280C40
// independently fixes the string at +0x08, vector at +0x0C, attribute handle
// at +0x24, and UpgradeModuleData subobject at +0x28.

extern const char g_Rva0107301CEmptyString[];

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data( 0 ) {}
	~RetailLayoutString() { releaseBuffer(); }
	void clear() { set( g_Rva0107301CEmptyString, 0 ); }
	void set( const char *text, int length );

private:
	void releaseBuffer();
	char *m_data;
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	AttributeModifierAuraUpdateModuleDataMemberB()
		: m_begin( 0 ), m_end( 0 ), m_capacity( 0 )
	{
	}
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

private:
	unsigned int m_value;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub() throw();
	~UpgradeModuleDataSub();

private:
	unsigned char m_data[ 0x68 ];
};

class __declspec(novtable) AttributeModifierAuraUpdateModuleDataPrimaryBase
{
public:
	virtual ~AttributeModifierAuraUpdateModuleDataPrimaryBase();

private:
	unsigned int m_moduleData;
};

class AttributeModifierAuraUpdateModuleData
	: public AttributeModifierAuraUpdateModuleDataPrimaryBase
{
public:
	AttributeModifierAuraUpdateModuleData();
	virtual ~AttributeModifierAuraUpdateModuleData();

private:
	RetailLayoutString m_modifierName;
	AttributeModifierAuraUpdateModuleDataMemberB m_modules;
	unsigned int m_radius;
	unsigned int m_refreshDelay;
	unsigned char m_enabled;
	unsigned char m_affectSelf;
	unsigned char m_pad22[ 2 ];
	AttributeHandleStandIn m_attributeHandle;
	UpgradeModuleDataSub m_upgradeData;
	unsigned char m_targetEnemies;
	unsigned char m_pad91[ 3 ];
	unsigned int m_requiredKindOf;
	unsigned int m_forbiddenKindOf;
	unsigned int m_extraKindOf;
	unsigned char m_allowAllies;
	unsigned char m_allowEnemies;
	unsigned char m_allowNeutral;
	unsigned char m_allowDead;
	unsigned int m_maxCount;
};

// ??0AttributeModifierAuraUpdateModuleData@@QAE@XZ
AttributeModifierAuraUpdateModuleData::AttributeModifierAuraUpdateModuleData()
{
	m_forbiddenKindOf = 0;
	m_modifierName.clear();
	m_radius = 0;
	m_refreshDelay = 0;
	m_affectSelf = 0;
	m_targetEnemies = 0;
	m_requiredKindOf = 0;
	m_forbiddenKindOf = 0;
	m_extraKindOf = 0;
	m_allowAllies = 0;
	m_allowEnemies = 0;
	m_allowNeutral = 0;
	m_allowDead = 0;
	m_maxCount = 0;
	m_enabled = 1;
}
