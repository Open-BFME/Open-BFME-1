// cl: /DNDEBUG /MD /EHsc

class Rva00697D30
{
public:
	static int *decrement( int *value );
};

int *Rva00697D30::decrement( int *value )
{
	--*value;
	return value;
}
