// ?rva006169d0@BfmeLivingWorldManager@@QAEXXZ
// Retail RVA 0x006169D0, 389 bytes.
//
// BfmeLivingWorldManager owns the pointer vectors at +0x240 and +0x24C.
// The adjacent manager methods prove the receiver.
// Retail calls attachment slot +0x40 and item destructor 0x0061E3E0, which
// proves the item layout.
// Retail reads each vector through begin() during reverse cleanup loops.
// The direct getName() expression keeps its returned string in the expected
// temporary stack slot before the manager removes the name.
// Retail clears each STLport vector after its cleanup loop.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"

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
	void releaseBuffer();

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

class BfmeHostCA
{
public:
	void bfmeRemoveCA(const char *name);
};

class BfmeB1024
{
public:
	void bfmeGo1024B();
};

class BfmeLivingWorldManager
{
public:
	void rva00610090();
	void rva006169d0();

private:
	unsigned char m_prefix[0x240];
	_STL::vector<Rva006169D0Item *> m_first;
	_STL::vector<Rva006169D0Item *> m_second;
};

void BfmeLivingWorldManager::rva00610090()
{
	for (unsigned int index = 0; index < m_first.size(); ++index)
	{
		Rva006169D0Item *item = m_first.begin()[index];
		if (item != 0)
			((BfmeB1024 *)item)->bfmeGo1024B();
	}

	for (unsigned int index = 0; index < m_second.size(); ++index)
	{
		Rva006169D0Item *item = m_second.begin()[index];
		if (item != 0)
			((BfmeB1024 *)item)->bfmeGo1024B();
	}
}

void BfmeLivingWorldManager::rva006169d0()
{
	rva00610090();

	for (int index = (int)m_first.size() - 1; index >= 0; --index)
	{
		if (m_first.begin()[index]->m_attachment != 0)
		{
			m_first.begin()[index]->m_attachment->slot40();

			reinterpret_cast<BfmeHostCA *>(this)->bfmeRemoveCA(
				m_first.begin()[index]->getName().str());

			Rva006169D0Item *item = m_first.begin()[index];
			if (item != 0)
			{
				item->destroy();
				::operator delete(item);
			}
		}
	}
	m_first.clear();

	for (int index = (int)m_second.size() - 1; index >= 0; --index)
	{
		if (m_second.begin()[index]->m_attachment != 0)
		{
			m_second.begin()[index]->m_attachment->slot40();
			Rva006169D0Item *item = m_second.begin()[index];
			if (item != 0)
			{
				item->destroy();
				::operator delete(item);
			}
		}
	}
	m_second.clear();
}
