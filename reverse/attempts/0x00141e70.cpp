// ?bfmeInitialise@Gen00141E70@@QAEPAV1@XZ
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Initializes two contiguous 0x60-byte tables and then completes setup.

#include <string.h>

class Gen00141E70
{
public:
	Gen00141E70 *bfmeInitialise();
	void bfmeCompleteInitialise();

private:
	char m_bfmePad00[4];
	int m_bfme04;
	char m_bfmePad08[0x20];
	int m_bfmeFirst[0x18];
	int m_bfmeSecond[0x18];
};

Gen00141E70 *Gen00141E70::bfmeInitialise()
{
	m_bfme04 = 0;
	int *first = m_bfmeFirst;
	memset(first, 0, sizeof(m_bfmeFirst));
	int *second = m_bfmeSecond;
	memset(second, 0, sizeof(m_bfmeSecond));
	bfmeCompleteInitialise();
	return this;
}
