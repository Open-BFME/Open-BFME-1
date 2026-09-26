// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Object;

class Rva0022CD00Primary
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
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
	virtual bool probe(Object *obj);
};

class Rva0022CD00Obj
{
public:
	int reserve(void *unused, Object *obj);
};

int Rva0022CD00Obj::reserve(void *unused, Object *obj)
{
	return ((Rva0022CD00Primary *)((char *)this - 0x30))->probe(obj) ? 0 : -1;
}
