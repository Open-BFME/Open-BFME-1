// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class Rva0060A470Element
{
public:
	void update();
};

class Rva0060FF60Vector
{
public:
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	Rva0060A470Element *at(unsigned int index) const
	{
		return m_begin[index];
	}

private:
	Rva0060A470Element **m_begin;
	Rva0060A470Element **m_end;
	Rva0060A470Element **m_capacity;
};

class Rva0060FF60Owner
{
public:
	void updateElements();

private:
	char m_head[0x258];
	Rva0060FF60Vector m_elements;
};

void Rva0060FF60Owner::updateElements()
{
	for (unsigned int i = 0; i < m_elements.size(); ++i)
		m_elements.at(i)->update();
}
