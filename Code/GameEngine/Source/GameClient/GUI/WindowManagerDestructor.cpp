// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <hash_map>

// These payload declarations describe the eight STLport hash maps that the
// destructor releases. Their existing template instantiations provide the
// eight retail destructor bodies called below.
struct Gen_t_0046aab0_p12cd
{
	int a[3];
	Gen_t_0046aab0_p12cd();
	Gen_t_0046aab0_p12cd(const Gen_t_0046aab0_p12cd &);
	~Gen_t_0046aab0_p12cd();
	Gen_t_0046aab0_p12cd &operator=(const Gen_t_0046aab0_p12cd &);
};
bool operator==(const Gen_t_0046aab0_p12cd &, const Gen_t_0046aab0_p12cd &);
bool operator<(const Gen_t_0046aab0_p12cd &, const Gen_t_0046aab0_p12cd &);
typedef _STL::pair<const int, Gen_t_0046aab0_p12cd> TgPair_hash_int_p12cd_0046aab0;

struct Gen_t_0046ab60_p12cd
{
	int a[3];
	Gen_t_0046ab60_p12cd();
	Gen_t_0046ab60_p12cd(const Gen_t_0046ab60_p12cd &);
	~Gen_t_0046ab60_p12cd();
	Gen_t_0046ab60_p12cd &operator=(const Gen_t_0046ab60_p12cd &);
};
bool operator==(const Gen_t_0046ab60_p12cd &, const Gen_t_0046ab60_p12cd &);
bool operator<(const Gen_t_0046ab60_p12cd &, const Gen_t_0046ab60_p12cd &);
typedef _STL::pair<const int, Gen_t_0046ab60_p12cd> TgPair_hash_int_p12cd_0046ab60;

struct Gen_t_0046b590_p12cd
{
	int a[3];
	Gen_t_0046b590_p12cd();
	Gen_t_0046b590_p12cd(const Gen_t_0046b590_p12cd &);
	~Gen_t_0046b590_p12cd();
	Gen_t_0046b590_p12cd &operator=(const Gen_t_0046b590_p12cd &);
};
bool operator==(const Gen_t_0046b590_p12cd &, const Gen_t_0046b590_p12cd &);
bool operator<(const Gen_t_0046b590_p12cd &, const Gen_t_0046b590_p12cd &);
typedef _STL::pair<const int, Gen_t_0046b590_p12cd> TgPair_hash_int_p12cd_0046b590;

struct Gen_t_0046b960_p12cd
{
	int a[3];
	Gen_t_0046b960_p12cd();
	Gen_t_0046b960_p12cd(const Gen_t_0046b960_p12cd &);
	~Gen_t_0046b960_p12cd();
	Gen_t_0046b960_p12cd &operator=(const Gen_t_0046b960_p12cd &);
};
bool operator==(const Gen_t_0046b960_p12cd &, const Gen_t_0046b960_p12cd &);
bool operator<(const Gen_t_0046b960_p12cd &, const Gen_t_0046b960_p12cd &);
typedef _STL::pair<const int, Gen_t_0046b960_p12cd> TgPair_hash_int_p12cd_0046b960;

struct Gen_t_0046d1e0_p12cd
{
	int a[3];
	Gen_t_0046d1e0_p12cd();
	Gen_t_0046d1e0_p12cd(const Gen_t_0046d1e0_p12cd &);
	~Gen_t_0046d1e0_p12cd();
	Gen_t_0046d1e0_p12cd &operator=(const Gen_t_0046d1e0_p12cd &);
};
bool operator==(const Gen_t_0046d1e0_p12cd &, const Gen_t_0046d1e0_p12cd &);
bool operator<(const Gen_t_0046d1e0_p12cd &, const Gen_t_0046d1e0_p12cd &);
typedef _STL::pair<const int, Gen_t_0046d1e0_p12cd> TgPair_hash_int_p12cd_0046d1e0;

