// cl: /O2 /DNDEBUG /MD

// Retail 0x00171240 contains only ret 4. The owner and argument name remain
// unknown because the body consumes one stack dword without reading it.

class Rva00171240Owner
{
public:
	void ret4( int value );
};

void Rva00171240Owner::ret4( int value )
{
}
