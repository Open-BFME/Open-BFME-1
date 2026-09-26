// cl: /DNDEBUG /MD /EHsc

class Rva00537A90
{
	unsigned char padding[0x188];
	int state;

public:
	void update( int ignored );
};

void Rva00537A90::update( int ignored )
{
	if( state == 2 )
		state = 9;
}
