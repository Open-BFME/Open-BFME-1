class BfmeSlotGD
{
public:
	void *m_bfmePtrGD;
	unsigned char m_bfmeRestGD[12];
};

// ILT 0x82A6 -> 0x006BBD80, matched protected
// ?translateEvent@Win32Mouse@@IAEXIPAUMouseIO@@@Z (Win32Mouse_translateEvent.cpp).
struct MouseIO;
class Win32Mouse
{
	friend class BfmeRingGD;
protected:
	void translateEvent(unsigned int eventIndex, MouseIO *result);
};

class BfmeRingGD
{
public:
	char bfmePushGD(void *p, int unused);

	unsigned char m_bfmeHeadGD2[0x4e14];
	BfmeSlotGD m_bfmeSlotsGD[256];
	unsigned char m_bfmeGapGD[4];
	int m_bfmeHeadGD;
};

char BfmeRingGD::bfmePushGD(void *p, int unused)
{
	int i = m_bfmeHeadGD;

	if (m_bfmeSlotsGD[i].m_bfmePtrGD == 0)
		return 0;

	reinterpret_cast<Win32Mouse *>(this)->translateEvent(i, (MouseIO *)p);

	m_bfmeSlotsGD[m_bfmeHeadGD].m_bfmePtrGD = 0;

	++m_bfmeHeadGD;

	if ((unsigned int)m_bfmeHeadGD >= 0x100)
		m_bfmeHeadGD = 0;

	return 1;
}
