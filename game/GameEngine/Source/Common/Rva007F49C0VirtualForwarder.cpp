// Address-derived reconstruction of the 15-byte virtual forwarding wrapper at 0x007F49C0.

class Rva007F49C0VirtualForwarder
{
public:
	virtual void reserved0();
	virtual void reserved1();
	virtual void reserved2();
	virtual void reserved3();
	virtual void invoke( void *value, int mode );

	void invokeDefault( void *value );
};

void Rva007F49C0VirtualForwarder::invokeDefault( void *value )
{
	invoke( value, 0 );
}
