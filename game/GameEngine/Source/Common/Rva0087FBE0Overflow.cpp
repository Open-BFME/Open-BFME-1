// cl: /O2 /Ob0 /G6

struct BfmeFalseBE
{
};

struct BfmeTailBE
{
	char *m_p;
	void copyFrom(const BfmeTailBE *src);
};

struct BfmeCoordBE
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordBE m_10;
	BfmeTailBE m_1C;
	char m_20;
	char m_pad[3];

	void copyFrom(const BfmeElemBE &src);
};

void *__cdecl bfmeAllocLargeBE(unsigned bytes);
void *__cdecl bfmeAllocSmallBE(unsigned bytes);

BfmeElemBE *bfmeCopyBE(const BfmeElemBE *first, const BfmeElemBE *last,
	BfmeElemBE *result, const BfmeFalseBE &);
BfmeElemBE *bfmeFillBE(BfmeElemBE *result, unsigned count,
	const BfmeElemBE &value, const BfmeFalseBE &);

class BfmeVecBE
{
public:
	void overflow(BfmeElemBE *pos, const BfmeElemBE &value,
		const BfmeFalseBE &, unsigned fill, bool atEnd);
	void clear();

	BfmeElemBE *_M_start;
	BfmeElemBE *_M_finish;
	BfmeElemBE *_M_end_of_storage;
};

void BfmeVecBE::overflow(BfmeElemBE *pos, const BfmeElemBE &value,
	const BfmeFalseBE &, unsigned fill, bool atEnd)
{
	unsigned oldSize = (unsigned)(_M_finish - _M_start);
	const unsigned &growth = oldSize < fill ? fill : oldSize;
	unsigned length = growth + oldSize;

	BfmeElemBE *newStart;
	if (length)
	{
		unsigned bytes = length * sizeof(BfmeElemBE);
		if (bytes > 128)
			newStart = (BfmeElemBE *)bfmeAllocLargeBE(bytes);
		else
			newStart = (BfmeElemBE *)bfmeAllocSmallBE(bytes);
	}
	else
	{
		newStart = 0;
	}

	BfmeElemBE *newFinish = bfmeCopyBE(_M_start, pos, newStart,
		reinterpret_cast<const BfmeFalseBE &>(atEnd));

	if (fill == 1)
	{
		if (newFinish)
			newFinish->copyFrom(value);
		++newFinish;
	}
	else
	{
		newFinish = bfmeFillBE(newFinish, fill, value,
			reinterpret_cast<const BfmeFalseBE &>(atEnd));
	}

	if (!atEnd)
		newFinish = bfmeCopyBE(pos, _M_finish, newFinish,
			reinterpret_cast<const BfmeFalseBE &>(atEnd));

	clear();

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}
