// ?isPowerCurrentlyInUse@SpecialAbilityUpdate@@QBE_NPBVCommandButton@@@Z
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum SpecialPowerType
{
	SPECIAL_REMOTE_CHARGES = 0x16
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *friend_getFinalOverride( void ) const;
	const Overridable *m_nextOverride;

	const Overridable *getFinalOverrideForReload( void ) const
	{
		const Overridable *next = m_nextOverride;
		if ( next )
		{
			if ( next->m_nextOverride )
				return next->m_nextOverride->friend_getFinalOverride();
			return next;
		}
		return this;
	}
};

class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType( void ) const
	{
		const SpecialPowerTemplate *self;
		const Overridable *next = m_nextOverride;

		if ( next )
		{
			if ( next->m_nextOverride )
				next = next->m_nextOverride->friend_getFinalOverride();

			self = (const SpecialPowerTemplate *)next;
		}
		else
			self = this;

		return self->m_specialPowerType;
	}

	UnsignedInt getReloadTime( void ) const
	{
		return ((const SpecialPowerTemplate *)getFinalOverrideForReload())->m_reloadTime;
	}

	__declspec(noinline) const SpecialPowerTemplate *getFO( void ) const
	{
		const Overridable *next = m_nextOverride;

		if ( next )
			next = next->m_nextOverride ? next->m_nextOverride->friend_getFinalOverride() : next;
		else
			next = this;

		return (const SpecialPowerTemplate *)next;
	}

	public:
	unsigned char m_unmodelled_08[0x14 - 8];
	SpecialPowerType m_specialPowerType;
	UnsignedInt m_reloadTime;
};

class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate( void ) const
	{
		return m_specialPowerTemplate;
	}

	UnsignedInt getOptions( void ) const
	{
		return m_options;
	}

private:
	unsigned char m_unmodelled_00[0x18];
	UnsignedInt m_options;
	unsigned char m_unmodelled_1c[0x18];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialAbilityUpdate
{
public:
	Bool isPowerCurrentlyInUse( const CommandButton *command = 0 ) const;

	UnsignedInt getSpecialObjectCount( void ) const
	{
		return m_specialObjectEntries;
	}

private:
	unsigned char m_unmodelled_00[0x10];
	UnsignedInt m_packingState;
	unsigned char m_unmodelled_14[0x9c];
	UnsignedInt m_specialObjectEntries;
	unsigned char m_unmodelled_b4[0x0e];
	Bool m_withinStartAbilityRange;
};

Bool SpecialAbilityUpdate::isPowerCurrentlyInUse( const CommandButton *command ) const
{
	if ( command )
	{
		const SpecialPowerTemplate *specialPowerTemplate = command->getSpecialPowerTemplate();
		if ( specialPowerTemplate &&
			specialPowerTemplate->getSpecialPowerType() == SPECIAL_REMOTE_CHARGES )
		{
			if ( !(command->getOptions() & 0x200) )
				return getSpecialObjectCount() == 0;
		}
	}

	if ( m_packingState != 0 )
	{
		if ( (m_packingState == 1 || m_packingState == 3) &&
			command && command->getSpecialPowerTemplate()->getReloadTime() == 0 )
			return false;

		if ( m_withinStartAbilityRange )
			return true;
	}

	return false;
}
