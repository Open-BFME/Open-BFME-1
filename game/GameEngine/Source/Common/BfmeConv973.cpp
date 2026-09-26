// Open-BFME5 conversions.

struct BfmeObjA973;

struct BfmeTabA973
{
	char m_bfmePad[8];
	void (__stdcall *m_bfmeFn)(BfmeObjA973 *o);
};

struct BfmeObjA973
{
	BfmeTabA973 *m_bfmeTab;
};

struct BfmeItemA973
{
	char m_bfmePad[8];
	BfmeObjA973 *m_bfmeObj;
	char m_bfmePad2[0x34];
	int m_bfme40;
};

struct BfmeHoldA973
{
	char m_bfmePad[0x14];
	BfmeItemA973 *m_bfmeItem;
};

class BfmeA973
{
public:
	void bfmeGo973A();

	BfmeHoldA973 *m_bfmeHold;
};

void BfmeA973::bfmeGo973A()
{
	BfmeHoldA973 *h = m_bfmeHold;
	BfmeItemA973 *it;

	if (h && (it = h->m_bfmeItem) != 0 && it->m_bfmeObj && !it->m_bfme40) {
		it->m_bfmeObj->m_bfmeTab->m_bfmeFn(it->m_bfmeObj);
		h->m_bfmeItem->m_bfmeObj = 0;
	}
}
