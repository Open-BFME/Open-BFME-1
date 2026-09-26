// cl: /DNDEBUG /MD /EHsc

class Rva00410580
{
	unsigned char padding[0x110];
	unsigned flags;

public:
	bool has( unsigned mask ) const;
};

bool Rva00410580::has( unsigned mask ) const
{
	return ( flags & mask ) != 0;
}
