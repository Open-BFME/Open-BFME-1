class BfmeDataESH
{
public:
	unsigned char m_bfmeHeadESH[4];
	unsigned short m_bfmeLenESH;
};

class BfmeSubESH
{
public:
	char bfmeBusyESH();
};

class BfmeItemESH
{
public:
	unsigned char m_bfmeHeadESH[4];
	BfmeSubESH m_bfmeSubESH;
	unsigned char m_bfmePadESH[0x13];
	BfmeDataESH *m_bfme18ESH;
};

class BfmeHostESH
{
public:
	void bfmeTickESH();
	void bfmeFireESH(int mode);

	unsigned char m_bfmeHeadESH[0x140];
	char m_bfme140ESH;
	char m_bfme141ESH;
	unsigned char m_bfmeGapESH[2];
	BfmeItemESH *m_bfme144ESH;
	BfmeItemESH *m_bfme148ESH;
};

void BfmeHostESH::bfmeTickESH()
{
	if (m_bfme140ESH == 0 || m_bfme141ESH == 0)
		return;

	BfmeItemESH *first = m_bfme144ESH;

	if (first != 0)
	{
		BfmeDataESH *data = first->m_bfme18ESH;

		if (data == 0 || data->m_bfmeLenESH == 0 ||
			first->m_bfmeSubESH.bfmeBusyESH() != 0)
			return;
	}

	BfmeItemESH *second = m_bfme148ESH;

	if (second != 0)
	{
		BfmeDataESH *data = second->m_bfme18ESH;

		if (data == 0 || data->m_bfmeLenESH == 0 ||
			second->m_bfmeSubESH.bfmeBusyESH() != 0)
			return;
	}

	bfmeFireESH(0);
}
