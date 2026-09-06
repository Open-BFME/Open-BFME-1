// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /MD /EHsc /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "Common/STLTypedefs.h"
#include <hash_map>
#include <list>
#include <set>

struct Gen_t_006939d0_p12cd
{
	int words[3];
	Gen_t_006939d0_p12cd();
	Gen_t_006939d0_p12cd(const Gen_t_006939d0_p12cd &);
	~Gen_t_006939d0_p12cd();
	Gen_t_006939d0_p12cd &operator=(const Gen_t_006939d0_p12cd &);
};

struct Rva00694710TreeValue8
{
	int words[2];
};

typedef _STL::pair<const int, Gen_t_006939d0_p12cd> Rva00694710HashPair;
typedef _STL::hash_map<int, Gen_t_006939d0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00694710HashPair> > Rva00694710HashMap;

class Rva00694710AudioWorker
{
public:
	Rva00694710AudioWorker(void *context);

private:
	Rva00694710HashMap m_files;
	_STL::list<int> m_requests[3];
	_STL::set<Rva00694710TreeValue8> m_open;
	_STL::set<int> m_complete;
	int m_state38;
	int m_state3c;
	void *m_thread;
	unsigned char m_stop;
	void *m_context;
};

Rva00694710AudioWorker::Rva00694710AudioWorker(void *context)
	: m_files(), m_requests(), m_open(), m_complete()
{
	m_state38 = 0;
	m_state3c = 0;
	m_thread = 0;
	m_stop = 0;
	m_context = context;
	m_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)0x004193F8,
		this, 0, NULL);
}
