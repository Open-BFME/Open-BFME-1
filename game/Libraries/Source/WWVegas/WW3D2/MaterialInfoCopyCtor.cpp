// cl: /DNDEBUG /MD /EHsc
// BFME MaterialInfoClass copy constructor, retail 0x00930E00 / 352 bytes.
// Uses the layout and vector vtable identities already established by
// MaterialInfoClassCtor.cpp. Upstream matinfo.cpp clones vertex materials;
// retail spells Clone out as default construction plus assignment, allocating
// 0x6c bytes. Texture handles are copied via the base-vector assignment.
// MaterialVector::Add follows WWLib/vector.h: increment the count before the
// element store, preserving the distinct old and new indices.

class VertexMaterialClass {
public:
 VertexMaterialClass();
 VertexMaterialClass &operator=(const VertexMaterialClass &);
 char storage[0x6c];
};
void *__cdecl operator new(unsigned int);

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim();
 TextureVectorBaseCtorShim &operator=(const TextureVectorBaseCtorShim &);

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

class MaterialVector {
public:
 __forceinline MaterialVector()
 {
  Vector = 0;
  VectorMax = 0;
  IsValid = true;
  IsAllocated = false;
  Vtable = 0x0113c614;
  GrowthStep = 10;
  ActiveCount = 0;
 }
 ~MaterialVector();
 int Count() const { return ActiveCount; }
 VertexMaterialClass *operator[](int i) const { return Vector[i]; }
 bool Add(VertexMaterialClass *const &value) {
  // VectorClass slots: destructor, equality, Resize.
  struct Dispatch {
   virtual void DestructorSlot();
   virtual void EqualitySlot();
   virtual bool Resize(int, VertexMaterialClass **);
  };
  if(ActiveCount>=VectorMax) {
   if((!IsAllocated && VectorMax) || GrowthStep<=0) return false;
   if(!((Dispatch *)this)->Resize(VectorMax+GrowthStep,0)) return false;
  }
  int index = ActiveCount++;
  Vector[index] = value;
  return true;
 }
private:
 unsigned Vtable; VertexMaterialClass **Vector; int VectorMax;
 bool IsValid, IsAllocated; char pad[2]; int ActiveCount, GrowthStep;
};

class TextureVector : public TextureVectorBaseCtorShim
{
public:
	__forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)this = 0x0113c62c;
  GrowthStep = 10;
  ActiveCount = 0;
	}
 ~TextureVector();
 TextureVector &operator=(const TextureVector &other) {
  TextureVectorBaseCtorShim::operator=(other);
  ActiveCount = other.ActiveCount;
  GrowthStep = other.GrowthStep;
  return *this;
 }

private:
	int ActiveCount, GrowthStep;
};

class RefCountClass
{
public:
	RefCountClass() : Count(1) {}
	virtual void Delete_This() { delete this; }

protected:
	virtual ~RefCountClass() {}

private:
	int Count;
};

class MaterialInfoClass : public RefCountClass
{
public:
	MaterialInfoClass(const MaterialInfoClass &);
	virtual ~MaterialInfoClass();

private:
	MaterialVector VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::MaterialInfoClass(const MaterialInfoClass &src)
{
 for (int i=0; i<src.VertexMaterials.Count(); ++i) {
  VertexMaterialClass *old = src.VertexMaterials[i];
  VertexMaterialClass *material = new VertexMaterialClass();
  *material = *old;
  VertexMaterials.Add(material);
 }
 Textures = src.Textures;
}
