// BFME U1SupplierHigh::fill at retail 0x005C8E90.
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

struct Gen_t_005c7940_p4pod
{
	U1Slot2Field *value;
};

struct Gen_t_005c6190_m4pod
{
	void *value;
};

class U1FillTargetHigh
{
};

class U1SupplierHigh
{
public:
	void fill( U1FillTargetHigh *output, void *context );

private:
	unsigned char m_padB8[ 0xb8 ];
	U1Slot2Field *m_fB8;
	U1Slot2Field *m_fBC;
	std::vector<Gen_t_005c7940_p4pod> m_suppliers;
};

void U1SupplierHigh::fill( U1FillTargetHigh *output, void *context )
{
	std::vector<Gen_t_005c6190_m4pod> values;
	values.reserve( m_suppliers.size() );
	for (std::vector<Gen_t_005c7940_p4pod>::iterator it = m_suppliers.begin();
		it != m_suppliers.end(); ++it)
	{
		Gen_t_005c6190_m4pod value;
		value.value = it->value->get( context );
		values.push_back( value );
	}
	reinterpret_cast<std::vector<Gen_t_005c6190_m4pod> *>( output )->swap( values );
}
