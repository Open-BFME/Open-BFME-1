// cl: /O2 /Ob2 /GR- /MD /EHsc /D_STLP_USE_STATIC_LIB
// partial score=0.9 date=2026-09-08

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

template <typename T>
class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class Rva0061E3E0Attachment
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
};

class Rva006169D0Item
{
public:
	virtual void itemSlot00() = 0;
	virtual void itemSlot04() = 0;
	virtual void itemSlot08() = 0;
	virtual void itemSlot0c() = 0;
	virtual void itemSlot10() = 0;
	virtual void itemSlot14() = 0;
	virtual void itemSlot18() = 0;
	virtual void itemSlot1c() = 0;
	virtual void itemSlot20() = 0;
	virtual void itemSlot24() = 0;
	virtual void itemSlot28() = 0;
	virtual void itemSlot2c() = 0;
	virtual void itemSlot30() = 0;
	virtual void itemSlot34() = 0;
	virtual void itemSlot38() = 0;
	virtual void itemSlot3c() = 0;
	virtual void itemSlot40() = 0;
	BFMERetailAsciiString getName();
	void destroy();

	BFMERetailAsciiString m_name;
	Rva0061E3E0Attachment *m_attachment;
};

class Rva006169D0Vector
{
public:
	int size() const
	{
		return (int)(m_end - m_begin);
	}

	Rva006169D0Item *operator[](int index) const
	{
		return m_begin[index];
	}

	Rva006169D0Item **begin() const
	{
		return m_begin;
	}

	Rva006169D0Item **end() const
	{
		return m_end;
	}

	void erase(Rva006169D0Item **first, Rva006169D0Item **last)
	{
		Rva006169D0Item **finish = m_end;
		Rva006169D0Item **newFinish = first;
		if (last != finish)
		{
			unsigned int bytes = (unsigned int)((char *)finish - (char *)last);
			newFinish = (Rva006169D0Item **)((char *)memmove(first, last, bytes) + bytes);
		}
		m_end = newFinish;
	}

	Rva006169D0Item **m_begin;
	Rva006169D0Item **m_end;
	Rva006169D0Item **m_capacity;
};

class BfmeLivingWorldManager
{
public:
	void rva00610090();
	void removeObject(const char *name);
	void rva006169d0();

private:
	unsigned char m_prefix[0x240];
	Rva006169D0Vector m_first;
	Rva006169D0Vector m_second;
};

void BfmeLivingWorldManager::rva006169d0()
{
	rva00610090();

	for (int index = (int)m_first.size() - 1; index >= 0; --index)
	{
		if (m_first[index]->m_attachment != 0)
		{
			m_first[index]->m_attachment->slot40();

			BFMERetailAsciiString name = m_first[index]->getName();
			removeObject(name.str());

			Rva006169D0Item *item = m_first[index];
			if (item != 0)
			{
				item->destroy();
				::operator delete(item);
			}
		}
	}
	m_first.erase(m_first.begin(), m_first.end());

	for (int index = (int)m_second.size() - 1; index >= 0; --index)
	{
		Rva006169D0Item *item = m_second[index];
		if (item != 0 && item->m_attachment != 0)
			item->m_attachment->slot40();
		if (item != 0)
		{
			item->destroy();
			::operator delete(item);
		}
	}
	m_second.erase(m_second.begin(), m_second.end());
}
