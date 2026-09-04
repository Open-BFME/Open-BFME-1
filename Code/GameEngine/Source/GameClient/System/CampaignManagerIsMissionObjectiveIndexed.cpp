// ?isMissionObjectiveIndexed@CampaignManager@@QAEEH@Z
// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic(_ReadWriteBarrier)

struct Rva003BDF70Span
{
	void **m_begin;
	void **m_end;
	int size() const { return m_end - m_begin; }
};

class Gen003C8A50Result
{
public:
	char m_pad00[ 0x54 ];
	Rva003BDF70Span m_first;
	char m_pad5C[ 0x4 ];
	Rva003BDF70Span m_second;
};

class Gen003C8A50
{
public:
	Gen003C8A50Result *find( const char *key );
};

static __forceinline int isInSecondSpan( const Gen003C8A50Result *found, unsigned index )
{
	unsigned first = (unsigned)found->m_first.size();
	if ( index < first )
	{
		_ReadWriteBarrier();
		return 0;
	}

	unsigned second = (unsigned)found->m_second.size();
	unsigned total = first + second;
	if ( index < total )
	{
		_ReadWriteBarrier();
		return 1;
	}
	_ReadWriteBarrier();
	return 0;
}

class CampaignManager
{
public:
	unsigned char isMissionObjectiveIndexed( int index );

private:
	char m_pad00[ 0x28 ];
	Gen003C8A50 *m_resolver;
	char m_pad2C[ 0x4 ];
	char m_key;
};

unsigned char CampaignManager::isMissionObjectiveIndexed( int index )
{
	Gen003C8A50 *resolver = m_resolver;
	if ( resolver )
	{
		int idx = index;
		if ( idx >= 0 )
		{
			Gen003C8A50Result *found = resolver->find( &m_key );
			if ( found )
				return isInSecondSpan( found, (unsigned)idx );
		}
	}
	return 0;
}
