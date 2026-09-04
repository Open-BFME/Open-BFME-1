// ?wrap@Rva007F5FB0@@QAEHPAX000@Z
// partial score=0.72 date=2026-09-02
// cl: /O2
// 0x007F5FB0: thiscall four-arg wrapper that calls virtual slot 0x80 with a
// zero inserted between the second and third arguments.

class Rva007F5FB0
{
public:
	virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
	virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
	virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
	virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
	virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
	virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
	virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
	virtual int v28(); virtual int v29(); virtual int v30(); virtual int v31();
	virtual void slot32(void *a, void *b, bool z, void *c, void *d);

	void wrap(void *a, void *b, void *c, void *d) throw();
};

void Rva007F5FB0::wrap(void *a, void *b, void *c, void *d) throw()
{
	void *last = d;
	void *next = c;
	bool z = false;
	void *prior = b;
	void *first = a;
	slot32(first, prior, z, next, last);
}
