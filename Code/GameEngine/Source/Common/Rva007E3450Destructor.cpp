// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString( void );

private:
	int m_raw;
};

class Rva007E3450Resource
{
public:
	virtual void v0( void );
	virtual void v1( void );
	virtual void release( void );
};

class Rva007E3450 : public AsciiString
{
public:
	~Rva007E3450( void );

private:
	Rva007E3450Resource *m_resource;
};

Rva007E3450::~Rva007E3450( void )
{
	if ( m_resource != 0 ) {
		m_resource->release();
		m_resource = 0;
	}
}
