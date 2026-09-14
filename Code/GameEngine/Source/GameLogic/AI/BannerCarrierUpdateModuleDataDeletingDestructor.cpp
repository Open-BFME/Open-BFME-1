// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Open-BFME5: BannerCarrierUpdateModuleData scalar-deleting destructor at
// retail RVA 0x00285490 (30 bytes).  Its vtable 0x010BBBB8 slot zero routes
// through ILT 0x0003FDD2 to the matched complete destructor at 0x00284AA0;
// the exact constructor at 0x00284600 installs that same primary vtable.
// BannerCarrierUpdateModuleData's matched object-name and locomotor lookup
// methods independently corroborate the class identity.

class BannerCarrierUpdateModuleData
{
public:
	virtual ~BannerCarrierUpdateModuleData();
};

void forceBannerCarrierUpdateModuleDataDeletingDestructor()
{
	BannerCarrierUpdateModuleData value;
}
