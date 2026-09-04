// cl: /DNDEBUG /MD /EHs-c-
// TerrainLogic::reset, retail 0x001ACF90 size 183.
// SubsystemInterface virtual: ecx is this+4. First vptr getFirstBridge is slot 37.

class HeapNode
{
public:
	virtual void destroy(int flag);
};

extern HeapNode *g_Va012EF4D0;

class Bridge
{
public:
	virtual void destroy(int flag);
	Bridge *m_next;
};

class SnapshotView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
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
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual Bridge *getFirstBridge();
};

class Member48
{
public:
	void clearA();
};

struct BfmeTerrainP48
{
	int m_words[12];
};

struct RandomAccessIteratorTag
{
};

BfmeTerrainP48 *copyP48(BfmeTerrainP48 *first, BfmeTerrainP48 *last,
	BfmeTerrainP48 *result, const RandomAccessIteratorTag &, int *);

void resetHelper4949a();
void bfmeFreeArray(void *p);

class TerrainLogic
{
public:
	virtual void reset();

private:
	char m_pad04[0x14 - 4];
	void *m_array;
	char m_pad18[0x30 - 0x18];
	Bridge *m_bridgeHead;
	char m_pad34[0x38 - 0x34];
	int m_field38;
	char m_pad3C[0x548 - 0x3C];
	int m_field548;
	char m_pad54C[0x558 - 0x54C];
	BfmeTerrainP48 *m_p48begin;
	BfmeTerrainP48 *m_p48end;
	char m_pad560[4];
	int m_fill[0x4E2];
	int m_field18EC;
	char m_pad18F0[0x18F4 - 0x18F0];
	int m_field18F4;
};

void TerrainLogic::reset()
{
	SnapshotView *first;
	while (g_Va012EF4D0)
		g_Va012EF4D0->destroy(1);

	first = (SnapshotView *)((char *)this - 4);
	Bridge *bridge = first->getFirstBridge();
	while (bridge)
	{
		Bridge *next = bridge->m_next;
		__asm mov dword ptr [eax+4], ebp
		bridge->destroy(1);
		bridge = next;
	}
	*(Bridge **)((char *)first + 0x34) = 0;

	((Member48 *)((char *)this + 0x44))->clearA();
	resetHelper4949a();

	BfmeTerrainP48 *result = m_p48begin;
	BfmeTerrainP48 *finish = m_p48end;
	RandomAccessIteratorTag tag;
	m_p48end = copyP48(finish, finish, result, tag, 0);

	int fillVal = -1;
	int *fill = m_fill;
	int fillN = 0x4E2;
	do
	{
		*fill++ = fillVal;
	} while (--fillN);

	m_field548 = 0;
	m_field18EC = 0;
	m_field38 = 1;

	void *array = *(void **)((char *)first + 0x18);
	bfmeFreeArray(array);
	*(void **)((char *)first + 0x18) = 0;
	m_field18F4 = 0;
}
