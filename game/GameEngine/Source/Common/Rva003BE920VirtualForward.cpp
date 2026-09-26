// Open-BFME5: two-argument callback forwarder reconstructed from retail
// RVA 0x003BE920.  The callback pointer is held at this+0x08.

typedef void (__cdecl *Rva003BE920Callback)( int first, int second );

class Rva003BE920Object
{
public:
	void forward( int first, int second );

	char m_padding[8];
	Rva003BE920Callback m_callback;
};

void Rva003BE920Object::forward( int first, int second )
{
	m_callback( first, second );
}
