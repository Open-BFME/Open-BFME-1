// ?reset@Rva0058EFF0Owner@@QAEXXZ
// partial score=0.56 date=2026-09-02
// cl: /O2 /Ob0

void __cdecl bfmeFree58EFF0( void *block );

class Rva0058EFF0Owner
{
public:
	void reset();

private:
	char  m_pad00[ 0x460 ];
	int   m_head0;
	int   m_head1;
	bool  m_flag;
	char  m_pad469[ 3 ];
	int   m_index0;
	int   m_index1;
	int   m_index2;
	int   m_value;
	int   m_tail;
	void *m_optional;
	void *m_second;
	char  m_pad488[ 0x44 ];
	void *m_first;
};

void Rva0058EFF0Owner::reset()
{
	bfmeFree58EFF0( m_first );

	int zero = 0;
	m_first = 0;
	m_flag = false;
	int invalid = -2;
	m_index0 = invalid;
	m_index1 = invalid;
	m_index2 = invalid;
	m_value = zero;

	if( m_optional )
		bfmeFree58EFF0( m_optional );
	m_optional = 0;

	bfmeFree58EFF0( m_second );
	m_second = 0;
	m_head0 = 0;
	m_head1 = 0;
	m_tail = 0;
}
