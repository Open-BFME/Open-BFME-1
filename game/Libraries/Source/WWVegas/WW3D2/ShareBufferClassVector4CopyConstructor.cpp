// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc
// Open-BFME5: retail ShareBufferClass<Vector4> copy constructor.

void *operator new[](unsigned int size);
void operator delete[](void *ptr);
inline void *operator new( unsigned int, void *place ) { return place; }

#include "../WWMath/vector4.h"

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
	~ShareBufferClass( void );

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

// The destructor as sharebuf.h defines it, so the implicit-virtual COMDAT body
// this TU emits is the one every other ShareBufferClass<Vector4> TU does.
template <class Type>
ShareBufferClass<Type>::~ShareBufferClass( void )
{
	if( RawBuffer )
	{
		delete[] RawBuffer;
		RawBuffer = 0;
		Array = 0;
	}
}

template ShareBufferClass<Vector4>::ShareBufferClass(
	const ShareBufferClass<Vector4> &);
