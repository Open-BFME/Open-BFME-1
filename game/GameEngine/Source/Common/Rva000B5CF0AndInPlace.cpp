struct Rva000B5CF0AndInPlace
{
	static int *apply( int *value, int mask );
};

int *Rva000B5CF0AndInPlace::apply( int *value, int mask )
{
	*value &= mask;
	return value;
}
