// ?movePair@BfmeB996Move@@QAEDPAH0PAII@Z
// partial score=0.84 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996Move
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual int classify( int value, int width );
};

class BfmeB996Move
{
public:
	char movePair( int *output, int *first, unsigned int *second, unsigned int limit );
	char bfmeTry996( int first, int second, char *stop );
private:
	char m_pad[ 4 ];
	BfmeDev996Move *m_dev;
};

char BfmeB996Move::movePair( int *output, int *first, unsigned int *second, unsigned int limit )
{
	int *destination = output;
	char stop = 0;
	if ( !bfmeTry996( (int)first, (int)second, &stop ) || stop || *second > limit ) {
		return 0;
	}
	int firstValue = *first;
	destination[ 0 ] = firstValue;
	destination[ 1 ] = *second;
	unsigned int base = *second - 8;
	return m_dev->classify( (int)(destination + 2), base ) == *second - 8;
}
