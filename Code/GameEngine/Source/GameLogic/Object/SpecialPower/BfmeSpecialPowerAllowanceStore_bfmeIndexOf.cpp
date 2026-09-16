// ?bfmeIndexOf@BfmeSpecialPowerAllowanceStore@@AAEHPBVSpecialPowerTemplate@@@Z

typedef int Int;

class Overridable
{
public:
	Overridable *friend_getFinalOverride( void );
	const Overridable *friend_getFinalOverride( void ) const
	{
		return const_cast<Overridable *>( this )->friend_getFinalOverride();
	}

	char m_bfmeHeadA[0x04];
	Overridable *m_bfmeNextOverride;
	char m_bfmeHeadB[0x10 - 0x08];
	void *m_bfmeKey;
};

class SpecialPowerTemplate : public Overridable
{
};

class BfmeAllowanceGroup;

class BfmeGroupVector
{
public:
	BfmeAllowanceGroup **begin( void ) { return m_bfmeBegin; }
	BfmeAllowanceGroup **end( void ) { return m_bfmeEnd; }
	unsigned size( void ) { return (unsigned)(m_bfmeEnd - m_bfmeBegin); }

private:
	BfmeAllowanceGroup **m_bfmeBegin;
	BfmeAllowanceGroup **m_bfmeEnd;
};

class BfmeEntryVector
{
public:
	void **begin( void ) const { return m_bfmeBegin; }
	void **end( void ) const { return m_bfmeEnd; }
	unsigned size( void ) const { return (unsigned)(m_bfmeEnd - m_bfmeBegin); }

private:
	void **m_bfmeBegin;
	void **m_bfmeEnd;
};

class BfmeAllowanceGroup
{
public:
	char m_bfmeHead[0x14];
	BfmeEntryVector m_bfmeEntries;
};

class BfmeSpecialPowerAllowanceStore
{
private:
	Int bfmeIndexOf( const SpecialPowerTemplate *tmpl );
	char m_bfmeHead[0x08];
	BfmeGroupVector m_bfmeGroups;
};

Int BfmeSpecialPowerAllowanceStore::bfmeIndexOf( const SpecialPowerTemplate *tmpl )
{
	unsigned outer = m_bfmeGroups.size();
	unsigned i = 0;
	if (outer <= 0)
		goto noMatch;
	BfmeAllowanceGroup **current = m_bfmeGroups.begin();

	while (i < outer)
	{
		const BfmeAllowanceGroup *group = *current;
		Int inner = group->m_bfmeEntries.size();
		Int j = 0;
		const SpecialPowerTemplate *next;
		if ((unsigned)inner <= 0)
			goto nextGroup;
		void **innerBegin = group->m_bfmeEntries.begin();
		next = (const SpecialPowerTemplate *)tmpl->m_bfmeNextOverride;

		do
		{
			const SpecialPowerTemplate *finalTmpl;

			if (next)
			{
				if (next->m_bfmeNextOverride)
					finalTmpl = (const SpecialPowerTemplate *)
						next->m_bfmeNextOverride->friend_getFinalOverride();
				else
					finalTmpl = next;
			}
			else
			{
				finalTmpl = tmpl;
			}

			if (innerBegin[j] == finalTmpl->m_bfmeKey)
				return (Int)i;

			++j;
			inner = group->m_bfmeEntries.size();
		}
		while ((unsigned)j < (unsigned)inner);

	nextGroup:
		++i;
		++current;
		outer = m_bfmeGroups.size();
	}

noMatch:
	return -1;
}
