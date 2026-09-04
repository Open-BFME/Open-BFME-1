// cl: /DNDEBUG /MD /EHsc
//
// Rva003BA500 ctor, retail 0x003BA9C0, 102 bytes.
// Same vtable 0x010ED46C as ??1Rva003BA500. Zeros scalars, builds the
// +0x0C range member, then range-assigns start/finish (ILT 0x00024C17).

class Rva003BA9C0Str
{
public:
	Rva003BA9C0Str()
	{
		m_buf = 0;
	}
	~Rva003BA9C0Str();

	char *m_buf;
};

class Rva003BA9C0Range
{
public:
	Rva003BA9C0Range()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}
	~Rva003BA9C0Range();
	void assign( void *first, void *last );

	void *volatile m_start;
	void *volatile m_finish;
	void *m_end;
};

class Rva003BA500
{
public:
	__declspec( noinline ) Rva003BA500();
	virtual void handle();

private:
	Rva003BA9C0Str m_at04;
	int m_at08;
	Rva003BA9C0Range m_at0C;
	bool m_at18;
	char m_pad19[ 3 ];
	Rva003BA9C0Str m_at1C;
	int m_at20;
};

// ??0Rva003BA500@@QAE@XZ
Rva003BA500::Rva003BA500()
	: m_at08( 0 ), m_at18( false ), m_at20( 0 )
{
	Rva003BA9C0Range *p = &m_at0C;
	void *last = p->m_finish;
	void *first = p->m_start;
	p->assign( first, last );
}
