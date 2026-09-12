// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

enum MaxHealthChangeType
{
	SAME_CURRENTHEALTH,
	PRESERVE_RATIO,
	ADD_CURRENT_HEALTH_TOO,
	FULLY_HEAL,
};

class BodyModuleInterface
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14(); virtual void pad18(); virtual void pad1C();
	virtual void pad20(); virtual void pad24(); virtual void pad28(); virtual void pad2C();
	virtual void pad30(); virtual void pad34(); virtual void pad38(); virtual void pad3C();
	virtual void pad40(); virtual void pad44(); virtual void pad48(); virtual void pad4C();
	virtual void pad50(); virtual void pad54(); virtual void pad58(); virtual void pad5C();
	virtual void pad60(); virtual void pad64(); virtual void pad68(); virtual void pad6C();
	virtual void pad70(); virtual void pad74(); virtual void pad78(); virtual void pad7C();
	virtual void internalChangeHealth( Real delta, Bool something );
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType );
};

class ActiveBody : public BodyModuleInterface
{
public:
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType );

private:
	unsigned char m_pad04[4];
	Real m_currentHealth;      // +0x08
	unsigned char m_pad0C[4];
	Real m_maxHealth;          // +0x10
	unsigned char m_pad14[8];
	Real m_initialHealth;      // +0x1C
};

void ActiveBody::setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType )
{
	Real prevMaxHealth = m_maxHealth;
	m_maxHealth = maxHealth;
	m_initialHealth = maxHealth;

	switch( healthChangeType )
	{
		case PRESERVE_RATIO:
		{
			Real ratio = m_currentHealth / prevMaxHealth;
			Real newHealth = maxHealth * ratio;
			internalChangeHealth( newHealth - m_currentHealth, false );
			break;
		}
		case ADD_CURRENT_HEALTH_TOO:
		{
			internalChangeHealth( maxHealth - prevMaxHealth, false );
			break;
		}
		default:
			break;
	}

	if( m_currentHealth > maxHealth )
	{
		internalChangeHealth( maxHealth - m_currentHealth, false );
	}
}
