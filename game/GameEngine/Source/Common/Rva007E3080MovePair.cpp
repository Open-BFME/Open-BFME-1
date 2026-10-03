// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int classify( int value, int width );
};

class BfmeB996Range
{
public:
	char checkRange( int first, unsigned int *second, char *stop );
};

class BfmeB996
{
public:
	char movePair( int *output, int *first, unsigned int *second,
		unsigned int limit );

private:
	char m_pad[ 4 ];
	BfmeDev996 *m_dev;
};

char BfmeB996::movePair( int *output, int *first,
	unsigned int *second, unsigned int limit )
{
	char stop = 0;
	if ( !reinterpret_cast<BfmeB996Range *>(this)->checkRange(
			(int)first, second, &stop ) ||
		stop || *second > limit ) {
		return 0;
	}
	int firstValue = *first;
	int *destination = output;
	destination[ 0 ] = firstValue;
	destination[ 1 ] = *second;
	BfmeDev996 *dev = m_dev;
	return dev->classify( (int)( destination + 2 ), *second - 8 ) ==
		*second - 8;
}
