// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived recovery, retail 0x0014A6C0, 311 bytes.
//
// No callers are converted yet, so the real class name and field types are
// unknown. The body is mechanical: given a query interface pointer taken
// from the stack, it asks the interface (via a bool getter at vtbl+0xC)
// whether data is present. If not, it fills a 2-byte local with {1,1} and
// hands it to a fallback getter at vtbl+0x28. Otherwise it walks 22 fields
// of `this` at fixed 4-byte-stride offsets (0x04..0x60, with two 4-byte
// gaps at 0x48 and 0x58) copying through three getters at vtbl+0x6C
// (most fields), vtbl+0x78 (offsets 0x0C/0x10) and vtbl+0x74 (offsets
// 0x14/0x3C/0x40/0x44), then a final getter at vtbl+0x8C for the field at
// 0x64. Landed under an address-derived name; identity of the class and
// the query interface is an open question.

class BfmeQuery0014A6C0
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual bool hasData();				// +0x0C
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void getDefault(void *out);			// +0x28
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5C();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void getA(void *out);				// +0x6C
	virtual void v70();
	virtual void getC(void *out);				// +0x74
	virtual void getB(void *out);				// +0x78
	virtual void v7C();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void getLast(void *out);			// +0x8C
};

class Rva0014A6C0Filler
{
public:
	void populateFromQuery(BfmeQuery0014A6C0 *query);
};

// ?populateFromQuery@Rva0014A6C0Filler@@QAEXPAVBfmeQuery0014A6C0@@@Z
void Rva0014A6C0Filler::populateFromQuery(BfmeQuery0014A6C0 *query)
{
	char *base = reinterpret_cast<char *>(this);

	if (query->hasData())
	{
		query->getA(base + 0x04);
		query->getA(base + 0x08);
		query->getB(base + 0x0C);
		query->getB(base + 0x10);
		query->getC(base + 0x14);
		query->getA(base + 0x18);
		query->getA(base + 0x1C);
		query->getA(base + 0x20);
		query->getA(base + 0x24);
		query->getA(base + 0x28);
		query->getA(base + 0x2C);
		query->getA(base + 0x30);
		query->getA(base + 0x34);
		query->getA(base + 0x38);
		query->getC(base + 0x3C);
		query->getC(base + 0x40);
		query->getC(base + 0x44);
		query->getA(base + 0x4C);
		query->getA(base + 0x50);
		query->getA(base + 0x54);
		query->getA(base + 0x5C);
		query->getA(base + 0x60);
		query->getLast(base + 0x64);
		return;
	}

	char fallback[2];
	fallback[0] = 1;
	fallback[1] = 1;
	query->getDefault(fallback);
}
