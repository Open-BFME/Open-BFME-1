// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_005e97b0.asm (?d_00609560@@YAXXZ).
// stdcall walk: recount via vslot 0x6C, get via 0x74, cdecl release then dec +4.

class Rva00609560Item
{
public:
	virtual void destroy();
	int m_refs;
};

class Rva00609560Bag
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual int count();
	virtual void v28();
	virtual Rva00609560Item *get(int i);
};

void __cdecl Rva00739B30(Rva00609560Item *item, int flag);

void __stdcall Rva00609560(Rva00609560Bag *bag)
{
	int i = 0;
	if (bag->count() <= 0)
		return;
	do
	{
		Rva00609560Item *item = bag->get(i);
		if (item)
		{
			Rva00739B30(item, 0);
			if (--item->m_refs == 0)
				item->destroy();
		}
		++i;
	} while (i < bag->count());
}
