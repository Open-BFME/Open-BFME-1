// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// The vector's element width does not identify its members. These placement
// constructors retain the out-of-line copy constructor each retail body calls.

struct Gen002E9E10
{
	char m_body[20];
};

class Rva002E8FC0
{
public:
	Rva002E8FC0(const Rva002E8FC0 &value);
	char m_body[20];
};

class Open2Rec134500
{
public:
	Open2Rec134500(const Open2Rec134500 &value);
	char m_body[20];
};

class Open2Rec3A4420
{
public:
	Open2Rec3A4420(const Open2Rec3A4420 &value);
	char m_body[20];
};

class Gen_003A8A70
{
public:
	Gen_003A8A70(const Gen_003A8A70 &value);
	virtual ~Gen_003A8A70();
	char m_body[16];
};

inline void *operator new(unsigned int, void *place) { return place; }
inline void operator delete(void *, void *) {}

namespace _STL
{
struct Rva00143CE0Element
{
	char m_body[20];
};

struct Rva003A5500Element
{
	char m_body[20];
};

struct Rva003B0760Element
{
	char m_body[20];
};

template <class Type>
void _Construct(Type *destination, const Type &value);

// Retail 0x00134F70 calls the copy constructor at 0x00134500 through 0x0001BCF7.
template <>
void _Construct(Rva00143CE0Element *destination, const Rva00143CE0Element &value)
{
	new (destination) Open2Rec134500(reinterpret_cast<const Open2Rec134500 &>(value));
}

// Retail 0x002EA020 calls the copy constructor at 0x002E8FC0 through 0x00036B10.
template <>
void _Construct(Gen002E9E10 *destination, const Gen002E9E10 &value)
{
	new (destination) Rva002E8FC0(reinterpret_cast<const Rva002E8FC0 &>(value));
}

// Retail 0x003A4670 calls the copy constructor at 0x003A4420 through 0x0000988B.
template <>
void _Construct(Rva003A5500Element *destination, const Rva003A5500Element &value)
{
	new (destination) Open2Rec3A4420(reinterpret_cast<const Open2Rec3A4420 &>(value));
}

// Retail 0x003A9310 calls the copy constructor at 0x003A8A70 through 0x00022AF2.
template <>
void _Construct(Rva003B0760Element *destination, const Rva003B0760Element &value)
{
	new (destination) Gen_003A8A70(reinterpret_cast<const Gen_003A8A70 &>(value));
}
}
