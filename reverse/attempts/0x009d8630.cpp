// ??0Gen_009D83D0@@QAE@XZ
// partial score=0.75 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Clean C++ conversion of the two-map constructor at retail RVA 0x009D8630.

#include <hash_map>

struct Gen_t_009d80b0_p12cd
{
	int a[3];
	Gen_t_009d80b0_p12cd();
	Gen_t_009d80b0_p12cd(const Gen_t_009d80b0_p12cd &);
	~Gen_t_009d80b0_p12cd();
	Gen_t_009d80b0_p12cd &operator=(const Gen_t_009d80b0_p12cd &);
};

struct Gen_t_009d8120_p12cd
{
	int a[3];
	Gen_t_009d8120_p12cd();
	Gen_t_009d8120_p12cd(const Gen_t_009d8120_p12cd &);
	~Gen_t_009d8120_p12cd();
	Gen_t_009d8120_p12cd &operator=(const Gen_t_009d8120_p12cd &);
};

class Gen_009D83D0
{
public:
	Gen_009D83D0();
	virtual ~Gen_009D83D0();

private:
	void *m_a;
	bool m_flag;
	void *m_b;
	void *m_c;
	void *m_d;
	_STL::hash_map<int, Gen_t_009d80b0_p12cd> m_map1;
	_STL::hash_map<int, Gen_t_009d8120_p12cd> m_map2;
};

Gen_009D83D0::Gen_009D83D0()
{
	m_a = 0;
	m_flag = false;
	m_b = 0;
	m_c = 0;
	m_d = 0;
}

Gen_009D83D0::~Gen_009D83D0()
{
}
