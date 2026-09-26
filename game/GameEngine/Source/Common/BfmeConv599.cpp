// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);
};

struct BfmeSubCGF
{
	unsigned char m_bfmeHead[4];
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(void *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void xferReal(float *value);
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool *value);
};

class BfmeThingCGF
{
public:
	void bfmeTwoCGF(void *what);
	void bfmeGoCGF(void *what);
	BfmeOwnerCGF *m_bfmeOwner;
	_STL::vector<float> m_bfmeValues;
	BfmeSubCGF m_bfmeSub;
};

void bfmeThreeCGF(void *what, BfmeSubCGF *sub);

void BfmeThingCGF::bfmeGoCGF(void *what)
{
	m_bfmeOwner->bfmeOneCGF(what);
	bfmeTwoCGF(what);
	bfmeThreeCGF(what, &m_bfmeSub);
}

// ?bfmeTwoCGF@BfmeThingCGF@@QAEXPAX@Z
void BfmeThingCGF::bfmeTwoCGF(void *what)
{
	Xfer *xfer = static_cast<Xfer *>(what);
	int count = (int)m_bfmeValues.size();
	xfer->xferInt(&count);
	if (xfer->isSaving())
	{
		for (_STL::vector<float>::iterator current = m_bfmeValues.begin();
			current != m_bfmeValues.end(); ++current)
		{
			float value = *current;
			xfer->xferReal(&value);
		}
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			float value;
			xfer->xferReal(&value);
			m_bfmeValues.push_back(value);
		}
	}
}
