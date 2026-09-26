// cl: /DNDEBUG /MD /EHsc

class Rva00538070
{
	unsigned char padding[8];
	unsigned flags;

public:
	void add( unsigned mask );
};

void Rva00538070::add( unsigned mask )
{
	flags |= mask;
}
