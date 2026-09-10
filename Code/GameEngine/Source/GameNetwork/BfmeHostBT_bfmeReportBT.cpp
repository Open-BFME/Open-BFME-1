// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2

typedef unsigned char Byte;

extern const char g_Rva0107301CEmptyString[];

class Rva00800290Buffer
{
public:
	void append(const char *text);

private:
	int data;
};

class BfmeReportTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void report(int first, int second, int third) = 0;
};

struct BfmeBTSlot
{
	int active;
	int unused04;
	int unused08;
	Byte unused0c;
	Byte padding0d[3];
	int unused10;
	Rva00800290Buffer text;
	int unused18;
	struct Ids
	{
		int idB;
		int idA;
	} ids;
	Byte padding24[0x40];
	Byte unused64;
	Byte padding65[0x2f];
};

class BfmeHostBT
{
public:
	void bfmeReportBT(int first, int second);

private:
	Byte padding00[0x1c];
	BfmeReportTarget *target;
	Byte padding20[0x40];
	BfmeBTSlot slots[4];
};

void BfmeHostBT::bfmeReportBT(int first, int second)
{
	int index = 0;
	BfmeBTSlot::Ids *ids = &slots[0].ids;
	for (; index < 4; ++index,
		ids = (BfmeBTSlot::Ids *)((char *)ids + sizeof(BfmeBTSlot)))
	{
		BfmeBTSlot *slot = (BfmeBTSlot *)((char *)ids - 0x1c);
		if (slot->active != 0 && ids->idB == second && ids->idA == first)
		{
			target->report(first, second, 0);
			slot->active = 0;
			slot->unused04 = 0;
			slot->unused08 = 0;
			slot->unused0c = 0;
			slot->unused10 = 0;
			slot->text.append(g_Rva0107301CEmptyString);
			ids->idB = 0;
			ids->idA = 0;
			*(Byte *)((char *)ids + 0x48) = 0;
			return;
		}
	}
}
