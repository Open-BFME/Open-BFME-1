// Open-BFME5: two-argument callback forwarder reconstructed from retail
// RVA 0x0081D3E0.  The callback pointer is held at this+0x04.

typedef void (__cdecl *Rva0081D3E0Callback)( int first, int second );

class Rva0081D3E0Object
{
public:
	void forward( int first, int second );

	char m_padding[4];
	Rva0081D3E0Callback m_callback;
};

void Rva0081D3E0Object::forward( int first, int second )
{
	m_callback( first, second );
}
