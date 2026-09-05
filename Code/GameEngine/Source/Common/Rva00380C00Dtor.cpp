// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: unidentified Overridable subclass destructor at 0x00380C00.
// This body resets to the single-slot Overridable table at0x0107FCB0.
// No derived-table identity is inferred from the neighbouring constructor.
// The inherited base destructor matches31B at94940; its deleting wrapper
// is emitted with the same behavior inlined, and receives no byte credit.

void __cdecl bfmeFreeScalar(void *block);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class AsciiString
{
public:
	~AsciiString(void);

private:
	void *m_data;
};

class Rva00026AB2Vec12
{
public:
	~Rva00026AB2Vec12(void);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Gen_uwm_000393d8
{
public:
	~Gen_uwm_000393d8(void);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class BfmeVecMemberR
{
public:
	~BfmeVecMemberR(void)
	{
		int *start = m_bfmeStart;
		if (start)
			bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
	}

private:
	int *m_bfmeStart;
	int *m_bfmeFinish;
	int *m_bfmeEnd;
};

class Overridable
{
public:
	Overridable *m_nextOverride;

	virtual ~Overridable(void)
	{
		if (m_nextOverride)
			delete m_nextOverride;
		m_nextOverride = 0;
	}

private:
	bool m_isOverride;
};

struct Rva00380C00TailStrings
{
	AsciiString m_str78;
	AsciiString m_str7c;
};

class __declspec(novtable) Rva00380C00Object : public Overridable
{
protected:
	virtual ~Rva00380C00Object(void);

private:
	AsciiString m_name;
	int m_pad10;
	int m_pad14;
	int m_pad18;
	Rva00026AB2Vec12 m_vec1c;
	Rva00026AB2Vec12 m_vec28;
	Gen_uwm_000393d8 m_vec34;
	int m_pad40;
	BfmeVecMemberR m_vec44;
	char m_pad50[0x28];
	Rva00380C00TailStrings m_tail;
};

// ??1Rva00380C00Object@@MAE@XZ
Rva00380C00Object::~Rva00380C00Object(void)
{
}
