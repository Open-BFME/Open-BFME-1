// cl: /EHsc
// Complete destructor at retail 0x008D56E0.  The paired scalar deleting
// destructor is at 0x008D5780.  The body clears the derived field at +0x20,
// then performs the common Q4 teardown through vtables 0x01136058 and
// 0x01135D68.

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	void notify( int a, int b );
};

class Rva008D5780Root
{
public:
	virtual ~Rva008D5780Root() {}
};

class Rva008D5780Middle : public Rva008D5780Root
{
public:
	__forceinline virtual ~Rva008D5780Middle()
	{
		((Q4Base00D35D68 *)this)->notify( 0, 0 );
		m_flag = 0;
	}

private:
	char m_gap0[ 8 - 4 ];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[ 0x18 - 9 ];
	int m_flag;
	char m_gap2[ 0x20 - 0x1C ];
};

class Rva008D5780HeaderedDeleting : public Rva008D5780Middle
{
public:
	virtual ~Rva008D5780HeaderedDeleting();

private:
	int m_field;
};

Rva008D5780HeaderedDeleting::~Rva008D5780HeaderedDeleting()
{
	m_field = 0;
}
