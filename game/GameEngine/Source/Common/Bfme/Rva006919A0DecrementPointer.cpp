// cl: /DNDEBUG /MD /EHsc

class Rva006919A0
{
public:
	static int *decrement( int *value );
};

int *Rva006919A0::decrement( int *value )
{
	--*value;
	return value;
}
