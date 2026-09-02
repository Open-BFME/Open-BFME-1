// Open-BFME5: clean C++ conversion of the four-string aggregate comparison.

typedef unsigned short wchar_t;

template <typename Character> class StringBase
{
public:
	int compare(const StringBase &other) const;

private:
	Character *m_data;
};

struct Rva005933A0Value
{
	StringBase<wchar_t> m_first;
	StringBase<wchar_t> m_second;
	StringBase<wchar_t> m_third;
	StringBase<wchar_t> m_fourth;
	unsigned short m_kind;
};

int __cdecl rva005933A0Equal(const Rva005933A0Value *left,
	const Rva005933A0Value *right)
{
	if (left->m_first.compare(right->m_first) != 0 ||
		left->m_second.compare(right->m_second) != 0 ||
		left->m_third.compare(right->m_third) != 0 ||
		left->m_fourth.compare(right->m_fourth) != 0 ||
		left->m_kind != right->m_kind) {
		return false;
	}

	return true;
}
