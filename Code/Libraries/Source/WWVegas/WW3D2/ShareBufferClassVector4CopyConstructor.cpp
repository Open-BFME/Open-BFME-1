// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail ShareBufferClass<Vector4> copy constructor.

void *operator new[](unsigned int size);
inline void *operator new( unsigned int, void *place ) { return place; }

class Vector4
{
public:
	Vector4();
	Vector4 &operator=( const Vector4 &that )
	{
		X = that.X;
		Y = that.Y;
		Z = that.Z;
		W = that.W;
		return *this;
	}

private:
	float X;
	float Y;
	float Z;
	float W;
};

class RefCountClass
{
public:
	RefCountClass() : NumRefs( 1 ) {}
	RefCountClass( const RefCountClass & ) : NumRefs( 1 ) {}
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
	ShareBufferClass( const ShareBufferClass &that );

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass( const ShareBufferClass<Type> &that ) :
	Count( that.Count )
{
	Alignment = that.Alignment;
	if( Alignment == 0 )
	{
		RawBuffer = new Type[ Count ];
		Array = RawBuffer;
	}
	else
	{
		RawBuffer = (Type *)new char[ Count * sizeof( Type ) + Alignment ];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for( int index = 0; index < Count; ++index )
	{
		Array[ index ] = that.Array[ index ];
	}
}

template ShareBufferClass<Vector4>::ShareBufferClass(
	const ShareBufferClass<Vector4> &);
