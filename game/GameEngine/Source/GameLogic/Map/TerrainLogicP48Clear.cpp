// cl: /DNDEBUG /MD /EHsc
// TerrainLogicP48::clear, retail 0x001A61F0.

struct TerrainLogicP48ClearRec
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

struct GameLogicFrame_001A61F0
{
	char pad[0x3C];
	int frame;
};

class TerrainVisualNotify_001A61F0
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
	virtual void notify(int key);
};

class TerrainLogicP48Clear
{
public:
	void clear(int key);

private:
	char m_pad[0x55C];
	TerrainLogicP48ClearRec *m_begin;
	TerrainLogicP48ClearRec *m_end;
	char m_pad564[0x18F0 - 0x564];
	int m_frameStamp;
};

void TerrainLogicP48Clear::clear(int key)
{
	m_frameStamp = (*(GameLogicFrame_001A61F0 **)0x012F0898)->frame;

	TerrainLogicP48ClearRec *first = m_begin;
	while (first != m_end)
	{
		if (first->key == key)
		{
			first->m0 = 0;
			first->m4 = 0;
			first->m8 = 0;
			first->key = 0;
			first->m10 = 0;
			first->m14 = 0;
			first->m18 = 0;
			first->field28 = 1;
			first->m2c = 1;
			first->m2d = 1;
			break;
		}
		++first;
	}
	TerrainVisualNotify_001A61F0 *visual =
		*(TerrainVisualNotify_001A61F0 **)0x012F7014;
	visual->notify(key);
}
