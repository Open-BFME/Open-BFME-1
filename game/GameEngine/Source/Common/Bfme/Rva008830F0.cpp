// cl: /DNDEBUG /MD /EHs-c-

class Rva008830F0Debug
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual Rva008830F0Debug *v30(unsigned);
	virtual void v34();
	virtual Rva008830F0Debug *v38(const char *);
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual Rva008830F0Debug *v50(void *a, int b);
};

struct Rva008830F0Table
{
	int index;
	unsigned field4;
	const char **names;
	int count;
};

Rva008830F0Debug *d_008830f0(Rva008830F0Debug *dbg, Rva008830F0Table *tab)
{
	const char *name;
	if (tab->index >= 0 && tab->index < tab->count)
		name = tab->names[tab->index];
	else
		name = "unknown";
	dbg->v50((void *)"0x", 0x10);
	dbg->v30(tab->field4)->v38("[")->v38(name)->v38("]");
	return dbg;
}
