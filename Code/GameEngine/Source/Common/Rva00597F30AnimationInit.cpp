// cl: /O2 /Ob0
#pragma optimize("a", on)

extern "C" void *memset( void *destination, int value, unsigned int count );

void *bfmeMakeASB( int first, int second );
extern void j_00031426();

struct Rva00597F30Item
{
	int first;
	int unused;
	void *made;
	float width;
	int x;
	unsigned char y;
};

void bfmeFillPart( Rva00597F30Item *, Rva00597F30Item *,
	const Rva00597F30Item * );

typedef void (__cdecl *Rva00597F30FillCall)( Rva00597F30Item *,
	Rva00597F30Item *, const Rva00597F30Item * );

class Rva00597F30
{
public:
	void init();

private:
	int m_zero;
	int m_zero2;
	unsigned char m_flags[ 0x14 ];
	Rva00597F30Item m_items[ 12 ];
};

// ?init@Rva00597F30@@QAEXXZ
void Rva00597F30::init()
{
	unsigned char *first = m_flags;
	Rva00597F30Item *begin = m_items;
	int zero = 0;
	Rva00597F30Item item;
	if ( first != (unsigned char *)begin )
		memset( first, 1, (unsigned char *)begin - first );

	item.first = zero;
	item.made = bfmeMakeASB( zero, zero );
	item.width = 1.0f;
	item.x = zero;
	item.y = zero;
	Rva00597F30FillCall fill = (Rva00597F30FillCall)j_00031426;
	fill( begin, m_items + 12, &item );

	m_zero = zero;
	m_zero2 = zero;
}
