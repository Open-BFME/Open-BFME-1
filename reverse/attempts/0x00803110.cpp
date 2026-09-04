// ?bfmeSend1028@BfmeSink1028@@QAEXHPAH0@Z
// partial score=0.7 date=2026-09-04
// cl: /GX- /GS
// jabba gamebrowserpinger.cpp add-pending-request @ 0x00803110 (332B).
// Asserts m_08 / capacity 0x80; bfmeGoUVB formats address; Rva008085A0 sends
// 8-byte (*b,*c) payload; records id+tick+args; bfmeSetVMO(count+1).
// Pin: ?bfmeSend1028@BfmeSink1028@@QAEXHPAH0@Z

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned now();
};

extern Rva007E9B70Obj *Rva007E9B70Get();

struct BfmeRecUVB
{
	char m_bfmePad[4];
	int m_bfmeKind;
	char m_bfmeText[4];
};

int bfmeGoUVB( BfmeRecUVB *r, char *out );

struct Rva00807BA0Ping;

int Rva008085A0( Rva00807BA0Ping *ping, const char *address,
	const char *text, int length );

struct Rva00803080Request
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class BfmeSvcVMO
{
public:
	void bfmeSetVMO( int n );
};

class BfmeSink1028
{
public:
	void bfmeSend1028( int a, int *b, int *c );

	void *m_00;
	void *m_04;
	Rva00807BA0Ping *m_08;
	Rva00803080Request *m_0C;
	int m_10;
};

void BfmeSink1028::bfmeSend1028( int a, int *b, int *c )
{
	int payload[2];
	char addr[0x14];
	int *pb;
	int *pc;
	int id;

	if( m_08 == 0 )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
			0x79 );
		return;
	}
	if( m_10 == 0x80 )
	{
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
			0x80 );
		return;
	}

	pb = b;
	pc = c;
	payload[1] = *pc;
	payload[0] = *pb;
	if( bfmeGoUVB( (BfmeRecUVB *)a, addr ) == 0 )
		goto done;

	id = Rva008085A0( m_08, addr, (const char *)payload, 8 );
	if( id < 0 )
		goto fail_ping;
	else
		goto success;

success:
	m_0C[m_10].m_00 = id;
	m_0C[m_10].m_04 = (int)Rva007E9B70Get()->now();
	m_0C[m_10].m_0C = *pc;
	m_0C[m_10].m_08 = *pb;
	( (BfmeSvcVMO *)this )->bfmeSetVMO( m_10 + 1 );
	return;

fail_ping:
	Rva007EB810Get()->fail(
		"false",
		"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
		0xA4 );
done:
	;
}
