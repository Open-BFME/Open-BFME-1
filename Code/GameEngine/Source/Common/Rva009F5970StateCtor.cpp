// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

struct Gen_p8cd
{
	int a[2];
};

struct T_009f4fb0
{
	void m();
};

struct T_009f59d0
{
	void m();
};

struct Rva009F5970StateInit
{
	int value[6];
};

class Rva009F5970State
{
public:
	Rva009F5970State();

private:
	int m_value0;
	int m_value1;
	int m_value2;
	int m_value3;
	int m_value4;
	int m_value5;
	_STL::vector<Gen_p8cd> m_items[17];
	void *m_head;
	float m_scale;
	unsigned m_mask;
	void *m_tail;
};

Rva009F5970State::Rva009F5970State()
{
	Rva009F5970StateInit init;
	m_head = 0;
	m_mask = 0;
	m_tail = 0;
	init.value[0] = 0;
	init.value[1] = 0;
	init.value[2] = 0;
	init.value[3] = 0;
	init.value[4] = 0;
	init.value[5] = 0;

	T_009f4fb0 *first = reinterpret_cast<T_009f4fb0 *>(this);
	typedef void (T_009f4fb0::*FirstCall)(Rva009F5970StateInit *);
	(first->*(FirstCall)&T_009f4fb0::m)(&init);

	T_009f59d0 *second = reinterpret_cast<T_009f59d0 *>(this);
	typedef void (T_009f59d0::*SecondCall)(unsigned);
	(second->*(SecondCall)&T_009f59d0::m)(0);
}
