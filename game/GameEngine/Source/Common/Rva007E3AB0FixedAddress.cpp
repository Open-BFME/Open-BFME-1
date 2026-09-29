// Address-derived reconstruction of the six-byte fixed-address getter at 0x007E3AB0.

extern char g_0112CBD8[];

void *Rva007E3AB0FixedAddress()
{
	return reinterpret_cast<void *>( g_0112CBD8 );
}
