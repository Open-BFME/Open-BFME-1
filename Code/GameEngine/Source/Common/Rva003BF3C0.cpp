// cl: /DNDEBUG /MD
// Retail 003BF3C0: gated map selection, two coordinate lookups, then owner lookup.
// Conditional expression reproduces the retail null-result path.
struct ICoord2D { int x; int y; };
struct Rva00615D50Object { char pad[8]; int id; };
class Gen_00609320 { public: unsigned char bfmeDisabled() const; };

class Glo012F7048Type
{
public:
	bool test();
	char m_pad00[ 0x4 ];
	int m_at04;
};

extern Glo012F7048Type *Glo012F7048;

class Glo012F706CType
{
public:
	bool isOpen() const;
	Rva00615D50Object *lookup(const ICoord2D *position, int category);
};

extern Glo012F706CType *g_bfmeGameCW;

class Gen003BD7D0Node
{
public:
	char m_pad00[ 0x8 ];
	int m_at08;
};

class Rva003BF540
{
public:
	void run();
	bool anyMatching( int mask );
	bool anyReady() const;
	Gen003BD7D0Node *find( int id );
	void applyOwner( Gen003BD7D0Node *owner );

	char m_pad00[ 0x1C ];
	bool m_at1C;
	char m_pad1D[ 3 ];
	ICoord2D m_at20;
	char m_pad28[ 0x78 - 0x28 ];
	bool m_at78;
};

void Rva003BF540::run()
{
	if( !g_bfmeGameCW->isOpen() )
		goto fail;
	Glo012F7048Type *state = Glo012F7048;
	if( state->m_at04 != 0 )
	{
		if( state->test() )
			goto fail;
		if( m_at78 )
			goto fail;
		if( anyMatching( 4 ) )
			goto fail;
		if( anyMatching( 8 ) )
			goto fail;
		state = Glo012F7048;
	}
	if( ((Gen_00609320 *)state)->bfmeDisabled() )
		goto fail;
	if( anyReady() )
		goto fail;
	if( m_at1C )
	{
		const ICoord2D *key = &m_at20;
		Rva00615D50Object *found = g_bfmeGameCW->lookup( key, 1 );
		if( !found )
			found = g_bfmeGameCW->lookup( key, 0 );
		Gen003BD7D0Node *owner = found ? find(found->id) : 0;
		applyOwner(owner);
		return;
	}
fail:
	applyOwner( 0 );
}
