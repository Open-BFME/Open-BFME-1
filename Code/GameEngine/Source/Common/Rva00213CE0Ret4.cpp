// cl: /O2 /DNDEBUG /MD

// Retail 0x00213CE0 contains only ret 4. The owner and argument name remain
// unknown because the body consumes one stack dword without reading it.

class Rva00213CE0Owner
{
public:
	void ret4( int value );
};

void Rva00213CE0Owner::ret4( int value )
{
}
