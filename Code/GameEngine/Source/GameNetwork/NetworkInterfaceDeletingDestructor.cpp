// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: NetworkInterface scalar-deleting destructor at retail RVA
// 0x00681880 (30 bytes). The matched constructor/destructor pair at
// 0x00681840/0x00681860 and NetworkInterface vtable 0x0111A850 establish
// this wrapper's identity; Network::~Network restores that same base vtable.

class NetworkInterface
{
public:
	virtual ~NetworkInterface();
};

void forceNetworkInterfaceDeletingDestructor()
{
	NetworkInterface value;
}
