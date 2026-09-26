struct Rva0020DEE0Outer
{
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(int mode);
};

struct Rva0020DEE0Inner
{
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(float value, int mode);

	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;

	void rva0020dee0Apply(int mode);
};

void Rva0020DEE0Inner::rva0020dee0Apply(int mode)
{
	switch (mode)
	{
	case 0:
		slot80(m_10 - m_08, 0);
		break;
	case 1:
		slot80(m_14 * m_10 - m_08, 0);
		break;
	case 2:
		slot80(m_18 * m_10 - m_08, 0);
		break;
	case 3:
		slot80(-m_08, 0);
		break;
	}
	((Rva0020DEE0Outer *)((char *)this - 0x10))->slot48(0);
}
