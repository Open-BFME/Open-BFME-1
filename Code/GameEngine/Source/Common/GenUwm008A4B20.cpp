// Open-BFME: 64-slot refcounted pointer table insert, retail 0x008A4B20.

class BfmeRef008A4B20
{
public:
	virtual void addRef();
	virtual void release();
};

class BfmePtrTable64_008A4B20
{
public:
	void add(BfmeRef008A4B20 *obj);
	int remove(BfmeRef008A4B20 *key);

	int m_count;
	BfmeRef008A4B20 *m_slots[64];
};

void BfmePtrTable64_008A4B20::add(BfmeRef008A4B20 *obj)
{
	int i = ++m_count;
	if (m_slots[i] != 0)
	{
		do
		{
			if (i < 0x3F)
				++i;
			else
				i = 0;
		} while (m_slots[i] != 0);
	}
	m_slots[i] = obj;
	obj->addRef();
}

int BfmePtrTable64_008A4B20::remove(BfmeRef008A4B20 *key)
{
	int i = 0;
	char *p = (char *)this + 8;
	do
	{
		if (*(BfmeRef008A4B20 **)(p - 4) == key)
			goto found;
		if (*(BfmeRef008A4B20 **)p == key)
		{
			++i;
			goto found;
		}
		if (*(BfmeRef008A4B20 **)(p + 4) == key)
		{
			i += 2;
			goto found;
		}
		if (*(BfmeRef008A4B20 **)(p + 8) == key)
		{
			i += 3;
			goto found;
		}
		i += 4;
		p += 16;
	} while (i < 0x40);
	return 0;
found:
	if (i >= 0x40)
		return 0;
	--m_count;
	m_slots[i]->release();
	m_slots[i] = 0;
	return 1;
}
