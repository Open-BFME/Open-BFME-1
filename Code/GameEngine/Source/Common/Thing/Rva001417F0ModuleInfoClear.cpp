// cl: /DNDEBUG /DWIN32 /MD
//
// Near-twin of ModuleInfo::clearAiModuleInfo (twin 0x00141770,
// Code/GameEngine/Source/Common/Thing/ModuleInfoClearAi.cpp): identical
// erase-in-place loop over a Nugget array, but the predicate virtual sits at
// vtable slot 0x14 here instead of 0x10 -- one more slot ahead of it than the
// twin's ModuleData -- so this is a sibling predicate on a differently
// shaped module-data interface.  Identity is address-derived: nothing in
// these bytes says which real predicate it is.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Rva001417F0ModuleData
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual void bfmeSlot4();
	virtual Bool bfmePredicate() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class Rva001417F0ModuleInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	struct Nugget
	{
		unsigned char m_strings[8];
		const Rva001417F0ModuleData *second;
		int m_interfaceMask;
		unsigned char m_flags[4];

		~Nugget();
	};

	Bool clearModuleInfo();

private:
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

namespace _STL
{
struct random_access_iterator_tag {};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first,
	InputIterator last,
	OutputIterator result,
	const random_access_iterator_tag &,
	Distance *);
}

// @?clearModuleInfo@Rva001417F0ModuleInfo@@QAE_NXZ 0x001417F0
Bool Rva001417F0ModuleInfo::clearModuleInfo()
{
	Bool cleared = false;
	Nugget *it = m_begin;
	while (it != m_end)
	{
		if (it->second->bfmePredicate())
		{
			Nugget *next = it + 1;
			if (next != m_end)
			{
				_STL::random_access_iterator_tag category;
				_STL::__copy(next, m_end, it, category, (int *)0);
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
