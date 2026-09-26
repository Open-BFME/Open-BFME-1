// Three more tiny ones: a search for the first empty slot of two, an
// all-clear test over a word and a short, and a constructor that stores its
// vftable and one field.

class Gen_00581920
{
public:
	int bfmeFirstEmpty(void) const;

private:
	int m_bfmeSlots[2];					// +0x00
};

// ?bfmeFirstEmpty@Gen_00581920@@QBEHXZ
int Gen_00581920::bfmeFirstEmpty(void) const
{
	for (int index = 0; index < 2; ++index)
	{
		if (m_bfmeSlots[index] == 0)
			return index;
	}

	return 2;
}

class Gen_00662720
{
public:
	int bfmeIsClear(void) const;

private:
	int m_bfmeCount;					// +0x00
	short m_bfmeFlags;					// +0x04
};

// ?bfmeIsClear@Gen_00662720@@QBEHXZ
int Gen_00662720::bfmeIsClear(void) const
{
	if (m_bfmeCount == 0 && m_bfmeFlags == 0)
		return 1;

	return 0;
}

class Gen_00749740
{
public:
	Gen_00749740(int value);

	virtual ~Gen_00749740(void);				// slot +0x00

private:
	int m_bfmeValue;					// +0x04
};

// ??0Gen_00749740@@QAE@H@Z
Gen_00749740::Gen_00749740(int value)
{
	m_bfmeValue = value;
}
