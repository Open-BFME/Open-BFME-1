class BfmeC994
{
public:
	void addString( const char *key, const char *value );
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int bfmeCallCIC(void *a, void *b, void *one, void *two);

void BfmeC994::addString( const char *key, const char *value )
{
	if (bfmeCallCIC(m_bfmeA, m_bfmeB, const_cast< char * >( key ), const_cast< char * >( value )) < 0)
		m_bfmeErr = -100;
}
