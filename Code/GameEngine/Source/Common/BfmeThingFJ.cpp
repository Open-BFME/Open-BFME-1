// A run told three things: walk the pointer vector at this+0 / this+4
// and call vtable slot 2 on each item.

class BfmeItemFJ
{
public:
	virtual void bfmeSpare000FJ(void) = 0;
	virtual void bfmeSpare001FJ(void) = 0;
	virtual void bfmeDoFJ(void *a, void *b, void *c) = 0;
};

class BfmeThingFJ
{
public:
	void bfmeTellFJ(void *a, void *b, void *c);

private:
	BfmeItemFJ **m_bfmeBegin;
	BfmeItemFJ **m_bfmeEnd;
};

void BfmeThingFJ::bfmeTellFJ(void *a, void *b, void *c)
{
	BfmeItemFJ **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoFJ(a, b, c);

		++at;
	}
}
