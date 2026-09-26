// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Address-derived identity retained. The old comparison to a purported
// NameKeyGenerator destructor at 0x168710 was false: that body belongs to
// AISkirmishPlayer. This distinct 95-byte body has a SubsystemInterface base
// and an auxiliary-map cleanup; its semantic class identity remains unproven.

#include "Common/SubsystemInterface.h"

class Rva0008FE00AuxMap
{
public:
	~Rva0008FE00AuxMap();
private:
	unsigned int m_storage[5];
};

class Rva0008FE00Owner : public SubsystemInterface
{
public:
	virtual ~Rva0008FE00Owner();
	virtual void init() { }
	virtual void update() { }
	virtual void reset() { }

private:
	void freeSockets();

	enum { SOCKET_COUNT = 45007 };
	void *m_sockets[SOCKET_COUNT];
	unsigned int m_nextID;
	Rva0008FE00AuxMap m_keyToBucketStorage;
};

Rva0008FE00Owner::~Rva0008FE00Owner()
{
	freeSockets();
}
