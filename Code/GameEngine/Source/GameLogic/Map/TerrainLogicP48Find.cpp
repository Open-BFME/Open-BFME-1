// cl: /DNDEBUG /MD /EHsc
// stlport

#include <algorithm>

// Open-BFME: TerrainLogic walk of the 48-byte record vector at +0x55C,
// retail 0x001A7A50.  On a key match at +0x0C it calls the thiscall at
// 0x001A6550 with (record, record+0x28).

struct TerrainLogicP48Rec
{
	int m0;
	int m4;
	int m8;
	int m_key;
	int m10;
	int m14;
	char m18;
	char m_pad19[0x0F];
	int m_field28;
	char m2c;
	char m2d;
	char m_pad2e[2];
};

class TerrainVisualNotify_001A6550
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
	virtual void notify(int key);
};

struct GameLogicFrame_001A6550
{
	char m_pad[0x3C];
	int frame;
};

class TerrainLogicP48Owner
{
public:
	int onMatch(TerrainLogicP48Rec *record, int value);
	void find(int key);

private:
	char m_pad[0x55C];
	TerrainLogicP48Rec *m_begin;
	TerrainLogicP48Rec *m_end;
	char m_padAfter[0x18F0 - 0x564];
	int m_frameStamp;
};

int TerrainLogicP48Owner::onMatch(TerrainLogicP48Rec *record, int value)
{
	int current = record->m_field28;
	TerrainLogicP48Owner *self = this;
	const int &currentRef = current;
	const int &take = (_STL::min)(currentRef, value);
	record->m_field28 -= take;
	if (record->m_field28 <= 0)
	{
		TerrainVisualNotify_001A6550 *visual =
			*(TerrainVisualNotify_001A6550 **)0x012F7014;
		visual->notify(record->m_key);
		record->m0 = 0;
		record->m4 = 0;
		record->m8 = 0;
		record->m_key = 0;
		record->m10 = 0;
		record->m14 = 0;
		record->m18 = 0;
		record->m_field28 = 1;
		record->m2c = 1;
		record->m2d = 1;
		GameLogicFrame_001A6550 *logic =
			*(GameLogicFrame_001A6550 **)0x012F0898;
		self->m_frameStamp = logic->frame;
	}
	return take;
}

void TerrainLogicP48Owner::find(int key)
{
	TerrainLogicP48Rec *first = m_begin;
	TerrainLogicP48Rec *last = m_end;
	if (first < last)
	{
		do
		{
			if (first->m_key == key)
			{
				onMatch(first, first->m_field28);
				return;
			}
			++first;
		}
		while (first < last);
	}
}
