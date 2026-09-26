// Advance an Apt value's counter and clear its dirty flag.
struct BfmeCounter8C5700
{
	char m_reserved[0x18];
	int m_count;
	unsigned m_flags;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int count);

	char m_reserved[0x50];
	BfmeCounter8C5700 *m_counter;
};

struct BfmeCallback8C5700
{
	int m_unused;
	BfmeThingCBC *m_value;
};

void __cdecl bfmeAdvanceCounter8C5700(void *, BfmeCallback8C5700 *payload)
{
	BfmeThingCBC *value = payload->m_value;
	value->bfmeStepCBC(value->m_counter->m_count + 1);
	value->m_counter->m_flags &= ~0x02000000u;
}

void __cdecl bfmeRetreatCounter8C5730(void *, BfmeCallback8C5700 *payload)
{
	BfmeThingCBC *value = payload->m_value;
	value->bfmeStepCBC(value->m_counter->m_count - 1);
	value->m_counter->m_flags &= ~0x02000000u;
}
