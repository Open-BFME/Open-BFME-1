// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Rva0078FA30Base
{
public:
	Rva0078FA30Base( int value );
	virtual ~Rva0078FA30Base();

private:
	char m_unreconstructed[ 0x2F4 ];
};

class Rva0078FA30Product : public Rva0078FA30Base
{
public:
	Rva0078FA30Product( int value ) : Rva0078FA30Base( value ) {}
	virtual ~Rva0078FA30Product();
};

Rva0078FA30Product *__stdcall rva0078FA30Create( int value )
{
	return new Rva0078FA30Product( value );
}
