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

extern unsigned fadeQueueKey;
void j_00049454();
void j_0003922a();
void j_00009a70();
void j_0000e2f5();

class BfmeAptScreenMainMenu
{
public:
	void rva0051F1C0Campaign( const char *campaign, bool evil );

private:
	unsigned char m_unmodelled00[ 0x25c ];
	unsigned char m_active25c;
};

class BfmeLivingWorldManagerIcons;
// Retail 0x012F1028 is EA's LivingWorldLogic *TheLivingWorldLogic;
// Rva012F1028Owner is this TU's view of the object.
class LivingWorldLogic;
class GlobalData;
extern int g_012B7638;
extern BfmeLivingWorldManagerIcons *TheLivingWorldManager;
static inline Rva012F706COwner *RVA012F706CView() { return (Rva012F706COwner *)TheLivingWorldManager; }
extern LivingWorldLogic *TheLivingWorldLogic;
static inline Rva012F1028Owner *RVA012F1028View() { return (Rva012F1028Owner *)TheLivingWorldLogic; }
extern GlobalData *TheWritableGlobalData;
static inline Rva012ED5C8Owner *RVA012ED5C8View() { return (Rva012ED5C8Owner *)TheWritableGlobalData; }

#define RVA012B7638 g_012B7638

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
		(RVA012F706CView()->*route.member)( evil );
	}

	if( (unsigned)campaign != (unsigned)zero )
	{
		int value = RVA012B7638;
		RVA012F1028View()->m_value90 = value;
	}

	postTimedOp( LoadGameFadeSlot( (void *)j_00049454 ),
		&fadeQueueKey );

	if( RVA012ED5C8View()->m_flag2a == (unsigned char)zero )
		postTimedOp( LoadGameFadeSlot( (void *)j_0003922a ),
			&fadeQueueKey );

	if( evil != (bool)zero )
		postTimedOp( LoadGameFadeSlot( (void *)j_00009a70 ),
			&fadeQueueKey );
	else
		postTimedOp( LoadGameFadeSlot( (void *)j_0000e2f5 ),
			&fadeQueueKey );

	m_active25c = 1;
}

#undef RVA012B7638
#undef RVA012F706CView()
#undef RVA012F1028View()
#undef RVA012ED5C8View()
