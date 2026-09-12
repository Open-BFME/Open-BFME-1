// Rva007F5FB0::wrap at retail RVA 0x007F5FB0 (36 bytes).
// A zero-initialized one-dword value is passed as the third slot-32 argument;
// its aggregate lifetime reproduces retail's ESI argument shuttle.
// cl: /O2

struct Rva007F5FB0Zero
{
	int value;
};

class Rva007F5FB0
{
public:
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual int v03();
	virtual int v04();
	virtual int v05();
	virtual int v06();
	virtual int v07();
	virtual int v08();
	virtual int v09();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int v31();
	virtual void slot32(
		void *a, void *b, Rva007F5FB0Zero z, void *c, void *d);

	virtual void wrap(void *a, void *b, void *c, void *d) throw();
};

void Rva007F5FB0::wrap(void *a, void *b, void *c, void *d) throw()
{
	Rva007F5FB0Zero z = { 0 };
	slot32(a, b, z, c, d);
}
