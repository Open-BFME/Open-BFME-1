// ?findAndInvoke@Gen00736AF0Owner@@QAE_NHH@Z
// partial score=0.86 date=2026-09-02
// Address-derived reconstruction of the fixed-array find-and-invoke at 0x00736AF0.
// stlport

class Gen00736AF0Item
{
public:
	int m_fieldA;			// 0x00
	char m_pad04[0x70 - 0x04];
	int m_fieldC;			// 0x70
	char m_pad74[0x7C - 0x74];
	int m_fieldB;			// 0x7C
	char m_pad80[0xE8 - 0x80];
};

class Gen00736AF0Owner
{
public:
	bool findAndInvoke(int fieldAValue, int value);
	void invokeAt(int index, int value);

private:
	char m_pad00[0x208];
	Gen00736AF0Item m_items[1];
	char m_padAfterItems[0x2A7CB0 - 0x208 - sizeof(Gen00736AF0Item)];
	int m_itemCount;		// 0x2A7CB0
};

bool Gen00736AF0Owner::findAndInvoke(int fieldAValue, int value)
{
	if (fieldAValue == 0)
		return false;

	int count = m_itemCount;
	for (int index = 0; index < count; ++index)
	{
		Gen00736AF0Item *item = m_items + index;
		if (item->m_fieldA != fieldAValue)
			continue;
		if (item->m_fieldB != 0)
			continue;
		if (item->m_fieldC != 0)
			continue;

		invokeAt(index, value);
		return true;
	}
	return false;
}
