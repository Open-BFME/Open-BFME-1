// cl: /GX- /GS
// FESL browser lookup at retail 0x00802240 (44B).
//
// Identity is address-derived.  The matched Rva00802380Owner constructor at
// 0x00802330 installs vtable 0x0112C534, whose slot 4 is this body.  Its
// matched getters and destructor establish the owner fields used here:
// m_host at +4, the returned pointer array at +0x28, and the surrounding
// members at +8, +0x10/+0x14 and +0x24.  Only the lookup vector's observed
// host offset is modeled below; the preceding host bytes remain opaque.
//
// The six family callers of 0x007f76f0 load this same host into ECX, push the
// key, then form the vector address with LEA from that receiver.  The helper
// is therefore declared as a neutral host member with the ordinary thiscall ABI:
// host receiver, while its two explicit arguments are the vector and the
// const char key.  Its retail body returns an index and cleans 8 bytes.

struct Rva007F76F0Slot
{
	const char *m_text;
	int m_tag;
};

struct Rva007F76F0Vector
{
	Rva007F76F0Slot *m_begin;
	int m_count;
};

class Rva00802240Host
{
public:
	int rva007F76F0( Rva007F76F0Vector *vector, const char *key );

	char m_opaquePrefix[0x2b8];
	Rva007F76F0Vector m_bfmeVector;
};

class Rva00800630Owner
{
public:
	void *m_block;
	int m_field4;
	int m_field8;
};

class Rva00802380Owner
{
public:
	void *rva00802240( const char *key );

	void *m_bfmeVft;
	Rva00802240Host *m_host;
	int m_field8;
	char m_bfmePad0c[0xc];
	Rva00800630Owner m_member18;
	int m_field24;
	void **m_items;
};

void *Rva00802380Owner::rva00802240( const char *key )
{
	int index = m_host->rva007F76F0( &m_host->m_bfmeVector, key );

	if( index == -1 )
		return 0;

	return m_items[index];
}
