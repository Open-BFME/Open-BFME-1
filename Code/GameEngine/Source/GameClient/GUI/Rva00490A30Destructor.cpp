// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: ~Rva00490A30 at 0x00490AC0 (316 B), the table owner of the
// Rva00490350 linked-object family (constructor landed in
// Rva00490350LinkedCtorAndWindowDtor.cpp). It sits on top of the window
// owner Rva00490470, clears eight of its eleven tables slot by slot (the
// per-slot clear is inlined eight times, one table set to -1) and then falls
// into the window owner's destructor through its ILT thunk (tail jump), so
// that destructor stays declared-only here.
class Rva00490350Base
{
public:
	virtual ~Rva00490350Base();
	virtual void slot1();
protected:
	void *m_link;
	int m_unused;
	int m_token;
};

class Rva00490470 : public Rva00490350Base
{
public:
	virtual ~Rva00490470();
};

class Rva00490A30 : public Rva00490470
{
public:
	virtual ~Rva00490A30();
private:
	void clearSlot( int i )
	{
		m_table0[i] = 0;
		m_table1[i] = 0;
		m_table2[i] = 0;
		m_table10[i] = -1;
		m_table3[i] = 0;
		m_table4[i] = 0;
		m_table5[i] = 0;
		m_table6[i] = 0;
	}
	int m_table0[8];
	int m_table1[8];
	int m_table2[8];
	int m_table3[8];
	int m_table4[8];
	int m_table5[8];
	int m_table6[8];
	int m_table7[8];
	int m_table8[8];
	int m_count130;
	int m_table9[8];
	int m_table10[8];
};

Rva00490A30::~Rva00490A30()
{
	for( int i = 0; i < 8; i++ )
		clearSlot( i );
}
