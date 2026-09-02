// ?accepts00216690@Rva00216690Predicate@@QBE_NXZ
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD
// Address-derived two-mask predicate at retail RVA 0x00216690.

class ObjectStatusMaskType
{
public:
	bool testForAny( const ObjectStatusMaskType &other ) const;
	void set( unsigned int word0, unsigned int word1, unsigned int word2 )
	{
		m_words[ 0 ] = word0;
		m_words[ 1 ] = word1;
		m_words[ 2 ] = word2;
	}
	unsigned int m_words[ 3 ];
};

struct Rva00216690Policy
{
	char m_unmodelled_000[ 0x0c ];
	ObjectStatusMaskType m_excluded;
	ObjectStatusMaskType m_required;
	bool m_allowEmpty;
};

struct Rva00216690StatusOwner
{
	char m_unmodelled_000[ 0x90 ];
	ObjectStatusMaskType m_status;
};

class Rva00216690Predicate
{
public:
	bool accepts00216690() const;
private:
	unsigned int m_unmodelled_000;
	Rva00216690Policy *m_policy;
	Rva00216690StatusOwner *m_owner;
	char m_unmodelled_00c[ 0x18 - 0x0c ];
	bool m_allowEmpty;
};

bool Rva00216690Predicate::accepts00216690() const
{
	Rva00216690Policy *policy = m_policy;
	unsigned int word0 = m_owner->m_status.m_words[ 0 ];
	unsigned int word1 = m_owner->m_status.m_words[ 1 ];
	unsigned int word2 = m_owner->m_status.m_words[ 2 ];
	ObjectStatusMaskType status;
	status.set( word0, word1, word2 );
	if( status.testForAny( policy->m_required ) )
		return false;
	status.set( ~word0, ~word1, ~word2 & 0x003fffff );
	if( status.testForAny( policy->m_excluded ) )
		return false;
	if( m_allowEmpty && policy->m_allowEmpty )
		return false;
	return true;
}
