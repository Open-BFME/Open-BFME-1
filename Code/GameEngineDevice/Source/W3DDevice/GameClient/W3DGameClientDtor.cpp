// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Identity revision of the 307-byte dtor at 0x0079D1D0.
//
// RadarViewBoxEdge is an image name the matching ctor at 0x0079D9F0
// passes into a member. The vtables establish the W3DGameClient identity.
//
// Confirmed W3DGameClient:
//   GameClient : SubsystemInterface (vptr + name = 8), Snapshot (vptr at +8).
//   Primary vtable 0x01127A48 slot 2 is loadIniFilesFromLegend@SubsystemInterface.
//   Secondary vtable 0x01127A34 slot 0 is ILT 0x00033AF5 -> 0x0079D350 (W7A this-8
//   dtor adjustor). Slots 1-3 are ILTs to 0x00596940 / 0x00596950 / 0x005954E0,
//   GameClient Snapshot crc / xfer / loadPostProcess.
//   Parent call is ILT 0x00025FB8 -> GameClient dtor 0x00597680.
//   Code/W3DGameClient.cpp already marks ??1W3DGameClient@@UAE@XZ present-unmatched.
// ZH W3DGameClient::~W3DGameClient is empty; BFME added the radar/texture members
// cleaned here before the GameClient dtor.

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
protected:
	virtual void crc( Xfer *xfer ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	char m_name[4];
};

class GameClient : public SubsystemInterface, public Snapshot
{
public:
	virtual ~GameClient();
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

class RefCountClass
{
public:
	virtual void Delete_This( void );
	int NumRefs;
	void Release_Ref( void )
	{
		NumRefs--;
		if ( NumRefs == 0 )
			Delete_This();
	}
};

class RefObj : public RefCountClass
{
public:
	virtual void unused01();
	virtual void unused02();
	virtual void attach( RefCountClass * );
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad0a();
	virtual void pad0b();
	virtual void pad0c();
	virtual void pad0d();
	virtual void pad0e();
	virtual void pad0f();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad1a();
	virtual void pad1b();
	virtual void pad1c();
	virtual void pad1d();
	virtual void pad1e();
	virtual void pad1f();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad2a();
	virtual void pad2b();
	virtual void pad2c();
	virtual void pad2d();
	virtual void pad2e();
	virtual void pad2f();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad3a();
	virtual void pad3b();
	virtual void pad3c();
	virtual void pad3d();
	virtual void pad3e();
	virtual void pad3f();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad4a();
	virtual void pad4b();
	virtual void pad4c();
	virtual void pad4d();
	virtual void pad4e();
	virtual void pad4f();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual void pad5a();
	virtual void pad5b();
	virtual void pad5c();
	virtual void pad5d();
	virtual void pad5e();
	virtual void pad5f();
	virtual void pad60();
	virtual void pad61();
	virtual void pad62();
	virtual void pad63();
	virtual void pad64();
	virtual void pad65();
	virtual void pad66();
	virtual void pad67();
	virtual void pad68();
	virtual void pad69();
	virtual void pad6a();
	virtual void pad6b();
	virtual void pad6c();
	virtual void pad6d();
	virtual void pad6e();
	virtual void pad6f();
	virtual void pad70();
	virtual void pad71();
	virtual void pad72();
	virtual void pad73();
	virtual void pad74();
	virtual void pad75();
	virtual void pad76();
	virtual void pad77();
	virtual void pad78();
	virtual void pad79();
	virtual bool ready( void );
};

class TextureClass
{
public:
	void Release_Ref( void );
};

class TexPtr
{
public:
	TextureClass *p;
	~TexPtr()
	{
		if ( p )
			p->Release_Ref();
	}
};

class Pair8
{
public:
	int a;
	int b;
	~Pair8() {}
};

class W3DGameClient : public GameClient
{
public:
	virtual ~W3DGameClient();

	unsigned char m_pad[0x504];
	RefObj *m_510;
	RefObj *m_514;
	RefObj *m_518;
	void *m_51C;
	TexPtr m_tex;
	Pair8 m_arr0[4];
	Pair8 m_arr1[4];
	Pair8 m_arr2[4];
};

W3DGameClient::~W3DGameClient()
{
	if ( m_510 )
	{
		if ( m_518 )
		{
			if ( m_518->ready() )
				m_510->attach( m_518 );
		}
	}
	if ( m_518 )
	{
		m_518->Release_Ref();
		m_518 = 0;
	}
	if ( m_514 )
	{
		m_514->Release_Ref();
		m_514 = 0;
	}
	if ( m_510 )
	{
		m_510->Release_Ref();
		m_510 = 0;
	}
}
