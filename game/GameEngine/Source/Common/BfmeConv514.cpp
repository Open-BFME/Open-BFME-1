class BfmeSinkBQE
{
public:
	void bfmeDoBQE(void *what);
};

// 0x012F1028 is the one Glo012F1028 global.  BfmeSinkBQE above is this TU's
// view of that object (its member is the pinned bfmeDoBQE callee), so the use
// casts rather than declaring a second name for the address.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

void __stdcall bfmeGoBQE(void *what)
{
	if (what == 0)
		((BfmeSinkBQE *)Glo012F1028)->bfmeDoBQE(0);
}
