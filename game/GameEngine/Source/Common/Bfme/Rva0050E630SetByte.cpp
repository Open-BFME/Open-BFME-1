// cl: /DNDEBUG /MD /EHsc

class Rva0050E630
{
	unsigned char padding[0x260];
	unsigned char value;

public:
	void reset( int ignored );
};

void Rva0050E630::reset( int ignored )
{
	value = 1;
}
