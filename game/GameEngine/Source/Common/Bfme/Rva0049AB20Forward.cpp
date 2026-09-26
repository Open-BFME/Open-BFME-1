// 25-byte forwarder with member and two arguments

class Callee0049AB20
{
public:
	void handle( void *param, int arg1, int arg2 );
};

class Rva0049AB20
{
public:
	void forward( int arg1, int arg2 );

	char            m_pad00[ 0x8 ];
	Callee0049AB20 *m_subObject;
	void           *m_param;
};

void Rva0049AB20::forward( int arg1, int arg2 )
{
	m_subObject->handle( m_param, arg1, arg2 );
}
