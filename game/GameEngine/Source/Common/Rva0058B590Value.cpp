// cl: /O2 /Ob1

extern "C" __declspec(dllimport) double __cdecl floor( double );


extern const float g_rva0107533C;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	long  getRva0058B590Value( int value ) const;
};

// The original call uses ILT0x000225BB ->0x000C9C20, the existing seven-byte
// float getter at receiver+0x644. Use its owned address-derived call view,
// as UpgradeTemplate_calcCostToBuild.cpp does; Player's layout is not inferred.
class Rva000C9C20FloatField
{
public:
	float get() const;
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
		float value = ((const Rva000C9C20FloatField *)valueOwner)->get() * 100.0f + g_rva0107533C;
		return rva0058B590FloatToLong( (float)floor( (double)value ) );
	}

	return valueOwner->getRva0058B590Value( m_data->m_value );
}
