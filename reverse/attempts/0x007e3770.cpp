// ?d_007e3770@@YAXXZ
// partial score=0.72 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

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

class BfmeB996
{
public:
	int Rva007E3770( int target, int *maximum );
	char bfmeTry996( int first, int second, char *stop );

private:
	char m_pad[ 4 ];
	BfmeDev996 *m_dev;
	int m_kind;
};

int BfmeB996::Rva007E3770( int target, int *maximum )
{
	int *max = maximum;
	int t = target;
	int count = 0;
	if ( m_kind != 6 )
		return 0;

	int initial = m_dev->available();
	if ( m_kind == 6 )
		m_dev->set996( 0, 0 );

	int second = 0;
	int first = 0;
	char stop = 0;

	for ( ;; ) {
		if ( m_kind != 6 )
			goto finish;
		if ( !bfmeTry996( (int)&first, (int)&second, &stop ) ) {
			if ( stop )
				return 0;
			goto finish;
		}
		if ( stop )
			return 0;

		m_dev->set996( -8, 1 );

		if ( t != 0 && first == t && *max < second )
			*max = second;
		if ( *max < second )
			*max = second;
		++count;

		if ( m_kind != 6 )
			goto finish;

		int second2;
		int first2;
		char stop2 = 0;
		if ( !bfmeTry996( (int)&first2, (int)&second2, &stop2 ) )
			continue;
		if ( stop2 )
			continue;

		m_dev->set996( -8, 1 );
		m_dev->set996( second2, 1 );
	}

finish:
	m_dev->set996( initial, 1 );
	return count;
}
