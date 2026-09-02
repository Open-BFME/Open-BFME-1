// cl: /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
friend class BfmeUnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class BfmeUnicodeString : private StringBase<unsigned short>
{
public:
	BfmeUnicodeString( const BfmeUnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~BfmeUnicodeString() {}
};

class BfmeThingME
{
public:
	int bfmeTestME();
};

void Rva0056C1C0Consume( void *context, BfmeUnicodeString value );

class Rva0056C1C0Owner : public BfmeThingME
{
public:
	char m_pad0[ 0x26c ];
	void *m_context;

	void submitUnicode();
};

void Rva0056C1C0Owner::submitUnicode()
{
	void *record = (void *)bfmeTestME();
	if ( record != 0 && m_context != 0 )
		Rva0056C1C0Consume( m_context,
			*(BfmeUnicodeString *)((char *)record + 0x28) );
}
