// cl: /DNDEBUG /DWIN32 /MD

typedef bool Bool;

class ModuleData
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual Bool isAiModuleData() const;
};

class ModuleInfo
{
public:
	struct Nugget
	{
		unsigned char m_strings[8];
		const ModuleData *second;
		int m_interfaceMask;
		unsigned char m_flags[4];

		~Nugget();
	};

	Bool clearAiModuleInfo();

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
