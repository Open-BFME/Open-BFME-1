// cl: /O2 /Ob0 /G6

struct BfmeFalse2E
{
};

struct BfmeElem2E
{
	char m[0x5C];
	void copyFrom(const BfmeElem2E *src);
};

void *__cdecl bfmeAllocLarge2E(unsigned bytes);
void *__cdecl bfmeAllocSmall2E(unsigned bytes);

BfmeElem2E *bfmeCopy2E(const BfmeElem2E *first, const BfmeElem2E *last,
	BfmeElem2E *result, const BfmeFalse2E &);

class BfmeVec2E
{
public:
	void overflow(BfmeElem2E *pos, const BfmeElem2E &value,
		const BfmeFalse2E &, unsigned fill, bool atEnd);
	void clear();

	BfmeElem2E *_M_start;
	BfmeElem2E *_M_finish;
	BfmeElem2E *_M_end_of_storage;
};

void BfmeVec2E::overflow(BfmeElem2E *pos, const BfmeElem2E &value,
	const BfmeFalse2E &, unsigned fill, bool atEnd)
{
	unsigned oldSize = (unsigned)(_M_finish - _M_start);
	const unsigned &growth = oldSize < fill ? fill : oldSize;
	unsigned length = growth + oldSize;

	BfmeElem2E *newStart;
	if (length)
	{
		unsigned bytes = length * sizeof(BfmeElem2E);
		if (bytes > 128)
			newStart = (BfmeElem2E *)bfmeAllocLarge2E(bytes);
		else
			newStart = (BfmeElem2E *)bfmeAllocSmall2E(bytes);
	}
	else
	{
		newStart = 0;
	}

	BfmeElem2E *newFinish = newStart;
	for (BfmeElem2E *src = _M_start; src != pos; ++src)
	{
		if (newFinish)
			newFinish->copyFrom(src);
		++newFinish;
	}

	if (fill == 1)
	{
		if (newFinish)
			newFinish->copyFrom(&value);
		++newFinish;
	}
	else
	{
		unsigned n = fill;
		if (n > 0)
		{
			do
			{
				if (newFinish)
					newFinish->copyFrom(&value);
				++newFinish;
				--n;
			} while (n);
		}
	}

	if (!atEnd)
		newFinish = bfmeCopy2E(pos, _M_finish, newFinish,
			reinterpret_cast<const BfmeFalse2E &>(atEnd));

	clear();

	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
	_M_start = newStart;
}
