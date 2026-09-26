// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class BfmeMgrF1D
{
public:
	void *registerObj(void *field);
};

extern BfmeMgrF1D *g_mgr12EF1D8;

class BfmeSub942D
{
public:
	void *bfmeCall942D(void *a);

private:
	struct BfmeElem942D
	{
		char m_bfmePad942D[0x60];
	};

	char m_bfmePad942D[4];

	class BfmeArray942D
	{
	public:
		BfmeElem942D *begin()
		{
			return m_bfmeBegin942D;
		}

		BfmeElem942D *end()
		{
			return m_bfmeEnd942D;
		}

		unsigned int size()
		{
			return (unsigned int)(end() - begin());
		}

	private:
		BfmeElem942D *m_bfmeBegin942D;
		BfmeElem942D *m_bfmeEnd942D;
	} m_bfmeElements942D;

};

void *BfmeSub942D::bfmeCall942D(void *a)
{
	int index = (int)a;
	if ((unsigned int)index < m_bfmeElements942D.size())
		return g_mgr12EF1D8->registerObj(
			m_bfmeElements942D.begin() + index);
	return 0;
}
