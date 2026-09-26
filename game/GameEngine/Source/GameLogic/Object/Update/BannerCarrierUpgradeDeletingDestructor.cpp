// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: BannerCarrierUpgrade scalar-deleting destructor at retail RVA
// 0x002846D0 (30 bytes). The recovered complete destructor at 0x002844F0 and
// BannerCarrierUpdateModuleData's owned vector deletion establish the concrete
// non-virtual type. The wrapper calls its destructor through ILT 0x000438AB.

class BannerCarrierUpgrade
{
public:
	~BannerCarrierUpgrade();
};

void forceBannerCarrierUpgradeDelete(BannerCarrierUpgrade *upgrade)
{
	delete upgrade;
}
