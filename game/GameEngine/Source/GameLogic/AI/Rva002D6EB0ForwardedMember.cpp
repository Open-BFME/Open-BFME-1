// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class BfmeSubBPB
{
public:
	void bfmeDoBPB(void *first, void *second, void *third);
};

class Rva002D6EB0Parent
{
private:
	char m_pad00[8];

public:
	BfmeSubBPB *m_nested;
};

class Rva002D6EB0
{
public:
	void update();

private:
	char m_pad00[0x0C];
	Rva002D6EB0Parent *m_parent;
	void *m_forwarded;
};

void Rva002D6EB0::update()
{
	Rva002D6EB0Parent *parent = m_parent;
	if (parent->m_nested != 0)
		parent->m_nested->bfmeDoBPB(m_forwarded, 0, 0);
}
