// BFME address-derived supplier fill at retail 0x005C8D40.
// Matched U1Collect_005CBBA0/005CC2E0 callers prove the field run and
// thiscall two-argument ABI. Their legacy supplier labels do not identify an
// original semantic owner, so this reconstruction retains the target RVA.
// Retail calls reserve0x5C7870 and overflow0x5C6040; the donor uses distinct
// helpers0x5C7940/0x5C6190. Each element here is one pointer (four bytes).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class U1Slot2Field
{
public:
	virtual ~U1Slot2Field();
	virtual void unused();
	virtual void *get( void *first ) = 0;
};

struct Gen_t_005c7870_p4pod
{
	int a[ 1 ];
};

struct Gen_t_005c72e0_m4pod
{
	void *value;
};

class Rva005C8D40Output;

class Rva005C8D40
{
public:
	void fill( Rva005C8D40Output *output, void *context );

private:
	unsigned char m_pad3C[ 0x3c ];
	U1Slot2Field *m_f3C;
	U1Slot2Field *m_f40;
	U1Slot2Field *m_f44;
	U1Slot2Field *m_f48;
	unsigned char m_pad4C[ 8 ];
	U1Slot2Field *m_f54;
	std::vector<U1Slot2Field *> m_suppliers;
};

void Rva005C8D40::fill( Rva005C8D40Output *output, void *context )
{
	std::vector<Gen_t_005c72e0_m4pod> values;
	reinterpret_cast<std::vector<Gen_t_005c7870_p4pod> *>( &values )->reserve( m_suppliers.size() );
	std::vector<U1Slot2Field *>::iterator end = m_suppliers.end();
	for (std::vector<U1Slot2Field *>::iterator it = m_suppliers.begin();
		it != end; ++it)
	{
		Gen_t_005c72e0_m4pod value;
		value.value = (*it)->get( context );
		values.push_back( value );
	}
	reinterpret_cast<std::vector<Gen_t_005c72e0_m4pod> *>( output )->swap( values );
}
