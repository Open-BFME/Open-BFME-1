// cl: /DNDEBUG /MD /EHsc

class Rva006092D0State
{
public:
	void setMode(int mode, int value);

	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(int); virtual void slot6C(int);

private:
	int m_mode;
};

// ?setMode@Rva006092D0State@@QAEXHH@Z
void Rva006092D0State::setMode(int mode, int value)
{
	if (mode == m_mode)
		return;

	m_mode = mode;
	switch (mode)
	{
	case 0:
		slot6C(value);
		break;
	case 1:
		slot68(value);
		break;
	case 3:
		slot6C(0);
		break;
	}
}
