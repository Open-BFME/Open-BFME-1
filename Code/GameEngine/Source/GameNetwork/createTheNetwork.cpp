// cl: /DNDEBUG /MD /GX

// Retail 0x00682320. Callers OnGameStart (0x0068A57E) and
// GameSpyStagingRoom::launchGame (0x006399B0) reach this through ILT
// 0x0001D0B1 in place of ZH's
//   TheNetwork = NetworkInterface::createNetwork();
//   TheNetwork->init();
// Distinct from NetworkInterface::createNetwork at 0x0065C1F0, which
// allocates the 0xA8 GameSpy queue. This factory deletes any existing
// TheNetwork, operator-news 0x40 bytes, constructs BFMENativeNetwork
// (ILT 0x0001E8F8 -> construct@BFMENativeNetwork 0x006818B0), stores
// the pointer at TheNetwork (0x012F7714), and vcalls init (slot +4).

class NetworkInterface
{
public:
	virtual ~NetworkInterface();
	virtual void init();
};

class BFMENativeNetwork : public NetworkInterface
{
public:
	BFMENativeNetwork();

private:
	unsigned char m_unreconstructed[0x3C];
};

extern NetworkInterface *TheNetwork;

void createTheNetwork(void)
{
	if (TheNetwork)
		delete TheNetwork;
	TheNetwork = new BFMENativeNetwork;
	TheNetwork->init();
}
