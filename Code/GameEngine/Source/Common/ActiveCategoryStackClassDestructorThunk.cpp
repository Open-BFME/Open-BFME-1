// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// ICF owner for DynamicVectorClass/VectorClass empty-element dtors at 0x00AFF130.
// Layout matches WW VectorClass: Vector@4, VectorMax@8, IsValid@c, IsAllocated@d.

void __cdecl operator delete(void *);

class ActiveCategoryStackClass
{
public:
	virtual ~ActiveCategoryStackClass();

protected:
	void *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool pad[2];
};

// ??1ActiveCategoryStackClass@@UAE@XZ
ActiveCategoryStackClass::~ActiveCategoryStackClass()
{
	if (Vector && IsAllocated) {
		operator delete(Vector);
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}
