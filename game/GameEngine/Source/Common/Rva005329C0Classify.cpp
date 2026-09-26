// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005329C0Obj;

class Rva005329Classify
{
public:
	void classify(Rva005329C0Obj *obj, int slot);
};

class Rva005329C0
{
public:
	void wrap(Rva005329C0Obj *obj);
};

void Rva005329C0::wrap(Rva005329C0Obj *obj)
{
	reinterpret_cast<Rva005329Classify *>(this)->classify(obj, 2);
}

class Rva005329E0
{
public:
	void wrap(Rva005329C0Obj *obj);
};

void Rva005329E0::wrap(Rva005329C0Obj *obj)
{
	reinterpret_cast<Rva005329Classify *>(this)->classify(obj, 3);
}
