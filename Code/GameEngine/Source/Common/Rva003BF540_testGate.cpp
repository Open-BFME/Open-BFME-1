// cl: /DNDEBUG /MD /EHsc
//
// Rva003BF540::test, retail 0x003BEAF0, 77 bytes.
//
// Niladic gate on d_003b8450: non-empty owner span at +0x28/+0x14, anyReady,
// the global bfmeDisabled predicate, and anyMatching(4) all force false;
// otherwise !m_at78. if/else keeps the early false epilogue ahead of the call
// chain so later failures jump backward to it. Ternary (not unary !) required
// for the retail mov-al/test/setz epilogue.

struct Gen003BEAF0Span
{
	void **m_begin;
	void **m_end;

	unsigned size() const { return m_end - m_begin; }
};

class Gen003BEAF0Owner
{
public:
	char m_pad00[ 0x14 ];
	Gen003BEAF0Span m_items;
};

class Gen_00609320
{
public:
	unsigned char bfmeDisabled() const;
};

extern Gen_00609320 *g_bfmeStateDF;

class Rva003BF540
{
public:
	bool test();
	bool anyReady() const;
	bool anyMatching( int mask );

private:
	char m_pad00[ 0x28 ];
	Gen003BEAF0Owner *m_at28;
	char m_pad2C[ 0x4C ];
	bool m_at78;
};

// ?test@Rva003BF540@@QAE_NXZ
bool Rva003BF540::test()
{
	unsigned n = m_at28->m_items.size();
	if( n > 0 )
	{
		return false;
	}
	else
	{
		if( anyReady() )
			goto no;
		if( g_bfmeStateDF->bfmeDisabled() )
			goto no;
		if( anyMatching( 4 ) )
			goto no;
		return m_at78 ? false : true;
no:
		return false;
	}
}
