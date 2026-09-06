// cl: /DNDEBUG /MD /EHsc
// Open-BFME: retail ShareBufferClass<ShaderClass> copy constructor.

void *operator new[](unsigned int size);

class ShaderClass
{
public:
	ShaderClass() : ShaderBits(0x0010441B) {}
	ShaderClass &operator=(const ShaderClass &that)
	{
		ShaderBits = that.ShaderBits;
		return *this;
	}

private:
	unsigned int ShaderBits;
};

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &that);

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
	Count(that.Count)
{
	Alignment = that.Alignment;
	if (Alignment == 0) {
		RawBuffer = new Type[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (Type *)new char[Count * sizeof(Type) + Alignment];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for (int index = 0; index < Count; ++index) {
		Array[index] = that.Array[index];
	}
}

template ShareBufferClass<ShaderClass>::ShareBufferClass(
	const ShareBufferClass<ShaderClass> &);
