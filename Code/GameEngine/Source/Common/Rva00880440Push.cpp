// cl: /O2 /Ob0 /G6

struct BfmeElem440
{
	char m[0x5C];
	void copyFrom(const BfmeElem440 *src);
};

struct BfmeFalse440
{
};

class BfmeVec440
{
public:
	void push_back(const BfmeElem440 *value);
	void overflow(BfmeElem440 *pos, const BfmeElem440 &value,
		const BfmeFalse440 &, unsigned fill, bool atEnd);

	BfmeElem440 *_M_start;
	BfmeElem440 *_M_finish;
	BfmeElem440 *_M_end_of_storage;
};

void BfmeVec440::push_back(const BfmeElem440 *value)
{
	if (_M_finish != _M_end_of_storage)
	{
		if (_M_finish)
			_M_finish->copyFrom(value);
		++_M_finish;
	}
	else
	{
		overflow(_M_finish, *value, reinterpret_cast<const BfmeFalse440 &>(value), 1, true);
	}
}
