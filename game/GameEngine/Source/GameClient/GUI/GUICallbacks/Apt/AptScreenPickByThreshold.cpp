// cl: /DNDEBUG /MD
//
// Retail 0x0055BDD0: thiscall, stdcall-arg.  Compare the argument against
// two virtual thresholds on the singleton at 0x012F70E4 and return one of
// three pointers at this+0x274 / +0x278 / +0x27c.

class BfmeThresholdSource
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual int getLow();
	virtual int getHigh();
};

extern BfmeThresholdSource *g_obj12F70E4;

class BfmeAptScreenPickByThreshold
{
public:
	void *pick( int value );

private:
	unsigned char m_unmodelled[ 0x274 ];
	void *m_low;
	void *m_mid;
	void *m_high;
};

// ?pick@BfmeAptScreenPickByThreshold@@QAEPAXH@Z
void *BfmeAptScreenPickByThreshold::pick( int value )
{
	if( !g_obj12F70E4 )
		return 0;
	if( value < g_obj12F70E4->getLow() )
		return m_low;
	if( value < g_obj12F70E4->getHigh() )
		return m_mid;
	return m_high;
}
