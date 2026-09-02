// cl: /DNDEBUG /MD /EHsc

// Open-BFME: TerrainLogic walk of the 48-byte record vector at +0x55C,
// retail 0x001A7A50.  On a key match at +0x0C it calls the thiscall at
// 0x001A6550 with (record, record+0x28).

struct TerrainLogicP48Rec
{
	int m_pad0[3];
	int m_key;
	char m_pad10[0x18];
	int m_field28;
	int m_pad2c;
};

class TerrainLogicP48Owner
{
public:
	void onMatch(TerrainLogicP48Rec *record, int value);
	void find(int key);

private:
	char m_pad[0x55C];
	TerrainLogicP48Rec *m_begin;
	TerrainLogicP48Rec *m_end;
};

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
