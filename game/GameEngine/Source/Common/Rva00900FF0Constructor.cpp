// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The constructor at retail RVA 0x009002C0 initializes the render object
// whose destructor uses the vtable at 0x01139068.

#include <string.h>
#include <vector>

class StringClass
{
public:
	StringClass(const char *string);
	~StringClass();
	StringClass &operator=(const char *string);
	static char *m_EmptyString;
	char *m_Buffer;

private:
	void Get_String(int length, bool is_temp);
};

inline StringClass::StringClass(const char *string)
	: m_Buffer(m_EmptyString)
{
	int len = string ? (int)strlen(string) : 0;
	if (len > 0)
		Get_String(len + 1, false);
	*this = string;
}

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00900FF0InnerVector
{
public:
	Rva00900FF0InnerVector(int allocator);
	Rva00900FF0InnerVector(const Rva00900FF0InnerVector &source);

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??0Rva00900FF0InnerVector@@QAE@H@Z=?d_008ffa50@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00900FF0InnerVector@@QAE@ABV0@@Z=?d_008ffb80@@YAXXZ")

class Rva00900FF0VecOfVec
{
public:
	Rva00900FF0VecOfVec(int allocator);
	Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source);
	~Rva00900FF0VecOfVec();

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??0Rva00900FF0VecOfVec@@QAE@H@Z=?d_008ffa50@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z=?d_008ffb80@@YAXXZ")

class Gen_ve_001f9520
{
};

typedef _STL::vector<Gen_ve_001f9520 *> Rva00900FF0SourceVector;
typedef _STL::vector<Gen_ve_001f9520 *> Rva00900FF0VectorHolder;

class Rva00900FF0 : public GenBase009EB7D0
{
public:
    Rva00900FF0(
        const char *first,
        const char *second,
        int field64,
        int field68,
        Rva00900FF0VecOfVec vec40,
        Rva00900FF0VecOfVec vec4c,
        Rva00900FF0SourceVector source);
    virtual ~Rva00900FF0();

private:
	StringClass m_str14;
	StringClass m_str18;
	Rva00900FF0VecOfVec m_vec1c;
	Rva00900FF0VecOfVec m_vec28;
	Rva00900FF0VecOfVec m_vec34;
	Rva00900FF0VecOfVec m_vec40;
    Rva00900FF0VecOfVec m_vec4c;
	Rva00900FF0VectorHolder m_vector58;
    int m_field64;
    int m_field68;
    int m_field6c;
    void *m_countedPtr70;
};

Rva00900FF0::Rva00900FF0(
    const char *first,
    const char *second,
    int field64,
    int field68,
    Rva00900FF0VecOfVec vec40,
    Rva00900FF0VecOfVec vec4c,
    Rva00900FF0SourceVector source)
    : GenBase009EB7D0(),
      m_str14(first),
      m_str18(second),
      m_vec1c(0),
      m_vec28(0),
      m_vec34(0),
      m_vec40(vec40),
      m_vec4c(vec4c),
      m_vector58(source),
      m_field64(field64),
      m_field68(field68),
      m_field6c(0),
      m_countedPtr70(0)
{
}
