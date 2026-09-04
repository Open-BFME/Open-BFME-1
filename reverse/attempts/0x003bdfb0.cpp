// ?isMissionObjectiveIndexed@CampaignManager@@QAEEH@Z
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CampaignManager::isMissionObjectiveIndexed at retail 0x003BDFB0
// (80B). Same guarded Gen003C8A50::find(&m_key) as Rva003BDF70CombinedSpanCount;
// true when index falls in the second four-byte span.
//
// Wall: body is instruction-identical through the span compares (71B) but the
// range success/fail epilogue emits mov al,1 / shared xor al,al, while retail
// uses mov eax,1 plus a separate xor eax,eax path for range misses and keeps
// xor al,al only for the early guards — same split as isMissionObjectiveComplete
// at 0x003BF6C0 (which gets it "for free" because it tests a flag byte in al).
// Int return yields the eax immediates but collapses the early xor al,al into
// xor eax,eax (74B). No spelling so far produces both epilogues together.

extern "C" void _ReadWriteBarrier(void);
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
			{
				unsigned first = (unsigned)found->m_first.size();
				if ( (unsigned)idx >= first )
				{
					unsigned second = (unsigned)found->m_second.size();
					unsigned total = first + second;
					if ( (unsigned)idx < total )
					{
						_ReadWriteBarrier();
						return 1;
					}
					_ReadWriteBarrier();
					return 0;
				}
				_ReadWriteBarrier();
				return 0;
			}
		}
	}
	return 0;
}
