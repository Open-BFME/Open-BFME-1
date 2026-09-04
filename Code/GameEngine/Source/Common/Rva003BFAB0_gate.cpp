// cl: /DNDEBUG /MD /EHsc
//
// Rva003BFAB0::run, retail 0x003BFAB0, 87 bytes.
//
// Sibling of Rva003BFB20::run on d_003b8450: always probe(m_at28, &m_at30) into
// m_at80; on a false stack flag write the +0xC8/+0xCC/+0x78/+0x7C fail block and
// return; otherwise on probe success step the campaign manager and finish().

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
};

class Rva003BFAB0
{
public:
	void run( bool flag );
	void finish();

private:
	char m_pad00[ 0x28 ];
	Gen003BFB20Owner *m_at28;
	char m_pad2C[ 0x4 ];
	char m_at30;
	char m_pad31[ 0x78 - 0x31 ];
	bool m_at78;
	char m_pad79[ 0x7C - 0x79 ];
	int m_at7C;
	bool m_at80;
	char m_pad81[ 0xC8 - 0x81 ];
	bool m_atC8;
	char m_padC9[ 0xCC - 0xC9 ];
	int m_atCC;
};

// ?run@Rva003BFAB0@@QAEX_N@Z
void Rva003BFAB0::run( bool flag )
{
	bool ok = m_at28->probe( &m_at30 );
	m_at80 = ok;
	if( !flag )
	{
		m_atC8 = true;
		m_atCC = 0x78;
		m_at78 = true;
		m_at7C = 0x1E;
		return;
	}
	if( ok )
	{
		TheLivingWorldCampaignManager->step();
		finish();
	}
}
