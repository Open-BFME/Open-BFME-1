// ?rva00883160@@YAPAVRva00883160Debug@@PAV1@PAURva00883160Table@@@Z
// Address-derived stack-frame formatter at retail 0x00883160.  The
// Rva008830F0 neighbor proves the complete debug stream interface, including
// v38(const char *); this source emits no numeric retail vtable address.

class DebugStackwalk
{
public:
	class Signature
	{
	public:
		static void GetSymbol(unsigned address, char *buffer, unsigned size);
	};
};

class Rva00883160Debug
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
	virtual Rva00883160Debug *v30(unsigned);
	virtual void v34();
	virtual Rva00883160Debug *v38(const char *);
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual Rva00883160Debug *v50(void *, int);
};

struct Rva00883160Table
{
	unsigned count;
	unsigned *addresses;
};

Rva00883160Debug *rva00883160(Rva00883160Debug *debug, Rva00883160Table *table)
{
	if (table->count != 0)
	{
		unsigned index = 0;
		if (index < table->count)
		{
			char buffer[512];
			do
			{
				DebugStackwalk::Signature::GetSymbol(table->addresses[index], buffer, 0x200);
				debug->v38("\t")->v38(buffer)->v38("\n");
				++index;
			} while (index < table->count);
		}
	}
	else
	{
		debug->v38("\t(no stack)\n");
	}
	return debug;
}
