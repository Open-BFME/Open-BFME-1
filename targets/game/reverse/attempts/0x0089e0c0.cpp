// ?rva0089E0C0@EAStringC@@QBE?AV1@ABV1@@Z
// partial score=0.9826 date=2026-10-03
// cl: /O2 /DNDEBUG /MD /EHsc
// Bank: 0x0089E0C0, 287 bytes; only terminator addressing at +0xCF/+0xD3 differs.
// Retail clears the SOURCE hash, not the result hash. The visible native reserve
// constructor (existing EAStringCReserveCtor.cpp) removes two extra pointer reloads.
// Its 93-byte emission probes exact; this bank is not strictly reference-verified.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class EAStringC {
public:
class StringDataC
{
public:
	unsigned short m_uRefCount;
	unsigned short m_uSize;
	unsigned short m_uMaxSize;
	unsigned short m_uHash;
};


 __declspec(noinline) EAStringC(unsigned int nSize);
 EAStringC(const EAStringC &other) : m_data(other.m_data) { ++m_data->m_uRefCount; }
 ~EAStringC() { StringDataC *data=m_data; if (--data->m_uRefCount==0) g_rva01337A30AllocPair->free(data); }
 EAStringC rva0089E0C0(const EAStringC &other) const;
 char *GetInternalBuffer() const { return reinterpret_cast<char *>(m_data)+sizeof(StringDataC); }
private:
 StringDataC *m_data;
};

struct BfmeAllocVKJ { void *(__cdecl *allocate)(unsigned int); void (__cdecl *free)(void *); };
extern BfmeAllocVKJ *g_bfmeAllocVKJ;
extern EAStringC::StringDataC g_rva012D5298Empty;
EAStringC::EAStringC(unsigned int nSize)
{
 if (nSize) {
  unsigned int alloc = (nSize + 12) & ~3u;
  m_data = (StringDataC *)g_bfmeAllocVKJ->allocate(alloc);
  m_data->m_uRefCount = 1;
  m_data->m_uMaxSize = (unsigned short)(alloc - 9);
  m_data->m_uSize = 0;
  m_data->m_uHash = 0;
  reinterpret_cast<char *>(m_data)[sizeof(StringDataC)] = 0;
 } else {
  m_data = &g_rva012D5298Empty;
  ++g_rva012D5298Empty.m_uRefCount;
 }
}


// Address-derived concatenation method; original public spelling is unproven.
EAStringC EAStringC::rva0089E0C0(const EAStringC &other) const
{
	unsigned int thisSize = m_data->m_uSize;
	if (thisSize == 0)
		return other;

	unsigned int otherSize = other.m_data->m_uSize;
	if (otherSize == 0)
		return *this;

	EAStringC result(thisSize + otherSize);
	EAStringC::StringDataC *resultData = result.m_data;
	memcpy(reinterpret_cast<char *>(resultData) + sizeof(EAStringC::StringDataC),
		GetInternalBuffer(), thisSize);
	memcpy(reinterpret_cast<char *>(resultData) + sizeof(EAStringC::StringDataC) + thisSize,
		other.GetInternalBuffer(), otherSize);
	reinterpret_cast<char *>(resultData)[sizeof(EAStringC::StringDataC) + thisSize + otherSize] = 0;
	resultData->m_uSize = thisSize + otherSize;
	m_data->m_uHash = 0;
	return result;
}
