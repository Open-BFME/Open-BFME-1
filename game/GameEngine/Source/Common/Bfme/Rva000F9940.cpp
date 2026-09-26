// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

// Retail 0x000F9940 (102 bytes).  This is a no-argument member of the same
// 0x60-byte record vector used by the matched 0x000F94B0 accessor and the
// 0x000F9670 lookup.  Its first call and every loop call load the same global
// at 0x012F1028.  The call targets are bodies at 0x003C3AC0 and 0x003C3B50:
// both receive that exact global object.  The former passes its +0x68/+0x6C
// vector pair to the range helper; the latter uses +0x68/+0x6C/+0x70 as one
// three-pointer vector and appends the supplied 0x60-byte record.  The retail
// method names are unavailable, so the single proven owner uses neutral RVA
// method names rather than unrelated receiver classes or semantic guesses.

struct P6Elem003C3B50
{
	unsigned char m_opaque[0x60];
};

class BfmeRecordVector
{
public:
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	P6Elem003C3B50 &operator[](unsigned int index)
	{
		return m_begin[index];
	}

private:
	P6Elem003C3B50 *m_begin;
	P6Elem003C3B50 *m_end;
	P6Elem003C3B50 *m_storageEnd;
};

class Glo012F1028Type
{
public:
	void rva003C3AC0();
	void rva003C3B50(const P6Elem003C3B50 *value);

private:
	unsigned char m_opaque00[0x68];
	BfmeRecordVector m_records;
};

extern Glo012F1028Type *Glo012F1028;

class BfmeVecVLH
{
public:
	void rva000F9940();

private:
	int m_opaque00;
	BfmeRecordVector m_records;
};

// ?rva000F9940@BfmeVecVLH@@QAEXXZ
void BfmeVecVLH::rva000F9940()
{
	Glo012F1028->rva003C3AC0();

	for (unsigned int index = 0; index < m_records.size(); ++index)
	{
		Glo012F1028->rva003C3B50(&m_records[index]);
	}
}
