// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
#include <vector>

struct Q3SortElem4
{
	void *m_item;
};

struct Gen_t_007546f0_p12cd
{
	int a[3];
	Gen_t_007546f0_p12cd();
	Gen_t_007546f0_p12cd(const Gen_t_007546f0_p12cd &);
	~Gen_t_007546f0_p12cd();
	Gen_t_007546f0_p12cd &operator=(const Gen_t_007546f0_p12cd &);
};

class Gen007558B0
{
public:
	void sortAndPrune(void);
	~Gen007558B0();

private:
	_STL::vector<Q3SortElem4> m_vec0;
	_STL::list<Gen_t_007546f0_p12cd> m_list;
	_STL::vector<Q3SortElem4> m_vec1;
	_STL::vector<Q3SortElem4> m_vec2;
};

// ??1Gen007558B0@@QAE@XZ
Gen007558B0::~Gen007558B0()
{
	sortAndPrune();
}
