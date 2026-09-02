// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Gen0078D1C0
{
public:
	Gen0078D1C0();
};

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	virtual ~BfmeAptScreenBase();

protected:
	Gen0078D1C0 *m_memberPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D310Host : public BfmeAptScreenBase
{
public:
	Rva0078D310Host( void *context );
	virtual ~Rva0078D310Host();

private:
	Gen0078D1C0 m_member;
};

Rva0078D310Host::Rva0078D310Host( void *context )
	: BfmeAptScreenBase( context )
{
	m_memberPointer = &m_member;
}
