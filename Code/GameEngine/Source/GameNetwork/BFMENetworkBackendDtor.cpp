// cl: /DNDEBUG /MD /GX

class BFMENetworkThreadBase
{
public:
	virtual ~BFMENetworkThreadBase();
	virtual void start();
};

class BFMENetworkBackend : public BFMENetworkThreadBase
{
public:
	virtual ~BFMENetworkBackend();
	void openLiveHandle();
	void closeLiveHandle();
};

BFMENetworkBackend::~BFMENetworkBackend()
{
	closeLiveHandle();
}
