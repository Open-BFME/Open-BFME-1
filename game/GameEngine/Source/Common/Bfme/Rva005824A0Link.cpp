// cl: /DNDEBUG /MD /EHsc

class Rva005824A0
{
	unsigned char padding[8];
	unsigned char *target;
	unsigned char *value;

public:
	void set( unsigned ignored );
};

void Rva005824A0::set( unsigned ignored )
{
	(void)ignored;
	*reinterpret_cast<unsigned char **>( target + 0x40 ) = value;
}
