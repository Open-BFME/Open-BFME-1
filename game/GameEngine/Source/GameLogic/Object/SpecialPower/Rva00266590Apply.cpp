// cl: /DNDEBUG /MD /EHsc
// Address-derived reconstruction of retail RVA 0x00266590 (171 bytes).
// The owning class is not recovered; the owner/target names describe only
// the proven ABI and field layout used by this body.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeSeedTarget
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09(void *, UnsignedInt);
	virtual void slot10(void *);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24(void *);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29(void *);
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35(void *);
};

// Retail callee at 0x00033B77; this address is pinned as the owner's
// private bfmeAccept(BfmeSeedTarget *) helper.
class Gen_0025A590
{
public:
	void apply(BfmeSeedTarget *target);

	char m_pad00[0x38];
	int m_field38;
	int m_field3c;
	int m_field40;
	int m_field44;
	int m_field48;
	char m_pad4c[0x54 - 0x4c];
	int m_field54;
	char m_pad58[0x60 - 0x58];
	int m_field60;
	int m_field64;
	char m_pad68[0x70 - 0x68];
	int m_field70;

private:
	void bfmeAccept(BfmeSeedTarget *target);
};

// Retail callee at 0x0000C9B4; its second argument is an int-field address.
void bfmeCalcTGC(void *, int *);

// ?apply@Gen_0025A590@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0025A590::apply(BfmeSeedTarget *target)
{
	bfmeAccept(target);
	if (target->slot04())
		return;

	struct LocalPair
	{
		unsigned char first;
		unsigned char second;
	} pair = { 1, 2 };

	target->slot10(&pair);
	target->slot09(&m_field38, 4);
	target->slot29(&m_field3c);
	bfmeCalcTGC(target, &m_field40);
	bfmeCalcTGC(target, &m_field44);
	target->slot24(&m_field48);
	target->slot35(&m_field70);
	target->slot35(&m_field60);
	if (pair.second >= 2)
	{
		target->slot24(&m_field54);
		target->slot24(&m_field64);
	}
}
