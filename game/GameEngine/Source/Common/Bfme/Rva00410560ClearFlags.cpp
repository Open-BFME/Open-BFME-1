// cl: /DNDEBUG /MD /EHsc

class Rva00410560
{
	unsigned char padding[0x110];
	unsigned flags;

public:
	void clear( unsigned mask );
};

void Rva00410560::clear( unsigned mask )
{
	flags &= ~mask;
}
