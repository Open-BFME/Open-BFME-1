// cl: /DNDEBUG /MD /EHsc

class Rva00537760
{
public:
	static int advance( int *value );
};

int Rva00537760::advance( int *value )
{
	++value[1];
	return --value[0];
}
