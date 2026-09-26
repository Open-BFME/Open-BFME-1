// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996Range
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual int classify( int value, int width );
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual int cursor();
};

class BfmeB996Range
{
public:
	char checkRange( int first, unsigned int *second, char *stop );
private:
	char m_pad[ 4 ];
	BfmeDev996Range *m_dev;
	int m_kind;
	int m_limit;
};

char BfmeB996Range::checkRange( int first, unsigned int *second, char *stop )
{
	int firstClass = m_dev->classify( first, 4 );
	*stop = 0;
	if ( firstClass != 4 ) {
		if ( firstClass != 0 ) {
			*stop = 1;
		}
		return 0;
	}

	int secondClass = m_dev->classify( (int)second, 4 );
	unsigned int remaining = m_limit - m_dev->cursor();
	if ( secondClass == 4 && *second >= 8 && *second - 8 <= remaining ) {
		return 1;
	}
	*stop = 1;
	return 0;
}
