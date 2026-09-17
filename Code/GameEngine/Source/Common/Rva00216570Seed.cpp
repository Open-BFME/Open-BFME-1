// cl: /DNDEBUG /MD /EHs-c-

struct BfmeVersionBlock
{
	unsigned char m_kind;
	unsigned char m_version;
};

class BfmeSeedTarget
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual bool askAt10(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void seed(BfmeVersionBlock *version);
	virtual void slot0B(void);
	virtual void takeAt30(void *held);
	virtual void slot0D(void);
	virtual void slot0E(void);
	virtual void slot0F(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot1A(void);
	virtual void slot1B(void);
	virtual void slot1C(void);
	virtual void slot1D(void);
	virtual void slot1E(void);
	virtual void slot1F(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void takeAt8C(void *item);
};

class Rva00216570;

class Gen_00217810
{
public:
	friend class Rva00216570;

private:
	void bfmeAccept(BfmeSeedTarget *target);
	char m_pad[0x14];
};

class Rva00216570 : public Gen_00217810
{
public:
	void seed(BfmeSeedTarget *target);

private:
	void *m_held;
	char m_tail[4];
};

void Rva00216570::seed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if (target->askAt10())
		return;

	BfmeVersionBlock version;
	version.m_kind = 1;
	version.m_version = 1;
	target->seed(&version);

	unsigned char present = (m_held != 0);
	target->takeAt8C(&present);
	if (present)
		target->takeAt30(m_held);
	target->takeAt8C(m_tail);
}
