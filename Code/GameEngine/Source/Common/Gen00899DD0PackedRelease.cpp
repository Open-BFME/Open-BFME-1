// ?bfmeRelease99DD0@Rva00899DD0@@QAEXXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeItemGH
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual bool canRelease() = 0;

	union
	{
		unsigned m_flags;
		struct
		{
			unsigned short m_low;
			unsigned short m_kind;
		};
	};
};

class BfmeThingGH
{
public:
	void bfmeSetGH(BfmeItemGH *item);
};

class Rva00899DD0
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	void bfmeRelease99DD0();

	union
	{
		unsigned m_flags;
		struct
		{
			unsigned short m_low;
			unsigned short m_kind;
		};
	};
	char m_pad08[0x10];
	BfmeItemGH *m_item;
};

void Rva00899DD0::bfmeRelease99DD0()
{
	unsigned count = m_kind & 0xfff;

	if (m_item != 0 && count == 2 && m_item->canRelease() != 0 &&
		(m_item->m_kind & 0xfff) == 1)
	{
		((BfmeThingGH *)this)->bfmeSetGH(0);
		count = m_kind & 0xfff;
	}

	--count;
	unsigned next = count;
	if (next > 0xfff)
		next = 0xfff;
	m_flags = (m_flags & 0xf000ffff) | (next << 16);

	if (count == 0)
		slot02();
}
