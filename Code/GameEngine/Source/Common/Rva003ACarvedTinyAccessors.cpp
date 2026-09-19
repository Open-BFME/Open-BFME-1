// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva003AC4B0OffsetGetter
{
public:
	void *get();
};

void *Rva003AC4B0OffsetGetter::get()
{
	return reinterpret_cast<char *>(this) + 4;
}

#define RVA_RETURN_THIS( RVA ) \
class Rva##RVA \
{ \
public: \
	Rva##RVA *getThis(); \
}; \
Rva##RVA *Rva##RVA::getThis() \
{ \
	return this; \
}

RVA_RETURN_THIS( 003AC4E0 )
RVA_RETURN_THIS( 003AC4F0 )
RVA_RETURN_THIS( 003AC500 )
RVA_RETURN_THIS( 003AC530 )
RVA_RETURN_THIS( 003AC540 )
RVA_RETURN_THIS( 003AC550 )
RVA_RETURN_THIS( 003AC580 )
RVA_RETURN_THIS( 003AC590 )
RVA_RETURN_THIS( 003AC5C0 )
RVA_RETURN_THIS( 003AC5D0 )
RVA_RETURN_THIS( 003AC5E0 )

#undef RVA_RETURN_THIS

#define RVA_RETURN_WORD( RVA ) \
class Rva##RVA \
{ \
public: \
	unsigned int getValue() const; \
}; \
unsigned int Rva##RVA::getValue() const \
{ \
	return *reinterpret_cast<const unsigned int *>(this); \
}

RVA_RETURN_WORD( 003AC610 )
RVA_RETURN_WORD( 003AC6A0 )
RVA_RETURN_WORD( 003AC6B0 )
RVA_RETURN_WORD( 003AC6F0 )
RVA_RETURN_WORD( 003AC750 )
RVA_RETURN_WORD( 003AC760 )

#undef RVA_RETURN_WORD