struct Gen_t_0046d3b0_p12cd
{
	int a[3];
	Gen_t_0046d3b0_p12cd();
	Gen_t_0046d3b0_p12cd(const Gen_t_0046d3b0_p12cd &);
	~Gen_t_0046d3b0_p12cd();
	Gen_t_0046d3b0_p12cd &operator=(const Gen_t_0046d3b0_p12cd &);
};
bool operator==(const Gen_t_0046d3b0_p12cd &, const Gen_t_0046d3b0_p12cd &);
bool operator<(const Gen_t_0046d3b0_p12cd &, const Gen_t_0046d3b0_p12cd &);
typedef _STL::pair<const int, Gen_t_0046d3b0_p12cd> TgPair_hash_int_p12cd_0046d3b0;

struct Gen_t_0046d570_p12cd
{
	int a[3];
	Gen_t_0046d570_p12cd();
	Gen_t_0046d570_p12cd(const Gen_t_0046d570_p12cd &);
	~Gen_t_0046d570_p12cd();
	Gen_t_0046d570_p12cd &operator=(const Gen_t_0046d570_p12cd &);
};
bool operator==(const Gen_t_0046d570_p12cd &, const Gen_t_0046d570_p12cd &);
bool operator<(const Gen_t_0046d570_p12cd &, const Gen_t_0046d570_p12cd &);
typedef _STL::pair<const int, Gen_t_0046d570_p12cd> TgPair_hash_int_p12cd_0046d570;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void loadIniFilesFromLegend() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

private:
	char m_name[4];
};

class WindowManager;
extern WindowManager *g_theWindowManager;

typedef _STL::hash_map<int, Gen_t_0046d1e0_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046d1e0> > MapD1E0;
typedef _STL::hash_map<int, Gen_t_0046d3b0_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046d3b0> > MapD3B0;
typedef _STL::hash_map<int, Gen_t_0046d570_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046d570> > MapD570;
typedef _STL::hash_map<int, Gen_t_0046b590_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046b590> > MapB590;
typedef _STL::hash_map<int, Gen_t_0046aab0_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046aab0> > MapAAB0;
typedef _STL::hash_map<int, Gen_t_0046ab60_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046ab60> > MapAB60;
typedef _STL::hash_map<int, Gen_t_0046b960_p12cd,
	_STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<TgPair_hash_int_p12cd_0046b960> > MapB960;

class BfmeVector
{
public:
	~BfmeVector()
	{
		int *start = m_start;
		if (start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>((m_end - start) * 4);
			if (bytes > 0x80)
				::operator delete(start);
			else
				_STL::__node_alloc<true, 0>::deallocate(start, bytes);
		}
	}

	int *m_start;
	int *m_finish;
	int *m_end;
};

extern void __cdecl j_00018246();
extern void __cdecl j_0002b314();
extern void __cdecl d_00894a90();

struct AptElement
{
	~AptElement()
	{
	}

	unsigned char m_padding[0x10];
	unsigned char m_flags;
	unsigned char m_tail[3];
};

class WindowManager : public SubsystemInterface
{
public:
	virtual ~WindowManager();
	bool hideAptWindowInternal(int);

private:
	MapD1E0 m_mapD1E0;
	MapD3B0 m_mapD3B0;
	MapD570 m_mapD570;
	MapB590 m_mapB590;
	MapAAB0 m_mapAAB0;
	MapAB60 m_mapAB60;
	MapD1E0 m_mapD1E0b;
	MapB960 m_mapB960;
	AptElement m_aptWindows[12];
	BfmeVector m_vector;
	unsigned char m_tail[0x24];
};

typedef void (__cdecl *ReleaseAll)(int);

WindowManager::~WindowManager()
{
	if (g_theWindowManager != 0)
	{
		if ((m_aptWindows[0].m_flags & 2) != 0)
			hideAptWindowInternal(0);
		(reinterpret_cast<ReleaseAll>(d_00894a90))(1);
		j_0002b314();
		g_theWindowManager = 0;
	}
}
