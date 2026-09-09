// ?bfmeFillBE@@YAPAUBfmeElemBE@@PAU1@IABU1@ABUBfmeFalseBE@@@Z
// partial score=0.85 date=2026-09-08
inline void *operator new(unsigned int, void *p)
{
	return p;
}

struct BfmeFalseBE
{
};

struct BfmeTailBE
{
	void *m_p;
	BfmeTailBE(const BfmeTailBE &other);
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTailBE m_1C;
	char m_20;
};

#pragma comment(linker, "/alternatename:??0BfmeTailBE@@QAE@ABU0@@Z=??0?$StringBase@D@@QAE@ABV0@@Z")

namespace _STL
{
	template <class T>
	__forceinline void _Construct(T *p, const T &value)
	{
		new (p) T(value);
	}

	template <class T>
	__forceinline T *uninitialized_fill_n(T *result, unsigned int count,
		const T &value)
	{
		T *current = result;
		for (; count > 0; --count, ++current)
			_Construct(current, value);
		return current;
	}
}

BfmeElemBE *bfmeFillBE(BfmeElemBE *result, unsigned int count,
	const BfmeElemBE &value, const BfmeFalseBE &)
{
	if (count <= 0)
		goto finish;

	int *middle = &result->m_18;
	do
	{
		if (result != 0)
			new (result) BfmeElemBE(value);
		++result;
		middle += 9;
		--count;
	}
while (count != 0);

finish:
	return result;
}
