struct BfmeFlagsAXB
{
	unsigned char m_bfmeOne;
	unsigned char m_bfmeTwo;
};

class BfmeSrcAXB
{
public:
	virtual void bfmeSpareAXBa0();
	virtual void bfmeSpareAXBa1();
	virtual void bfmeSpareAXBa2();
	virtual bool bfmeAskAXB();
	virtual void bfmeSpareAXBb0();
	virtual void bfmeSpareAXBb1();
	virtual void bfmeSpareAXBb2();
	virtual void bfmeSpareAXBb3();
	virtual void bfmeSpareAXBb4();
	virtual void bfmeSpareAXBb5();
	virtual void bfmeFillAXB(BfmeFlagsAXB *out);
	virtual void bfmeSpareAXBc0();
	virtual void bfmeSpareAXBc1();
	virtual void bfmeSpareAXBc2();
	virtual void bfmeSpareAXBc3();
	virtual void bfmeSpareAXBc4();
	virtual void bfmeSpareAXBc5();
	virtual void bfmeSpareAXBc6();
	virtual void bfmeSpareAXBc7();
	virtual void bfmeSpareAXBc8();
	virtual void bfmeSpareAXBc9();
	virtual void bfmeSpareAXBd0();
	virtual void bfmeSpareAXBd1();
	virtual void bfmeSpareAXBd2();
	virtual void bfmeTakeAt60(void *item);
	virtual void bfmeSpareAXBd4();
	virtual void bfmeTakeAt68(void *item);
	virtual void bfmeSpareAXBd6();
	virtual void bfmeSpareAXBd7();
	virtual void bfmeSpareAXBd8();
	virtual void bfmeTakeAt78(void *item);
	virtual void bfmeSpareAXBe0();
	virtual void bfmeSpareAXBe1();
	virtual void bfmeSpareAXBe2();
	virtual void bfmeTakeAt88(void *item);
	virtual void bfmeTakeAt8C(void *item);
};

class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);
void Rva0010C3E0(MidVirtualSlot90Receiver *receiver, void *context);
void Rva0010C400(MidVirtualSlot90Receiver *receiver, void *context);

class BfmeThingAXB
{
public:
	void bfmeSendAXB(BfmeSrcAXB *src, BfmeFlagsAXB *flags);
	void bfmeGoAXB(BfmeSrcAXB *src);

private:
	char m_bfmePad00[0x14];
	char m_bfmeField14[0x14];
	int m_bfmeField28;
	char m_bfmeField2C[0x4];
	int m_bfmeMode;
	char m_bfmeField34[0x30];
	int m_bfmeField64;
	char m_bfmeField68[0x8];
};

void BfmeThingAXB::bfmeSendAXB(BfmeSrcAXB *src, BfmeFlagsAXB *flags)
{
	char type;
	char subtype;
	char field28;

	src->bfmeTakeAt68(m_bfmeField14);
	type = (char)m_bfmeMode;
	src->bfmeTakeAt88(&type);
	m_bfmeMode = (signed char)type;
	switch (m_bfmeMode)
	{
	case 0:
		src->bfmeTakeAt60(m_bfmeField34);
		break;
	case 1:
		Rva0010C3E0((MidVirtualSlot90Receiver *)src, m_bfmeField2C);
		break;
	case 2:
		Rva0010C3C0((MidVirtualSlot90Receiver *)src, m_bfmeField2C);
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		Rva0010C400((MidVirtualSlot90Receiver *)src, m_bfmeField2C);
		break;
	}

	if (reinterpret_cast<unsigned char *>(flags)[1] >= 2)
		src->bfmeTakeAt8C(m_bfmeField34 + 0x0C);
	src->bfmeTakeAt8C(m_bfmeField34 + 0x0D);
	src->bfmeTakeAt8C(m_bfmeField34 + 0x0E);
	src->bfmeTakeAt8C(m_bfmeField34 + 0x0F);
	src->bfmeTakeAt78(m_bfmeField34 + 0x28);
	src->bfmeTakeAt8C(m_bfmeField34 + 0x11);
	field28 = (char)m_bfmeField28;
	src->bfmeTakeAt88(&field28);
	m_bfmeField28 = (signed char)field28;
	subtype = (char)m_bfmeField64;
	src->bfmeTakeAt88(&subtype);
	m_bfmeField64 = (signed char)subtype;
	src->bfmeTakeAt68(m_bfmeField68 + 4);
	src->bfmeTakeAt78(m_bfmeField68);
}

void BfmeThingAXB::bfmeGoAXB(BfmeSrcAXB *src)
{
	if (src->bfmeAskAXB())
		return;
	BfmeFlagsAXB flags;
	flags.m_bfmeOne = 1;
	flags.m_bfmeTwo = 2;
	src->bfmeFillAXB(&flags);
	bfmeSendAXB(src, &flags);
}
