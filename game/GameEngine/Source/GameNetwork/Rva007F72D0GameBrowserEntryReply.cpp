// cl: /O2
// 0x007F72D0: FESL game-browser reply for a LID/GID entry.
//
// The callback thunk at 0x007F7350 proves a one-dword message argument and
// thiscall receiver.  The established game-key constructor supplies LID/GID;
// the receiver's matched 0x007F6A40 lookup proves its four-entry table, and
// the returned entry's +8 active word is cleared.  The literal "peri" is the
// only surviving entry name, so the handler name remains address-derived.

class Rva007E8810Message
{
public:
	int getError( void );
};

class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
};

struct BfmeEntryZI
{
	char m_head[ 8 ];
	int m_active;
};

class Rva007F7980Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void onSlot12( int lid, int gid, int status );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class BfmeThingZI
{
public:
	BfmeEntryZI *bfmeFindZI( int key, int other );
	void Rva007F72D0( Rva007E8810Message *msg );

private:
	char m_pad000[ 0x1c ];
	Rva007F7980Listener *m_listener;
};

void BfmeThingZI::Rva007F72D0( Rva007E8810Message *msg )
{
	Rva007FBC30GameKey key( msg );
	int lid = key.m_lid;
	int gid = key.m_gid;
	BfmeEntryZI *peri = bfmeFindZI( lid, gid );

	if( peri == 0 )
	{
		Rva007EB810Get()->fail(
			"peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x301 );
	}
	else
	{
		peri->m_active = 0;
	}

	m_listener->onSlot12( lid, gid, msg->getError() );
}
