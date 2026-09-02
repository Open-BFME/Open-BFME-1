// cl: /O2 /Ob1

template <class T>
class StringBase
{
public:
	void set(const StringBase &other);

private:
	void *m_bfmeData;
};

struct BfmeSubA100
{
	void set(const BfmeSubA100 &other);
	char m_bfmeBytes[12];
};

struct BfmeElemA100
{
	StringBase<char> m_bfmeKey;
	unsigned char m_bfmeFlag;
	char m_bfmePad[3];
	BfmeSubA100 m_bfmeSub;
};

BfmeElemA100 *bfmeCopyA100(const BfmeElemA100 *first, const BfmeElemA100 *last, BfmeElemA100 *dest)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			dest->m_bfmeKey.set(first->m_bfmeKey);
			dest->m_bfmeFlag = first->m_bfmeFlag;
			dest->m_bfmeSub.set(first->m_bfmeSub);
			++first;
			++dest;
		}
		while (--count);
	}

	return dest;
}
