// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BfmeAptScreenMainMenu campaign callback body, retail 0x0051F1C0 (331B).
// The matched GoodCampaign/EvilCampaign wrappers establish the owner class and
// thiscall signature.  The body selects the campaign mode, stops the active
// AQA operation through the proven 0x00040840 thunk, then posts the observed
// LoadGameFadeHolder callback sequence and marks +0x25c active.

class Rva012F706COwner
{
public:
	void rva00040840( bool what );
};

// The member-call receiver is visible in the retail call setup.  The thunk and
// its target are already independently matched; this is only an address-derived
// ABI view, not a semantic identity claim.  The union is the established
// raw-function-to-member ABI bridge used by the matched callers in this tree.
extern void j_00040840();

class Rva012F1028Owner
{
public:
	unsigned char m_pad00[ 0x90 ];
	int m_value90;
};

class Rva012ED5C8Owner
{
public:
	unsigned char m_pad00[ 0x2a ];
	unsigned char m_flag2a;
};

struct LoadGameFadeSlot
{
	LoadGameFadeSlot( void *fn ) : m_fn( fn ) {}

	void *m_fn;
};

class LoadGameFadeWrapperHead
{
public:
	LoadGameFadeWrapperHead() throw() : m_refCount( 0 ) {}
	virtual void loadGameFadeWrapperAnchor();

	unsigned int m_refCount;
};

class LoadGameFadeWrapper : public LoadGameFadeWrapperHead
{
public:
	__forceinline LoadGameFadeWrapper( const LoadGameFadeSlot &slot ) throw()
		: m_slot( slot ) {}

	LoadGameFadeSlot m_slot;
};

class LoadGameFadeHolder
{
public:
	__forceinline LoadGameFadeHolder( LoadGameFadeSlot binding ) throw()
	{
		m_ptr = new LoadGameFadeWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	~LoadGameFadeHolder() {}

	LoadGameFadeWrapper *m_ptr;
};

void postTimedOp( LoadGameFadeHolder holder, void *key );

class BfmeAptScreenMainMenu
{
public:
	void rva0051F1C0Campaign( const char *campaign, bool evil );

private:
	unsigned char m_unmodelled00[ 0x25c ];
	unsigned char m_active25c;
};

#define RVA012B7638 (*(int *)0x012B7638)
#define RVA012F706C (*(Rva012F706COwner **)0x012F706C)
#define RVA012F1028 (*(Rva012F1028Owner **)0x012F1028)
#define RVA012ED5C8 (*(Rva012ED5C8Owner **)0x012ED5C8)

// ?rva0051F1C0Campaign@BfmeAptScreenMainMenu@@QAEXPBD_N@Z
void BfmeAptScreenMainMenu::rva0051F1C0Campaign( const char *campaign, bool evil )
{
	int zero = 0;

	if( (unsigned)campaign != (unsigned)zero )
	{
		if( *campaign != 'E' )
			RVA012B7638 = ( *campaign == 'H' ) + 1;
		else
			RVA012B7638 = zero;
	}

	{
		typedef void (Rva012F706COwner::*Call)( bool );
		union
		{
			void (*plain)();
			Call member;
		} route;
		route.plain = j_00040840;
		(RVA012F706C->*route.member)( evil );
	}

	if( (unsigned)campaign != (unsigned)zero )
	{
		int value = RVA012B7638;
		RVA012F1028->m_value90 = value;
	}

	postTimedOp( LoadGameFadeSlot( (void *)0x00449454 ),
		reinterpret_cast<void *>( 0x012ED588 ) );

	if( RVA012ED5C8->m_flag2a == (unsigned char)zero )
		postTimedOp( LoadGameFadeSlot( (void *)0x0043922A ),
			reinterpret_cast<void *>( 0x012ED588 ) );

	if( evil != (bool)zero )
		postTimedOp( LoadGameFadeSlot( (void *)0x00409A70 ),
			reinterpret_cast<void *>( 0x012ED588 ) );
	else
		postTimedOp( LoadGameFadeSlot( (void *)0x0040E2F5 ),
			reinterpret_cast<void *>( 0x012ED588 ) );

	m_active25c = 1;
}

#undef RVA012B7638
#undef RVA012F706C
#undef RVA012F1028
#undef RVA012ED5C8
