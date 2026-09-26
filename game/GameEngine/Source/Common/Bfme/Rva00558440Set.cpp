// cl: /DNDEBUG /MD /EHsc

class Rva00558440
{
	unsigned char padding[0x55];
	unsigned char state;

public:
	void set( unsigned value );
};

void Rva00558440::set( unsigned value )
{
	(void)value;
	state = 1;
}
