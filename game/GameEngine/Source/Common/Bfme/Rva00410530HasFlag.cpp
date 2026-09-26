// cl: /DNDEBUG /MD /EHsc

class Rva00410530
{
	unsigned char padding[0x11c];
	unsigned flags;

public:
	bool has( unsigned mask ) const;
};

bool Rva00410530::has( unsigned mask ) const
{
	return ( flags & mask ) != 0;
}
