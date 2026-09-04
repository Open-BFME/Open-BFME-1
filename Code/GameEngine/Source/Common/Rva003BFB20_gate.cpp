// cl: /DNDEBUG /MD /EHsc
//
// Rva003BFB20::run, retail 0x003BFB20, 77 bytes.
//
// WritableGlobalData[+0x90] gate on d_003b8450: probe(m_at28, &m_at30) into
// m_at80; on success step the campaign manager and finish(); always set
// owner[+0x10] and notify. Unused stack arg retained for ret 4.

class Glo012ED5C8Type
{
public:
	char m_pad00[ 0x90 ];
	bool m_at90;
};

extern Glo012ED5C8Type *TheWritableGlobalData;

class Glo012F1024Type
{
public:
	void step();
};

extern Glo012F1024Type *TheLivingWorldCampaignManager;

class Gen003BFB20Owner
{
public:
	bool probe( void * key );
	void notify();

	char m_pad00[ 0x10 ];
	bool m_at10;
};

class Rva003BFB20
{
public:
	void run( int unused );
	void finish();

private:
	char m_pad00[ 0x28 ];
	Gen003BFB20Owner *m_at28;
	char m_pad2C[ 0x4 ];
	char m_at30;
	char m_pad31[ 0x80 - 0x31 ];
	bool m_at80;
};

// ?run@Rva003BFB20@@QAEXH@Z
void Rva003BFB20::run( int unused )
{
	(void)unused;
	if( !TheWritableGlobalData->m_at90 )
		return;
	bool ok = m_at28->probe( &m_at30 );
	m_at80 = ok;
	if( ok )
	{
		TheLivingWorldCampaignManager->step();
		finish();
	}
	m_at28->m_at10 = true;
	m_at28->notify();
}
