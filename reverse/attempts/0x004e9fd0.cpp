// ??0Gen_t_004ea1f0_m4cd@@QAE@ABU0@@Z
// partial score=0.82 date=2026-09-04
// cl: /O2 /Ob0 /EHsc

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);
	~StringBase();

private:
	void *m_item;
};

struct Gen_t_004ea1f0_m4cd
{
	int m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	int m_10;
	StringBase<unsigned short> m_14;
	StringBase<unsigned short> m_18;

	Gen_t_004ea1f0_m4cd(const Gen_t_004ea1f0_m4cd &other)
		: m_00(other.m_00)
		, m_04(other.m_04)
		, m_08(other.m_08)
		, m_0C(other.m_0C)
		, m_10(other.m_10)
		, m_14(other.m_14)
		, m_18(other.m_18)
	{
	}
};

void Rva004E9FD0ForceCopy(const Gen_t_004ea1f0_m4cd &other)
{
	Gen_t_004ea1f0_m4cd local(other);
}
