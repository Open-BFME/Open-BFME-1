// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Address-derived scan over the BfmeB996 range records at retail 0x007E3770.
// Retail inlines the kind-6 rewind (0x007E3410) and advance step (0x007E3230).

class BfmeDev996
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void set996( int value, int enabled );
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual int available();
};

extern void j_00038163();

class BfmeB996
{
public:
	int Rva007E3770( int target, int *maximum );
	typedef char (BfmeB996::*BfmeTry996Fn)( int, int, char * );
	union BfmeTry996Target
	{
		void (*asFunction)();
		BfmeTry996Fn asMember;
	};

	bool bfmeIsMode6()
	{
		if ( m_kind == 6 )
			return true;
		return false;
	}

	void invokeForMode()
	{
		if ( m_kind == 6 )
			m_dev->set996( 0, 0 );
	}

private:
	char m_pad[ 4 ];
	BfmeDev996 *m_dev;
	int m_kind;
};

int BfmeB996::Rva007E3770( int target, int *maximum )
{
	if ( m_kind == 6 ) {
		int count = 0;
		int initial = m_dev->available();
		int first = 0;
		unsigned int second = 0;
		char stop = 0;
		BfmeTry996Target try996;
		try996.asFunction = j_00038163;
		invokeForMode();

		while ( bfmeIsMode6() ) {
			if ( !(this->*try996.asMember)( (int)&first, (int)&second, &stop ) ) {
				if ( stop )
					goto fail;
				break;
			}
			if ( stop )
				goto fail;
			m_dev->set996( -8, 1 );
			if ( target == 0 ) {
				++count;
			} else if ( first == target ) {
				if ( *maximum < second )
					*maximum = second;
				++count;
			}
			if ( *maximum < second )
				*maximum = second;
			if ( m_kind == 6 ) {
				int probe2;
				unsigned int arg2;
				char flag2 = 0;
				BfmeB996::BfmeTry996Target try996;
				try996.asFunction = j_00038163;
				if ( (this->*try996.asMember)( (int)&probe2, (int)&arg2, &flag2 ) && !flag2 ) {
					m_dev->set996( -8, 1 );
					m_dev->set996( arg2, 1 );
				}
			}
		}
		m_dev->set996( initial, 1 );
		return count;
	} else {
fail:
		return 0;
	}
}
