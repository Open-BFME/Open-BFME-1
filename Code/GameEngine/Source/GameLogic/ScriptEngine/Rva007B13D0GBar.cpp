// ?bar@Rva007B13D0G@@QAEXPAURva007AFB50Shadow@@@Z
// partial score=0.97 date=2026-09-02
// Open-BFME: Rva007B13D0G::bar, retail 0x007AFB50, 153 bytes.

class ClientFrameSubsystem
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual unsigned int getFrame(void);
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;

class Gen00459960
{
public:
	void setBounds(int, int, int, int, int, int, int, int);
};

struct W3DProjectedShadow;

class W3DProjectedShadowManager
{
public:
	bool recycleFromList(W3DProjectedShadow *, W3DProjectedShadow **);
};

struct Rva007AFB50Shadow
{
	unsigned char m_pad0[0x34];
	int m_type;
	unsigned char m_pad1[4];
	unsigned int m_frame;
	int m_40;
	unsigned char m_pad2[4];
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	unsigned char m_pad3[0x2C];
	unsigned char m_flag84;
	unsigned char m_flag85;
};

class Rva007B13D0G
{
public:
	void bar(Rva007AFB50Shadow *shadow);

private:
	unsigned char m_pad0[4];
	Rva007AFB50Shadow *m_list04;
	Rva007AFB50Shadow *m_list08;
	Rva007AFB50Shadow *m_list0C;
	unsigned char m_pad1[0x0C];
	Rva007AFB50Shadow *m_list1C;
};

void Rva007B13D0G::bar(Rva007AFB50Shadow *shadow)
{
	if ((shadow->m_type & 0x0C00) && shadow->m_frame > TheGameClientClientUpdate->getFrame())
	{
		int a40 = shadow->m_40;
		int a48 = shadow->m_48;
		int extra = shadow->m_4C;
		int span = shadow->m_50;
		int a54 = shadow->m_54;
		if (extra == -1)
			reinterpret_cast<Gen00459960 *>(shadow)->setBounds(0, span, a40, 0, a48, 0, span, a54);
		else
		{
			span -= extra;
			reinterpret_cast<Gen00459960 *>(shadow)->setBounds(0, span, a40, 0, a48, 0, span, a54);
		}
		return;
	}

	if (shadow->m_type & 0x1C61)
	{
		if (shadow->m_flag84)
		{
			if (reinterpret_cast<W3DProjectedShadowManager *>(this)->recycleFromList(reinterpret_cast<W3DProjectedShadow *>(shadow), reinterpret_cast<W3DProjectedShadow **>(&m_list0C)))
				return;
		}
		else if (shadow->m_flag85)
		{
			if (reinterpret_cast<W3DProjectedShadowManager *>(this)->recycleFromList(reinterpret_cast<W3DProjectedShadow *>(shadow), reinterpret_cast<W3DProjectedShadow **>(&m_list1C)))
				return;
		}
		else
		{
			if (reinterpret_cast<W3DProjectedShadowManager *>(this)->recycleFromList(reinterpret_cast<W3DProjectedShadow *>(shadow), reinterpret_cast<W3DProjectedShadow **>(&m_list08)))
				return;
		}
	}

	reinterpret_cast<W3DProjectedShadowManager *>(this)->recycleFromList(reinterpret_cast<W3DProjectedShadow *>(shadow), reinterpret_cast<W3DProjectedShadow **>(&m_list04));
}
