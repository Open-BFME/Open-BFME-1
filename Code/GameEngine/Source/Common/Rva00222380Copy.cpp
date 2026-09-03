// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: copy constructor at 0x00222380. Six dwords of POD then an
// out-of-line StringBase<char> copy at +0x18 (??0?$StringBase@D@@AAE@ABV0@@Z).

template <typename T>
class StringBase
{
	friend class Rva00222380;

private:
	StringBase(const StringBase<T> &src);
	void *m_data;
};

struct Rva00222380Head
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
};

class Rva00222380
{
public:
	Rva00222380(const Rva00222380 &other);

private:
	Rva00222380Head m_head;
	StringBase<char> m_name;
};

// ??0Rva00222380@@QAE@ABV0@@Z
Rva00222380::Rva00222380(const Rva00222380 &other)
	: m_head(other.m_head), m_name(other.m_name)
{
}
