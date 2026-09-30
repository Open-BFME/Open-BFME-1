// Retail 0x00760660: opaque owner of the two 0x1C-byte channel records at +0xDC/+0xF8
// (helpers 0x0075CAA0, 0x0075CBE0, 0x0075CB60); one direct caller at 0x00765FB0.
// cl: /DNDEBUG /MD /EHsc

class Rva00760660Ref
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual int slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void *slot38();
};

class Rva00760660SlotB0
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0(void *, void *, int);
};

class BfmeHostESC
{
public:
	void bfmeCallESC(void *, int, unsigned char, int, int, int, int, unsigned char, int);
	void bfmeSendESC(void *, int);
	void bfmeDoneESC(int);
};

extern float minf(float, float);
extern float maxf(float, float);

class Rva00760660Owner
{
public:
	void update(Rva00760660Ref *, int, int, float, float, int, int, float);

private:
	char m_pad00[0x34];
	Rva00760660SlotB0 *m_slotB0;
	char m_pad38[0x74 - 0x38];
	float m_float74;
	float m_float78;
	float m_float7C;
	char m_pad80[0xdc - 0x80];
	Rva00760660Ref *m_refDC;
	void *m_valueE0;
	char m_padE4[0xf8 - 0xe4];
	Rva00760660Ref *m_refF8;
	char m_padFC[0x111 - 0xfc];
	unsigned char m_flag111;
};

// The pinned 0x0075CAA0 view takes the two float arguments as raw dwords.
void Rva00760660Owner::update(Rva00760660Ref *replacement, int flag,
	int firstPart, float secondPart, float value, int valuePart, int slotByte,
	float storedValue)
{
	m_float7C = storedValue;
	if (replacement == 0)
		return;

	bool same = true;
	void *replacementKey = replacement->slot38();
	if (m_refDC != 0 && replacementKey != m_refDC->slot38())
		same = false;
	if (m_refF8 != 0 && replacementKey != m_refF8->slot38())
		same = false;

	BfmeHostESC *host = (BfmeHostESC *)this;
	if (secondPart != 0.0f && same)
	{
		if (m_refDC == 0 && m_refF8 == 0)
		{
			host->bfmeCallESC((void *)0, (int)replacement, (unsigned char)flag,
				firstPart, *(int *)&secondPart, *(int *)&value, valuePart,
				(unsigned char)slotByte, 1);
			m_float78 = 1.0f;
			m_float74 = 0.0f;
		}
		else
		{
			if (m_refDC != 0 && m_refF8 != 0)
			{
				if (m_flag111)
				{
					host->bfmeCallESC((void *)2, (int)replacement, (unsigned char)flag,
						firstPart, *(int *)&secondPart, *(int *)&value, valuePart,
						(unsigned char)slotByte, 1);
					return;
				}
				if (m_float74 / m_float78 < 0.5f)
					host->bfmeSendESC(0, 1);
			}
			else if (m_refDC == 0)
			{
				host->bfmeSendESC(0, 1);
			}
			host->bfmeCallESC((void *)1, (int)replacement, (unsigned char)flag,
				firstPart, *(int *)&secondPart, *(int *)&value, valuePart,
				(unsigned char)slotByte, 1);
			m_float74 = m_float78 = secondPart > 0.0f
				? maxf(1.0f, minf(secondPart, (float)replacement->slot10() - 1.0f))
				: maxf(1.0f, minf(5.0f, (float)replacement->slot10() - 1.0f));
		}
	}
	else
	{
		host->bfmeCallESC((void *)0, (int)replacement, (unsigned char)flag,
			firstPart, *(int *)&secondPart, *(int *)&value, valuePart,
			(unsigned char)slotByte, 1);
		host->bfmeDoneESC(1);
		m_float78 = 1.0f;
		m_float74 = 0.0f;
	}

	if (m_slotB0 != 0)
		m_slotB0->slotB0(m_refDC, m_valueE0, 0);
}
