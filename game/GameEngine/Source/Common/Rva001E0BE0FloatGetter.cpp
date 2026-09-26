// ?get@Rva001E0BE0FloatGetter@@QBEMXZ
// cl: /O2 /GR- /EHsc- /MD /DNDEBUG

class Rva001E0BE0FloatGetter
{
public:
	float get( void ) const;

private:
	char m_padding[ 0x74 ];
	float m_value;
};

float Rva001E0BE0FloatGetter::get( void ) const
{
	return m_value;
}

class Rva001E0BF0FloatGetter
{
public:
	float get( void ) const;

private:
	char m_padding[ 0x78 ];
	float m_value;
};

// ?get@Rva001E0BF0FloatGetter@@QBEMXZ
float Rva001E0BF0FloatGetter::get( void ) const
{
	return m_value;
}
