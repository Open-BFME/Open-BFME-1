// cl: /EHsc
// stlport
// The retail body is an owning destructor: it frees the auxiliary buffer,
// then destroys two 12-byte-value hash maps and an AsciiString member.

#include <algorithm>
#include <hash_map>

class AsciiString
{
public:
	~AsciiString();
};

struct Gen_t_00786db0_p12cd
{
	int a[3];
	Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd(const Gen_t_00786db0_p12cd &);
	~Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd &operator=(const Gen_t_00786db0_p12cd &);
};

struct Gen_t_00786e70_p12cd
{
	int a[3];
	Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd(const Gen_t_00786e70_p12cd &);
	~Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd &operator=(const Gen_t_00786e70_p12cd &);
};

bool operator==(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);
bool operator<(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);
bool operator==(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);
bool operator<(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);

typedef _STL::pair<const int, Gen_t_00786db0_p12cd> Rva00787C20PairA;
typedef _STL::pair<const int, Gen_t_00786e70_p12cd> Rva00787C20PairB;
typedef _STL::hash_map<int, Gen_t_00786db0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairA> > Rva00787C20MapA;
typedef _STL::hash_map<int, Gen_t_00786e70_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairB> > Rva00787C20MapB;

void __cdecl Rva00787C20CleanupA(Rva00787C20PairA &);
void __cdecl Rva00787C20CleanupB(Rva00787C20PairB &);

class Rva00787C20
{
public:
	~Rva00787C20();

private:
	AsciiString m_name;
	void *m_buffer;
	Rva00787C20MapA m_first;
	Rva00787C20MapB m_second;
};

Rva00787C20::~Rva00787C20()
{
	delete [] (char *)m_buffer;
	m_buffer = 0;
	_STL::for_each(m_first.begin(), m_first.end(), Rva00787C20CleanupA);
	_STL::for_each(m_second.begin(), m_second.end(), Rva00787C20CleanupB);
}
