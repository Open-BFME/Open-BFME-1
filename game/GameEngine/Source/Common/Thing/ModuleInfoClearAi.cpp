// cl: /DNDEBUG /DWIN32 /MD

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual Bool isAiModuleData() const;
};

// Retail 20-byte element shared with the matched 0x00134590 destruction family.
// Its original class name is not established by these container operations.
struct Gen00134590
{
    unsigned char m_strings[8];
    const ModuleData *second;
    int m_interfaceMask;
    unsigned char m_flags[4];
    ~Gen00134590();
};

class ModuleInfo
{
public:
    typedef Gen00134590 Nugget;
	Bool clearAiModuleInfo();

private:
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

namespace _STL
{
struct random_access_iterator_tag {};
}

// Retail target 0x0013EA50. Its caller pushes the three iterator arguments,
// the category tag by reference, and an unused Distance pointer.
ModuleInfo::Nugget *Rva0013EA50Copy(const ModuleInfo::Nugget *first,
	const ModuleInfo::Nugget *last, ModuleInfo::Nugget *result,
	const _STL::random_access_iterator_tag &, int *);

Bool ModuleInfo::clearAiModuleInfo()
{
	Bool cleared = false;
	Nugget *it = m_begin;
	while (it != m_end)
	{
		if (it->second->isAiModuleData())
		{
			Nugget *next = it + 1;
			if (next != m_end)
			{
				_STL::random_access_iterator_tag category;
				Rva0013EA50Copy(next, m_end, it, category, (int *)0);
			}
			--m_end;
			m_end->~Nugget();
			cleared = true;
		}
		else
		{
			++it;
		}
	}
	return cleared;
}
