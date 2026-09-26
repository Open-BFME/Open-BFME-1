// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PassiveAreaEffectBehavior module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00117650 allocates 0x24
// bytes and calls this constructor. Its matched destructor at 0x00202870
// independently fixes the twelve-byte owned range at +0x14 and handle at +0x20.

class PassiveAreaEffectBehaviorModuleDataMemberAFirst
{
public:
	PassiveAreaEffectBehaviorModuleDataMemberAFirst()
		: m_begin( 0 ), m_end( 0 )
	{
	}

	void *m_begin;
	void *m_end;
};

class PassiveAreaEffectBehaviorModuleDataMemberAEnd
{
public:
	PassiveAreaEffectBehaviorModuleDataMemberAEnd()
		: m_capacity( 0 )
	{
	}

private:
	void *m_capacity;
};

class PassiveAreaEffectBehaviorModuleDataMemberA
{
public:
	PassiveAreaEffectBehaviorModuleDataMemberA() {}
	~PassiveAreaEffectBehaviorModuleDataMemberA();

	void clear()
	{
		erase( m_first.m_begin, m_first.m_end );
	}

private:
	void erase( void *first, void *last );
	PassiveAreaEffectBehaviorModuleDataMemberAFirst m_first;
	PassiveAreaEffectBehaviorModuleDataMemberAEnd m_end;
};

class PassiveAreaEffectBehaviorModuleDataMemberB
{
public:
	PassiveAreaEffectBehaviorModuleDataMemberB();
	~PassiveAreaEffectBehaviorModuleDataMemberB();

private:
	unsigned int m_value;
};

class __declspec(novtable) PassiveAreaEffectBehaviorModuleDataBase
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleDataBase();

protected:
	unsigned int m_moduleData;
	float m_radius;
	unsigned int m_value0C;
	unsigned int m_updateDelay;
};

class PassiveAreaEffectBehaviorModuleData
	: public PassiveAreaEffectBehaviorModuleDataBase
{
public:
	PassiveAreaEffectBehaviorModuleData();
	virtual ~PassiveAreaEffectBehaviorModuleData();

private:
	PassiveAreaEffectBehaviorModuleDataMemberA m_ownedValues;
	PassiveAreaEffectBehaviorModuleDataMemberB m_handle;
};

// ??0PassiveAreaEffectBehaviorModuleData@@QAE@XZ
PassiveAreaEffectBehaviorModuleData::PassiveAreaEffectBehaviorModuleData()
{
	m_radius = 200.0f;
	m_updateDelay = 15;
	m_value0C = 0;
	m_ownedValues.clear();
}
