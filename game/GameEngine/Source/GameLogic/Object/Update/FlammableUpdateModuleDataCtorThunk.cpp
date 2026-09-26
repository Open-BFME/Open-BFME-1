// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FlammableUpdate module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00118460 allocates 0x54
// bytes and calls this constructor. Its matched destructor at 0x00294C40
// independently fixes the string at +0x18 and FireFXList vector at +0x24.

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data( 0 ) {}
	~RetailLayoutString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class FlammableUpdateModuleDataMemberB
{
public:
	FlammableUpdateModuleDataMemberB()
		: m_begin( 0 ), m_end( 0 ), m_capacity( 0 )
	{
	}
	~FlammableUpdateModuleDataMemberB();

	void clear()
	{
		erase( m_begin, m_end );
	}

private:
	void erase( void *first, void *last );
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class __declspec(novtable) FlammableUpdateModuleDataBase
{
public:
	virtual ~FlammableUpdateModuleDataBase();

protected:
	unsigned int m_moduleData;
	unsigned int m_burnedDelay;
	unsigned int m_aflameDuration;
	unsigned int m_aflameDamageDelay;
	int m_aflameDamageAmount;
};

class FlammableUpdateModuleData : public FlammableUpdateModuleDataBase
{
public:
	FlammableUpdateModuleData();
	virtual ~FlammableUpdateModuleData();

private:
	RetailLayoutString m_burningSoundName;
	float m_flameDamageLimitData;
	unsigned int m_flameDamageExpirationDelay;
	FlammableUpdateModuleDataMemberB m_fireFXList;
	unsigned char m_enabled;
	unsigned char m_affectSelf;
	unsigned char m_affectAllies;
	unsigned char m_affectEnemies;
	unsigned char m_affectNeutral;
	unsigned char m_affectDead;
	unsigned char m_pad36[ 2 ];
	unsigned int m_fxDelay;
	float m_range;
	float m_height;
	unsigned char m_looping;
	unsigned char m_pad45[ 3 ];
	int m_damageType;
	unsigned int m_extra0;
	unsigned int m_extra1;
};

// ??0FlammableUpdateModuleData@@QAE@XZ
FlammableUpdateModuleData::FlammableUpdateModuleData()
{
	m_burnedDelay = 0;
	m_aflameDuration = 0;
	m_aflameDamageDelay = 0;
	m_aflameDamageAmount = 0;
	m_burningSoundName.clear();
	m_flameDamageLimitData = 20.0f;
	m_flameDamageExpirationDelay = 25;
	m_fireFXList.clear();
	m_enabled = 0;
	m_affectSelf = 0;
	m_affectAllies = 0;
	m_affectEnemies = 0;
	m_affectNeutral = 0;
	m_affectDead = 0;
	m_fxDelay = 0;
	m_looping = 0;
	m_extra0 = 0;
	m_extra1 = 0;
	m_range = 200.0f;
	m_height = 60.0f;
	m_damageType = -1;
}
