// cl: /DNDEBUG /MD /EHsc
//
// Rva00350EF0::run, retail 0x00350EF0, 66 bytes.
//
// d_002ed640: two-byte true/true local into arg vslot+0x28; then shuttle
// this+0x14 through arg vslot+0x8C and write it back.

class Gen00350EF0Arg
{
public:
	virtual void vslot00();
	virtual void vslot01();
	virtual void vslot02();
	virtual void vslot03();
	virtual void vslot04();
	virtual void vslot05();
	virtual void vslot06();
	virtual void vslot07();
	virtual void vslot08();
	virtual void vslot09();
	virtual void vslot0a( void * local );	// +0x28
	virtual void vslot0b();
	virtual void vslot0c();
	virtual void vslot0d();
	virtual void vslot0e();
	virtual void vslot0f();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual void vslot14();
	virtual void vslot15();
	virtual void vslot16();
	virtual void vslot17();
	virtual void vslot18();
	virtual void vslot19();
	virtual void vslot1a();
	virtual void vslot1b();
	virtual void vslot1c();
	virtual void vslot1d();
	virtual void vslot1e();
	virtual void vslot1f();
	virtual void vslot20();
	virtual void vslot21();
	virtual void vslot22();
	virtual void vslot23( void * byteOut );	// +0x8C
};

class Rva00350EF0
{
public:
	void run( Gen00350EF0Arg * arg );

private:
	char m_pad00[ 0x14 ];
	char m_at14;
};

// ?run@Rva00350EF0@@QAEXPAVGen00350EF0Arg@@@Z
void Rva00350EF0::run( Gen00350EF0Arg * arg )
{
	char local[ 2 ];
	local[ 0 ] = 1;
	local[ 1 ] = 1;
	arg->vslot0a( local );
	char tmp = m_at14;
	arg->vslot23( &tmp );
	m_at14 = tmp;
}
