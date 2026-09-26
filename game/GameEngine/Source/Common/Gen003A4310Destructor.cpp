// cl: /DNDEBUG /MD /EHsc
//
// ~Gen003A4310, retail 0x003A4310, 102 bytes. Element destructor for the
// element-size-0x14 STLport vector<T> family in Q4VectorDtorPlain.cpp
// (pin ??1Gen003A4310@@QAE@XZ). Identity is not recovered; the element is
// two BFMERetailAsciiString-shaped fields at +0x08/+0x0c inside a 0x14-byte
// element. The body explicitly releases both fields' buffers first (two
// calls, forward field order) and then falls into the compiler's own
// implicit member destruction (two more calls, reverse field order) --
// that is the only source shape that reproduces four releaseBuffer calls
// against only two field addresses.

class BFMERetailAsciiString
{
public:
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	__forceinline void reset()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

class Gen003A4310
{
public:
	~Gen003A4310();

private:
	unsigned char m_pad00[8];
	BFMERetailAsciiString m_fieldA;
	BFMERetailAsciiString m_fieldB;
	unsigned char m_tail[4];
};

Gen003A4310::~Gen003A4310()
{
	m_fieldA.reset();
	m_fieldB.reset();
}
