// cl: /O2 /Ob0 /G6

struct BfmeFalseCD
{
};

struct BfmeTailCD
{
	void copyFrom(const BfmeTailCD *src);
};

struct BfmeElemCD
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailCD m_0C;
};

void *__cdecl bfmeAllocLargeCD(unsigned bytes);
void *__cdecl bfmeAllocSmallCD(unsigned bytes);

BfmeElemCD *bfmeCopyCD(const BfmeElemCD *first, const BfmeElemCD *last,
	BfmeElemCD *result, const BfmeFalseCD &);
BfmeElemCD *bfmeFillCD(BfmeElemCD *result, unsigned count,
	const BfmeElemCD &value, const BfmeFalseCD &);

class BfmeVecCD
{
public:
	void overflow(BfmeElemCD *pos, const BfmeElemCD &value,
		const BfmeFalseCD &, unsigned fill, bool atEnd);
	void clear();

	BfmeElemCD *_M_start;
	BfmeElemCD *_M_finish;
	BfmeElemCD *_M_end_of_storage;
};

void BfmeVecCD::overflow(BfmeElemCD *pos, const BfmeElemCD &value,
	const BfmeFalseCD &, unsigned fill, bool atEnd)
{
	unsigned oldSize = (unsigned)(_M_finish - _M_start);
	const unsigned &growth = oldSize < fill ? fill : oldSize;
	unsigned length = growth + oldSize;

	BfmeElemCD *newStart;
	if (length)
	{
		unsigned bytes = length * sizeof(BfmeElemCD);
		if (bytes > 128)
			newStart = (BfmeElemCD *)bfmeAllocLargeCD(bytes);
		else
			newStart = (BfmeElemCD *)bfmeAllocSmallCD(bytes);
	}
	else
	{
		newStart = 0;
	}

	BfmeElemCD *newFinish = bfmeCopyCD(_M_start, pos, newStart,
		reinterpret_cast<const BfmeFalseCD &>(atEnd));

	if (fill == 1)
	{
		if (newFinish)
		{
			const BfmeElemCD *v = &value;
			newFinish->m_00 = v->m_00;
			newFinish->m_04 = v->m_04;
			newFinish->m_08 = v->m_08;
			newFinish->m_0C.copyFrom(&v->m_0C);
		}
		++newFinish;
	}
	else
	{
		newFinish = bfmeFillCD(newFinish, fill, value,
			reinterpret_cast<const BfmeFalseCD &>(atEnd));
	}

	if (!atEnd)
		newFinish = bfmeCopyCD(pos, _M_finish, newFinish,
			reinterpret_cast<const BfmeFalseCD &>(atEnd));

	clear();

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}
