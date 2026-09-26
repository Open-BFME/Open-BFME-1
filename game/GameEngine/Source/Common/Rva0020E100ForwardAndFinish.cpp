class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *value, int kind);
};

class Rva0020E100Owner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void finish();

	void forwardAndFinish();

private:
	char m_pad04[0x20 - 0x04];
	void *m_value;
	int m_kind;
};

void Rva0020E100Owner::forwardAndFinish()
{
	BfmeSubFCB *helper = *reinterpret_cast<BfmeSubFCB **>(reinterpret_cast<char *>(this) - 8);
	helper->bfmeCallFCB(m_value, m_kind);
	finish();
}
