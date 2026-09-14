// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CreditsManager scalar-deleting destructor at retail RVA
// 0x0040CE00 (30 bytes). The matched constructor at 0x0040CA50 installs
// vtable 0x010F0D04, whose update slot is independently named, and the matched
// complete destructor at 0x0040CB20 owns the credits-list teardown. This
// wrapper calls it through ILT 0x000389CE before scalar operator delete.

class CreditsManager
{
public:
	virtual ~CreditsManager();
};

void forceCreditsManagerDeletingDestructor()
{
	CreditsManager value;
}
