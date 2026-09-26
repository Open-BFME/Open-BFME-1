class BfmeHelper71BA0
{
public:
	int bfmeCall71BA0();
};

class Rva00971BA0Owner
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
	virtual bool ready();
	virtual void prepare();

	int guardedHelper();

private:
	char m_pad04[0x14 - 0x04];
	BfmeHelper71BA0 *m_helper;
};

int Rva00971BA0Owner::guardedHelper()
{
	if (!ready())
		prepare();

	if (!m_helper)
		return false;

	return m_helper->bfmeCall71BA0();
}
