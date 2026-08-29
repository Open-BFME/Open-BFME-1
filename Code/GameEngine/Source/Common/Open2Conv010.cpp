// Three bodies from the 0x006xxxxx run.  Identity is not recovered; names are
// address-derived and the padding virtuals exist only to place the one slot
// each body calls.

// ---------------------------------------------------------------------------
// 0x0068AD80 -- forward one field of the first argument when the second
// argument matches what is already held.
//
// The two arguments are read at DIFFERENT times: the second before the
// register save (so at [esp+8] from an untouched frame) and the first after
// it, which is what makes the comparison chain run on argument two and the
// forwarded value come out of argument one.

class Open268AD80Key
{
public:
	int m_first;
	unsigned short m_second;
};

class Open268AD80Held
{
public:
	char m_pad[ 0xd ];
	unsigned char m_locked;
	char m_pad2[ 0x7a ];
	int m_first;
	unsigned short m_second;
};

// The payload sits at +0x22, an offset an int cannot take under default
// alignment; retail reads it there, so the record is packed.
#pragma pack(push, 1)
class Open268AD80Source
{
public:
	char m_pad[ 0x22 ];
	int m_payload;
};
#pragma pack(pop)

class Rva0068AD80
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94( int payload );

	void deliver( Open268AD80Source *source, const Open268AD80Key *key );

	char m_pad[ 0x39 ];
	unsigned char m_muted;
	char m_pad2[ 2 ];
	Open268AD80Held *m_held;
};

// @?deliver@Rva0068AD80@@QAEXPAVOpen268AD80Source@@PBVOpen268AD80Key@@@Z 0x0068AD80
void Rva0068AD80::deliver( Open268AD80Source *source, const Open268AD80Key *key )
{
	if( m_muted )
		return;

	Open268AD80Held *held = m_held;
	if( held == 0 )
		return;

	if( held->m_first != key->m_first )
		return;
	if( held->m_second != key->m_second )
		return;
	if( held->m_locked )
		return;

	slot94( source->m_payload );
}

// ---------------------------------------------------------------------------
// 0x006C0F40 -- map a normalised point into a rectangle.
//
// 0.0078125 is 1/128 and the other constant is 127.0, so the source point is
// in 0..127 with its Y axis inverted.  Both guards are null tests on the two
// pointers and the whole body is skipped together.
//
// Every integer argument is CAST to float in the source rather than left to
// the fused forms: retail emits `fild` then `faddp`/`fmulp`, where an
// uncast int gives `fiadd`/`fimul` and eight bytes fewer.  And the frame is
// cleaned by the callee (`ret 0x18`), so this is __stdcall.

class Open26C0F40Point
{
public:
	float m_x;
	float m_y;
};

class Open26C0F40Out
{
public:
	float m_x;
	float m_y;
};

// @?Rva006C0F40@@YGXPBVOpen26C0F40Point@@PAVOpen26C0F40Out@@HHHH@Z 0x006C0F40
void __stdcall Rva006C0F40( const Open26C0F40Point *point, Open26C0F40Out *out,
	int left, int top, int width, int height )
{
	if( point == 0 || out == 0 )
		return;

	float scaledWidth = (float)width;
	float scaledHeight = (float)height;
	float originX = (float)left;
	float originY = (float)top;

	out->m_x = scaledWidth * point->m_x * 0.0078125f + originX;
	out->m_y = ( 127.0f - point->m_y ) * scaledHeight * 0.0078125f + originY;
}
