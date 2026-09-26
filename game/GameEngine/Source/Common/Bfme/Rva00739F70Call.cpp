// 13-byte forwarder passing address of member at 0x1C to sub-object at 0x44

class SubObject00739E70
{
public:
	void method( void *member1c );
};

class Rva00739F70
{
public:
	void call();

	char                m_pad00[ 0x1C ];
	int                 m_member1C;
	char                m_pad20[ 0x24 ];
	SubObject00739E70 * m_subObject;
};

void Rva00739F70::call()
{
	m_subObject->method( &m_member1C );
}
