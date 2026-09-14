// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: BannerUI scalar-deleting destructor at retail 0x005847C0
// (30 bytes).  The named BannerUI vtable at 0x00D0B828 routes slot zero to
// this wrapper; the matched complete destructor at 0x00583FF0 and the
// existing BannerUI constructor/member layout establish the identity.

class BannerUI
{
public:
	virtual ~BannerUI();
};

void Force_BannerUI_Deleting_Destructor()
{
	BannerUI value;
}
