// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

class Rva007AE610Array
{
public:
	void setValue( UnsignedInt index, UnsignedInt value );

private:
	unsigned char m_pad0[0x68];
	UnsignedInt m_values[1];
};

void Rva007AE610Array::setValue( UnsignedInt index, UnsignedInt value )
{
	m_values[index] = value;
}
