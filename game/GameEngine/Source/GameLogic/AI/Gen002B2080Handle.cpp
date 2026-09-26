// cl: /DNDEBUG /MD /EHsc

struct FlagPair2B2080
{
	bool m_first;
	bool m_second;
};

class BfmeSeedTarget;

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
	virtual void applyFlags(const FlagPair2B2080 &flags);
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

private:
	unsigned char m_beforeValue[0x14];
	unsigned int m_value14;
	int m_value18;
};

// @?handle@Gen002B2080@@QAEXPAVFlagPairTarget@@@Z 0x002B2080
void Gen002B2080::handle(FlagPairTarget *target)
{
	FlagPair2B2080 flags;
	flags.m_first = true;
	flags.m_second = true;
	target->applyFlags(flags);

	bfmeAccept((BfmeSeedTarget *)target);
	if (!target->slot10())
	{
		target->updateValue(&m_value14);
		if (target->slot04())
			m_value18 = -1;
	}
}
