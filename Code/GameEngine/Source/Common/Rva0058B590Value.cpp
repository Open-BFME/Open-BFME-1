// cl: /O2 /Ob1

extern "C" __declspec(dllimport) double __cdecl floor( double );

extern float g_rva0058B590Scale;
extern float g_bfmeADL;

class Player
{
public:
	float getUpgradeCostChange() const;
	long  getRva0058B590Value( int value ) const;
};

__forceinline long rva0058B590FloatToLong( float value )
{
	volatile long result;
	__asm {
		fld value
		fistp result
	}
	return result;
}

struct Rva0058B590Data
{
	char m_pad00[ 0x70 ];
	int  m_value;
	char m_pad74[ 0x0C ];
	bool m_scaled;
};

class Rva0058B590Value
{
public:
	long get( Player *player ) const;

private:
	char                m_pad00[ 4 ];
	Rva0058B590Data    *m_data;
};

long Rva0058B590Value::get( Player *player ) const
{
	bool scaled = m_data->m_scaled;
	Player *valueOwner = player;
	if( scaled )
	{
		float value = valueOwner->getUpgradeCostChange() * g_rva0058B590Scale + g_bfmeADL;
		return rva0058B590FloatToLong( (float)floor( (double)value ) );
	}

	return valueOwner->getRva0058B590Value( m_data->m_value );
}
