// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0020DD50FieldSetter
{
public:
	void set( int value );

private:
	unsigned char m_beforeField0C[ 0x0c ];
	int m_field0C;
	unsigned char m_betweenFields[ 4 ];
	int m_field14;
};

void Rva0020DD50FieldSetter::set( int value )
{
	m_field0C = value;
	m_field14 = 3;
}
