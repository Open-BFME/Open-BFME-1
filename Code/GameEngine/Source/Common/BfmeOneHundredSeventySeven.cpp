// A part asking the whole it sits in to get on with something.

struct BfmeOwnerBX
{
	unsigned char m_bfmeHead[0x254];	// 0x000
	unsigned char m_bfmeReady;		// 0x254
};

class BfmeSubBX
{
public:
	void bfmeGoBX(void);

	unsigned char m_bfmeHead[4];		// 0x0
};


class BfmeHostBX
{
public:
	virtual void bfmeSpare000BX(void) = 0;
	virtual void bfmeSpare001BX(void) = 0;
	virtual void bfmeSpare002BX(void) = 0;
	virtual void bfmeSpare003BX(void) = 0;
	virtual void bfmeSpare004BX(void) = 0;
	virtual void bfmeSpare005BX(void) = 0;
	virtual void bfmeSpare006BX(void) = 0;
	virtual void bfmeSpare007BX(void) = 0;
	virtual void bfmeSpare008BX(void) = 0;
	virtual void bfmeSpare009BX(void) = 0;
	virtual void bfmeSpare010BX(void) = 0;
	virtual void bfmeSpare011BX(void) = 0;
	virtual void bfmeSpare012BX(void) = 0;
	virtual void bfmeSpare013BX(void) = 0;
	virtual void bfmeSpare014BX(void) = 0;
	virtual void bfmeDoBX(void) = 0;

	BfmeOwnerBX *m_bfmeOwner;		// 0x004
	unsigned char m_bfmeGap[0xe0];		// 0x008
	BfmeSubBX m_bfmeSub;			// 0x0e8
};

void BfmeSubBX::bfmeGoBX(void)
{
	if (((const BfmeHostBX *)((const char *)this - 0xe8))->m_bfmeOwner->m_bfmeReady == 0)
		return;

	((BfmeHostBX *)((char *)this - 0xe8))->bfmeDoBX();
}
