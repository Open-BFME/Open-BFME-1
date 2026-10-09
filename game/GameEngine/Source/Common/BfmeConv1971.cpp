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

// Both calls below reach retail through an ILT jump entry, not through a
// separate thunk function, so the call is respelled to the matched body the
// jump lands on:
//
//   ILT 0x00035A5D -> 0x000B2370  ?isCurrentlyPlaying@AudioEventRTS@@QBE_NXZ
//   ILT 0x000294B5 -> 0x00417A70  ?tail@Gen_00417cb0@@QAEXPAX@Z
//
// Neither class has a project header (both are declared TU-locally in their own
// homes: Common/Audio/AudioEventRTS.cpp and Common/Bfme/Gen_00417cb0_tail.cpp),
// so they are restated here and the call sites are cast to them. The existing
// BfmeHostESH/BfmeItemESH/BfmeSubESH declarations above are kept untouched.

class AudioEventRTS
{
public:
	bool isCurrentlyPlaying() const;			///< retail 0x000B2370, via ILT 0x00035A5D
};

class Gen_00417cb0
{
public:
	void tail(void *param);						///< retail 0x00417A70, via ILT 0x000294B5
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
			((AudioEventRTS *)&first->m_bfmeSubESH)->isCurrentlyPlaying())
			return;
	}

	BfmeItemESH *second = m_bfme148ESH;

	if (second != 0)
	{
		BfmeDataESH *data = second->m_bfme18ESH;

		if (data == 0 || data->m_bfmeLenESH == 0 ||
			((AudioEventRTS *)&second->m_bfmeSubESH)->isCurrentlyPlaying())
			return;
	}

	((Gen_00417cb0 *)this)->tail(0);
}
