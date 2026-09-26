// Open-BFME5: clean C++ conversion of the sixteen-byte payload fill walk.

extern int R2Data010EC760;

struct Gen_t_003acd30_p16cd
{
	void *m_at00;
	int m_at04;
	char m_at08;
	char m_pad09[3];
	int m_at0C;
};

namespace _STL
{
struct __false_type {};

template <class Output, class Size, class Value>
Output __uninitialized_fill_n(Output result, Size count, const Value &value,
	const __false_type &)
{
	Output current = result;
	if (count > 0)
	{
		Size remaining = count;
		do
		{
			if (current != 0)
			{
				current->m_at00 = &R2Data010EC760;
				current->m_at04 = value.m_at04;
				current->m_at08 = value.m_at08;
				current->m_at0C = value.m_at0C;
			}
			++current;
		} while (--remaining != 0);
	}
	return current;
}
}

template Gen_t_003acd30_p16cd * _STL::__uninitialized_fill_n<
	Gen_t_003acd30_p16cd *, unsigned int, Gen_t_003acd30_p16cd>(
	Gen_t_003acd30_p16cd *, unsigned int, const Gen_t_003acd30_p16cd &,
	const _STL::__false_type &);
