// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: ModuleInfo::clearCopiedFromDefaultEntries at retail RVA 0x001416F0.

typedef bool Bool;

class Rva001417F0ModuleInfo
{
	public:
	struct Nugget
	{
		unsigned char m_data[16];
		Bool copiedFromDefault;
		Bool inheritable;
		unsigned char m_padding[2];

		~Nugget();
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first,
	InputIterator last,
	OutputIterator result,
	const random_access_iterator_tag &,
	Distance *);
}

class ModuleInfo
{
private:
	typedef Rva001417F0ModuleInfo::Nugget Nugget;
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;

public:
	Bool clearCopiedFromDefaultEntries(int interfaceMask);
};

Bool ModuleInfo::clearCopiedFromDefaultEntries(int interfaceMask)
{
	Bool ret = false;

	Nugget *it = m_begin;
	while (it != m_end)
	{
		if ((*(int *)((char *)it + 0x0c) & interfaceMask) != 0
			&& it->copiedFromDefault && !it->inheritable)
		{
			Nugget *next = it + 1;
			if (next != m_end)
			{
				_STL::random_access_iterator_tag category;
				_STL::__copy(next, m_end, it, category, (int *)0);
			}
			--m_end;
			m_end->~Nugget();
			ret = true;
		}
		else
		{
			++it;
		}
	}
	return ret;
}
