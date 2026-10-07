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

// Retail calls the matched Rva007ECE60 (Y2Rva007EBAE0Module.cpp), which stores
// key/value as an escaped field into the (buffer, size) pair.
int Rva007ECE60(char *buffer, int size, const char *key, const char *value);

#define bfmeCallCIC( a, b, one, two ) \
	Rva007ECE60( static_cast< char * >( a ), reinterpret_cast< int >( b ), one, two )

void BfmeC994::addString( const char *key, const char *value )
{
	if (bfmeCallCIC(m_bfmeA, m_bfmeB, key, value) < 0)
		m_bfmeErr = -100;
}
