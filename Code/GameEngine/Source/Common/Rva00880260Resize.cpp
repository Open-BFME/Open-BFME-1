// cl: /O2 /Ob0 /G6

struct BfmeTail60
{
	char *m_p;
	void release();
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTail60 m_1C;
	char m_20;
	char m_pad[3];
};

class BfmeVec60
{
public:
	void resize(unsigned n, BfmeElem60 value);
	void erase(BfmeElem60 *first, BfmeElem60 *last);
	void insert(BfmeElem60 *pos, unsigned count, const BfmeElem60 &value);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

void BfmeVec60::resize(unsigned n, BfmeElem60 value)
{
	if (n < (unsigned)(_M_finish - _M_start))
	{
		erase(_M_start + n, _M_finish);
		value.m_1C.release();
	}
	else
	{
		insert(_M_finish, n - (unsigned)(_M_finish - _M_start), value);
		value.m_1C.release();
	}
}
