// cl: /DNDEBUG /MD
//
// Retail 0x00414050: guarded virtual forwarder.

class BfmeVtableTarget414050
{
public:
	virtual void s00(void); virtual void s04(void); virtual void s08(void);
	virtual void s0C(void); virtual void s10(void); virtual void s14(void);
	virtual void s18(void); virtual void s1C(void); virtual void s20(void);
	virtual void s24(void); virtual void s28(void); virtual void s2C(void);
	virtual void s30(void); virtual void s34(void); virtual void s38(void);
	virtual void s3C(void); virtual void s40(void); virtual void s44(void);
	virtual void s48(void); virtual void s4C(void); virtual void s50(void);
	virtual void s54(void); virtual void s58(void); virtual void s5C(void);
	virtual void s60(void); virtual void s64(void);
	virtual void slot68(int arg);
};

struct BfmeForwardHolder414050
{
	BfmeVtableTarget414050 *m_first;
};

class BfmeGuardedForward414050
{
public:
	void forward(int arg);

	private:
	char m_pad[0x150];
	BfmeForwardHolder414050 *m_holder;
};

void BfmeGuardedForward414050::forward(int arg)
{
	if (arg == 0)
		return;
	BfmeForwardHolder414050 *holder = m_holder;
	if (holder->m_first != 0)
		holder->m_first->slot68(arg);
}
