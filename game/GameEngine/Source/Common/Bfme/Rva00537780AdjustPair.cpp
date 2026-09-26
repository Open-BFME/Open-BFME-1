// cl: /DNDEBUG /MD /EHsc

class Rva00537780
{
public:
	static void adjust( int *value, int amount );
};

void Rva00537780::adjust( int *value, int amount )
{
	value[0] += amount;
	value[1] -= amount;
}
