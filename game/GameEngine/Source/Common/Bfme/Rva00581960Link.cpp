// cl: /DNDEBUG /MD /EHsc

class Rva00581960
{
	unsigned char *target;
	unsigned char *value;

public:
	void set( unsigned ignored );
};

void Rva00581960::set( unsigned ignored )
{
	(void)ignored;
	*reinterpret_cast<unsigned char **>( target + 0x40 ) = value;
}
// Retail 0x00581970 (34 B): EAX-indexed 0/2/3 -> 0/1/2 else 3 mapper beside
// the 0x00581960 link TU. Msg arrives in EAX; switch compiles to the retail
// sub/dec/je ladder with two mov-eax tails. No callers, refs=0, no ILT.
// ?map00581970@@YAHH@Z
static int map00581970(int value)
{
	switch (value)
	{
	case 0:
		return 0;
	case 2:
		return 1;
	case 3:
		return 2;
	}
	return 3;
}

// absent-from-retail: TU-local caller keeping the static alive with the
// same private register convention its unknown caller gives it.
int Rva00581970Caller(int value)
{
	return map00581970(value);
}

