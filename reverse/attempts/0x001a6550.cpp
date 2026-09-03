// ?release@TerrainLogicP48Release@@QAEHPAUTerrainLogicP48Rec@@H@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

#include <algorithm>

// Open-BFME: TerrainLogic 48-byte record release at 0x001A6550.  Subtracts
// min(amount, field28) from the occupancy word and resets the slot when it
// hits zero, notifying TheTerrainVisual vtable +0xAC.

struct TerrainLogicP48Rec
{
	int m0;
	int m4;
	int m8;
	int key;
	int m10;
	int m14;
	char m18;
	char pad19[0x0F];
	int field28;
	char m2c;
	char m2d;
	char pad2e[2];
};

class TerrainVisualAc
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
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void notifyKey(int key);
};

struct GameLogicFrame
{
	unsigned char pad[0x3C];
	int frame;
};

class TerrainLogicP48Release
{
public:
	int release(TerrainLogicP48Rec *record, int amount);

private:
	char m_pad[0x18F0];
	int m_frameStamp;
};

int TerrainLogicP48Release::release(TerrainLogicP48Rec *record, int amount)
{
    int current = record->field28;
	TerrainLogicP48Release *self = this;
    int take = std::min(amount, current);
	int remain = record->field28 - take;
	record->field28 = remain;
	if (remain <= 0)
	{
		(*(TerrainVisualAc **)0x012F7014)->notifyKey(record->key);
		record->m0 = 0;
		record->m4 = 0;
		record->m8 = 0;
		record->key = 0;
		record->m10 = 0;
		record->m14 = 0;
		record->m18 = 0;
		record->field28 = 1;
		record->m2c = 1;
		record->m2d = 1;
		self->m_frameStamp = (*(GameLogicFrame **)0x012F0898)->frame;
	}
	return take;
}
