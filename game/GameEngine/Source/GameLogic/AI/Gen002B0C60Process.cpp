// cl: /DNDEBUG /MD /O2
// Open-BFME5: Gen002B2080 sibling at retail 0x002B0C60, 110 bytes.
// applyFlags with version bytes (1,3), then handle(), then versioned
// updateValue / slot90 forwarder for fields at +0x20/+0x24/+0x28.

struct FlagPair2B0C60
{
	unsigned char m_first;
	unsigned char m_second;
};

class MidVirtualSlot90Receiver;

void Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);

class FlagPairTarget
{
public:
	virtual void slot00();
	virtual bool slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual bool slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void applyFlags(const FlagPair2B0C60 &flags);
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void updateValue(void *value);
};

class BfmeSeedTarget;

class Gen_001F61B0
{
private:
	void bfmeAccept(BfmeSeedTarget *target);
	friend class Gen002B2080;
};

class Gen002B2080 : public Gen_001F61B0
{
public:
	void handle(FlagPairTarget *target);

protected:
	unsigned char m_beforeValue[0x14];
	unsigned int m_value14;
	int m_value18;
};

class Gen002B0C60 : public Gen002B2080
{
public:
	void process(FlagPairTarget *target);

private:
	char m_pad1C[4];
	unsigned int m_at20;
	unsigned int m_at24;
	unsigned int m_at28;
};

// ?process@Gen002B0C60@@QAEXPAVFlagPairTarget@@@Z
void Gen002B0C60::process(FlagPairTarget *target)
{
	FlagPair2B0C60 flags;
	flags.m_first = 1;
	flags.m_second = 3;
	target->applyFlags(flags);

	handle(target);
	target->updateValue(&m_at20);
	if (flags.m_second >= 2)
		target->updateValue(&m_at24);
	else if (target->slot04())
		m_at24 = 0;
	if (flags.m_second >= 3)
		Rva0010C3C0((MidVirtualSlot90Receiver *)target, &m_at28);
}
