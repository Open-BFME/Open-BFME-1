// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: RadiusDecalUpdate scalar-deleting destructor at retail RVA
// 0x002A0720 (30 bytes). Its exact constructor at 0x002A0640, complete
// destructor at 0x002A04E0, factories, pool, and landed decal methods
// establish the class. The destructor ILT is 0x00012EC7.

class RadiusDecalUpdate
{
public:
	virtual ~RadiusDecalUpdate();
};

void forceRadiusDecalUpdateDeletingDestructor()
{
	RadiusDecalUpdate value;
}
