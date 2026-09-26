// Retail RVA 0x0034C5E0, 84 bytes.
// Vtable 0x010E7D00 and the releaseBuffer call identify the constructor
// layout, but the owning class name remains unknown.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

class BfmeStringYK
{
public:
	BfmeStringYK()
	{
		m_bfmeDataYK = 0;
	}

	~BfmeStringYK()
	{
		bfmeClearYK();
	}

	void bfmeClearYK();

	void *m_bfmeDataYK;
};

class BfmeBaseYK
{
public:
	BfmeBaseYK()
	{
	}

	~BfmeBaseYK();
	virtual void slot00();
};

class Rva0034C5E0 : public BfmeBaseYK
{
public:
	Rva0034C5E0();

	BfmeStringYK m_bfmeStrYK;
	int m_bfmeAYK;
	int m_bfmeBYK;
};

// ??0Rva0034C5E0@@QAE@XZ
Rva0034C5E0::Rva0034C5E0()
{
	m_bfmeAYK = 1;
	m_bfmeBYK = 0;
	m_bfmeStrYK.bfmeClearYK();
}
