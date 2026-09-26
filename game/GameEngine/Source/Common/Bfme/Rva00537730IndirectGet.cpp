// cl: /DNDEBUG /MD /EHsc

class Rva00537730
{
public:
	static void *get( void *value );
};

void *Rva00537730::get( void *value )
{
	return static_cast<void **>( value )[1];
}
