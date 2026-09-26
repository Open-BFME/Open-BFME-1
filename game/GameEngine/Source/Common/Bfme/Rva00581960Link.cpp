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
