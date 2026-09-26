// cl: /O2 /Ob0 /G6

struct BfmeTail50
{
	void copyFrom(const BfmeTail50 *src);
};

struct BfmeElem50
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTail50 m_0C;
};

struct BfmeFalse50
{
};

class BfmeVec50
{
public:
	void push_back(const BfmeElem50 *value);
	void overflow(BfmeElem50 *pos, const BfmeElem50 &value,
		const BfmeFalse50 &, unsigned fill, bool atEnd);

	BfmeElem50 *_M_start;
	BfmeElem50 *_M_finish;
	BfmeElem50 *_M_end_of_storage;
};

void BfmeVec50::push_back(const BfmeElem50 *value)
{
	if (_M_finish != _M_end_of_storage)
	{
		BfmeElem50 *f = _M_finish;
		if (f)
		{
			const BfmeElem50 *v = value;
			f->m_00 = v->m_00;
			f->m_04 = v->m_04;
			f->m_08 = v->m_08;
			f->m_0C.copyFrom(&v->m_0C);
		}
		++_M_finish;
	}
	else
	{
		overflow(_M_finish, *value, reinterpret_cast<const BfmeFalse50 &>(value), 1, true);
	}
}
