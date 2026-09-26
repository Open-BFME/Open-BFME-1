// ?getBlend@Rva0076EDA0Holder@@QAEXHPAURva0076EDA0Output@@0@Z
// partial score=0.45 date=2026-09-09
// The retail body at 0x0076EDA0 belongs to the same three-entry holder as the
// named sibling at 0x0076EB50. Both bodies compare the stamp at +0x90 with
// g_Va012F8064 and call the holder owner at this-0xc when the cache is stale.

class Rva0076CAF0ConditionalDispatch
{
public:
	void dispatchIfStale();
};

class Rva0076EDA0Item
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual int getValue();
};

extern int g_Va012F8064;
extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;
extern float g_Va01123C58;

struct Rva0076EDA0Output
{
	float first;
	float second;
};

struct Rva0076EDA0Entry
{
	unsigned char padding[0xd0];
	Rva0076EDA0Item *item;
	float lower;
	float upper;
	unsigned char entryPadding[8];
	int type;
	unsigned char enabled;
};

class Rva0076EDA0Holder
{
public:
	void getBlend(int index, Rva0076EDA0Output *first, Rva0076EDA0Output *second);

	unsigned char padding[0x90];
	int stamp;
};

void Rva0076EDA0Holder::getBlend(int index, Rva0076EDA0Output *first,
	Rva0076EDA0Output *second)
{
	Rva0076EDA0Entry *entry;
	Rva0076CAF0ConditionalDispatch *owner =
		(Rva0076CAF0ConditionalDispatch *)((char *)this - 0xc);
	int currentStamp = stamp;
	if (g_Va012F8064 != currentStamp)
		owner->dispatchIfStale();

	if (index < 0 || index >= 3)
	{
		first->first = 0.0f;
		first->second = 0.0f;
		second->first = 0.0f;
		second->second = 0.0f;
		return;
	}

	entry = (Rva0076EDA0Entry *)((char *)this + index * 0x1c);
	if (entry->item == 0)
	{
		first->first = 0.0f;
		first->second = 0.0f;
		second->first = 0.0f;
		second->second = 0.0f;
		return;
	}
	if (!entry->enabled)
	{
		first->first = entry->upper;
		first->second = 0.0f;
		second->first = 0.0f;
		second->second = 0.0f;
		return;
	}

	int type = *(int *)((char *)this + (index + 8) * 0x1c);
	if (type == 1)
	{
		if (entry->upper > entry->lower)
		{
			first->first = entry->upper;
			first->second = 0.0f;
			second->first = 0.0f;
			second->second = 0.0f;
			return;
		}
		first->first = -0.00001f;
	}
	else if (type == 3)
	{
		first->first = entry->upper;
		first->second = (float)entry->item->getValue() - g_bfmeDefaultBU;
		second->first = 0.0f;
		second->second = 0.0f;
	}
	else if (type == 5)
	{
		first->first = (float)entry->item->getValue() - g_Va01123C58;
	}
	else
	{
		first->first = entry->upper;
		first->second = entry->lower;
		second->first = 0.0f;
		second->second = 0.0f;
		return;
	}
	first->first = entry->upper;
	first->second = (float)entry->item->getValue();
	second->first = -0.00001f;
	second->second = entry->lower;
}
