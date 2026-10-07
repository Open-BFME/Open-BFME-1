// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
	virtual void bfmeVX0996(); virtual void bfmeVX1996();
	virtual void bfmeVX2996(); virtual void bfmeVX3996();
	virtual void bfmeVX4996();
	virtual void bfmeSet996( int value, int enabled );
};

// ILT 0x00038163 -> 0x007E2EB0, the matched BfmeB996Range::checkRange
// (BfmeConv996RangeCheck.cpp), called on this object.
class BfmeB996Range
{
public:
	char checkRange( int first, unsigned int *second, char *stop );
};

class BfmeB996
{
public:
	void bfmeAdvance996();

private:
	char m_bfmePad[ 4 ];
	BfmeDev996 *m_bfmeDev;
	int m_bfmeKind;
};

void BfmeB996::bfmeAdvance996()
{
	if ( m_bfmeKind == 6 ) {
		int first;
		int second;
		int third;
		char stop = 0;
		if ( ( (BfmeB996Range *)this )->checkRange( (int)&third, (unsigned int *)&second, &stop ) && !stop ) {
			m_bfmeDev->bfmeSet996( -8, 1 );
			m_bfmeDev->bfmeSet996( second, 1 );
		}
	}
}
