// cl: /O2 /Ob0
// stlport

#include <deque>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

void bfmeGo1071A( int index, char value );

struct Gen_t_005914e0_p12cd
{
	int a[ 3 ];
	Gen_t_005914e0_p12cd();
	Gen_t_005914e0_p12cd( const Gen_t_005914e0_p12cd &other );
	~Gen_t_005914e0_p12cd();
	Gen_t_005914e0_p12cd &operator=( const Gen_t_005914e0_p12cd &other );
};

bool operator==( const Gen_t_005914e0_p12cd &a, const Gen_t_005914e0_p12cd &b );
bool operator<( const Gen_t_005914e0_p12cd &a, const Gen_t_005914e0_p12cd &b );

template <> void _STL::deque<Gen_t_005914e0_p12cd>::clear();

class Rva00596AE0Member
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void release();
};

class Rva00596AE0Queue
{
public:
private:
	char m_storage[ 4 ];
};

class Rva00596AE0
{
public:
	void reset();

private:
	char m_pad00[ 0x10 ];
	Rva00596AE0Member *m_member;
	char m_pad18[ 4 ];
	char m_flags[ 6 ];
	char m_pad1e[ 2 ];
	Rva00596AE0Queue m_queue;
	char m_pad24[ 0x27 ];
	volatile char m_ready;
	char m_pad4c[ 0x41c ];
	volatile char m_active;
	char m_pad469[ 3 ];
	int m_value46c;
	int m_value470;
	int m_value474;
	volatile int m_value478;
};

// ?reset@Rva00596AE0@@QAEXXZ
void Rva00596AE0::reset()
{
	for ( int i = 0; i < 6; ++i )
	{
		bfmeGo1071A( i, 0 );
		m_flags[ i ] = 0;
	}

	if ( m_member != 0 )
		m_member->release();

	((_STL::deque<Gen_t_005914e0_p12cd> *)&m_queue)->clear();
	m_ready = 1;
	_ReadWriteBarrier();
	m_active = 0;
	m_value478 = 0;
	m_value46c = -2;
	m_value470 = -2;
	m_value474 = -2;
}
