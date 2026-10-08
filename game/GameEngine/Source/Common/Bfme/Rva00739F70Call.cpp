// 13-byte forwarder passing address of member at 0x1C to sub-object at 0x44

// Retail calls the ILT at 0x0003A7E7, which jumps to 0x00739E70: the matched
// Rva00739C70::update(int) row in Rva00739C70Cleanup.cpp. Its result is unused.
class TextureBaseClass;

class Rva00739C70
{
public:
	TextureBaseClass *update( int arg );
};

typedef Rva00739C70 SubObject00739E70;

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
	m_subObject->update( (int)&m_member1C );
}
