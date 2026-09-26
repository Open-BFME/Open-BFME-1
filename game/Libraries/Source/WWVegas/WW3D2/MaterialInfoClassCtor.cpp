// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of MaterialInfoClass::MaterialInfoClass().

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

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

class MaterialVector
{
public:
	__forceinline MaterialVector()
	{
		unsigned char *self = (unsigned char *)this;
		*(unsigned int *)(self + 4) = 0;
		*(unsigned int *)(self + 8) = 0;
		*(unsigned char *)(self + 0x0c) = 1;
		*(unsigned char *)(self + 0x0d) = 0;
		*(unsigned int *)self = 0x0113c614;
		*(unsigned int *)(self + 0x14) = 10;
		*(unsigned int *)(self + 0x10) = 0;
	}
	~MaterialVector();

private:
	unsigned char m_data[0x18];
};

class TextureVector : public TextureVectorBaseCtorShim
{
public:
	__forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
		*(unsigned int *)this = 0x0113c62c;
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
	}
	~TextureVector();

private:
	unsigned char m_data[8];
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
	MaterialInfoClass();
	virtual ~MaterialInfoClass();

private:
	MaterialVector VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::MaterialInfoClass()
{
}
