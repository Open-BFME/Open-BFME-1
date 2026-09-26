class BfmeAgentBG
{
public:
	virtual void bfmeSlot00BG();
	virtual void bfmeSlot01BG();
	virtual void bfmeSlot02BG();
	virtual void bfmeSlot03BG();
	virtual void bfmeSlot04BG();
	virtual void bfmeSlot05BG();
	virtual void bfmeSlot06BG();
	virtual void bfmeSlot07BG();
	virtual void bfmeSlot08BG();
	virtual void bfmeBlockBG(void *dst, int size);
	virtual void bfmeSlot10BG();
	virtual void bfmeSlot11BG();
	virtual void bfmeSlot12BG();
	virtual void bfmeSlot13BG();
	virtual void bfmeSlot14BG();
	virtual void bfmeSlot15BG();
	virtual void bfmeSlot16BG();
	virtual void bfmeSlot17BG();
	virtual void bfmeSlot18BG();
	virtual void bfmeSlot19BG();
	virtual void bfmeSlot20BG();
	virtual void bfmeSlot21BG();
	virtual void bfmeSlot22BG();
	virtual void bfmeSlot23BG();
	virtual void bfmeSlot24BG();
	virtual void bfmeSlot25BG();
	virtual void bfmeMarkBG(void *dst);
	virtual void bfmeLateBG(void *dst);
	virtual void bfmeSlot28BG();
	virtual void bfmeSlot29BG();
	virtual void bfmeSlot30BG();
	virtual void bfmeSlot31BG();
	virtual void bfmeSlot32BG();
	virtual void bfmeSlot33BG();
	virtual void bfmeSlot34BG();
	virtual void bfmeByteBG(unsigned char *dst);
};

extern "C" void __cdecl bfmeXferOneBG(BfmeAgentBG *ag, void *dst);
extern "C" void __cdecl bfmeXferTwoBG(BfmeAgentBG *ag, void *dst);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeHostBGInitFields
{
	unsigned int m_field00;
	unsigned int m_field04;
	unsigned int m_field08;
	float m_scale0C;
	unsigned char m_padding10[0x10];
	unsigned int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	unsigned int m_field2C;
	unsigned int m_field30;
	unsigned int m_field34;
	unsigned int m_field38;
	unsigned int m_field3C;
	unsigned int m_field40;
	unsigned int m_field44;
	unsigned int m_field48;
	float m_scale4C;
	unsigned int m_field50;
	unsigned int m_field54;
	unsigned int m_field58;
	unsigned int m_field5C;
	float m_scale60;
	unsigned int m_field64;
	unsigned int m_field68;
	unsigned int m_field6C;
	unsigned int m_field70;
	float m_scale74;
	unsigned int m_field78;
	unsigned char m_field7C;
	unsigned char m_field7D;
	unsigned char m_field7E;
	unsigned char m_field7F;
	float m_scale80;
	unsigned int m_field84;
	unsigned int m_field88;
	unsigned int m_field8C;
	unsigned int m_field90;
	unsigned char m_field94;
	unsigned char m_field95;
};

class BfmeHostBG
{
public:
	BfmeHostBG(void);
	void bfmeSaveBG(BfmeAgentBG *ag);

	unsigned char m_bfmeHeadBG[0x48];
	unsigned char m_bfmeSlotABG[4];
	unsigned char m_bfmeSlotBBG[4];
	unsigned char m_bfmePadOneBG[0x2c];
	unsigned char m_bfmeSlotCBG;
	unsigned char m_bfmeSlotDBG;
	unsigned char m_bfmeSlotEBG;
	unsigned char m_bfmePadTwoBG;
	unsigned char m_bfmeSlotFBG[4];
	unsigned char m_bfmeSlotGBG[4];
	unsigned char m_bfmeSlotHBG[4];
	unsigned char m_bfmeSlotIBG[4];
	unsigned char m_bfmeSlotJBG[4];
	unsigned char m_bfmeSlotKBG;
};

BfmeHostBG::BfmeHostBG(void)
{
	BfmeHostBGInitFields *fields = reinterpret_cast<BfmeHostBGInitFields *>(this);
	fields->m_field00 = 0;
	fields->m_field04 = 0;
	fields->m_field08 = 0;
	_ReadWriteBarrier();
	fields->m_scale0C = 1.0f;
	fields->m_field20 = 0;
	fields->m_field24 = 0;
	fields->m_field28 = 0;
	fields->m_field2C = 0;
	fields->m_field30 = 0;
	fields->m_field34 = 0;
	fields->m_field38 = 0;
	fields->m_field3C = 0;
	fields->m_field40 = 0;
	fields->m_field44 = 0;
	fields->m_field48 = 0;
	fields->m_scale4C = 1.0f;
	fields->m_field50 = 0;
	fields->m_field54 = 0;
	fields->m_field58 = 0;
	fields->m_field5C = 0;
	fields->m_scale60 = 1.0f;
	fields->m_field64 = 0;
	fields->m_field68 = 0;
	fields->m_field6C = 0;
	fields->m_field70 = 0;
	fields->m_scale74 = 1.0f;
	fields->m_field78 = 0;
	fields->m_field7C = 0;
	fields->m_field7D = 0;
	fields->m_field7E = 0;
	fields->m_scale80 = 1.0f;
	fields->m_field84 = 0;
	fields->m_field88 = 0;
	fields->m_field8C = 0;
	fields->m_field90 = 0;
	fields->m_field94 = 0;
	fields->m_field95 = 0;
}

void BfmeHostBG::bfmeSaveBG(BfmeAgentBG *ag)
{
	ag->bfmeMarkBG(m_bfmeSlotHBG);

	bfmeXferOneBG(ag, m_bfmeSlotABG);
	bfmeXferTwoBG(ag, m_bfmeSlotBBG);

	ag->bfmeByteBG(&m_bfmeSlotCBG);
	ag->bfmeByteBG(&m_bfmeSlotDBG);
	ag->bfmeByteBG(&m_bfmeSlotEBG);
	ag->bfmeLateBG(m_bfmeSlotFBG);
	ag->bfmeLateBG(m_bfmeSlotGBG);
	ag->bfmeBlockBG(m_bfmeSlotIBG, 4);
	ag->bfmeBlockBG(m_bfmeSlotJBG, 4);
	ag->bfmeByteBG(&m_bfmeSlotKBG);
}
