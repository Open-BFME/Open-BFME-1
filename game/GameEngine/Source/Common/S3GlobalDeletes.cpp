// Two seventeen-byte bodies, each a single delete of a global:
//
//     mov ecx, [global]
//     test ecx, ecx
//     je   end
//     mov eax, [ecx]
//     push 1
//     call [eax]
//     end: ret
//
// The null test and the vtable slot 0 call with an argument of 1 are what
// delete generates for a pointer whose class has a virtual destructor; nothing
// in the source tests anything.
//
// The ledger had each split after the global load, with the eleven bytes that
// follow claimed as an alias of Campaign::deleteInstance. That reading is
// byte-correct -- delete this compiles to exactly those eleven bytes -- but it
// is the tail of this body, not a function of its own. Campaign::deleteInstance
// keeps its primary row.

class BfmeDeletable
{
public:
	virtual ~BfmeDeletable();
};

extern BfmeDeletable *TheBfmeCampaignManager;				// 0x012F49D0
extern BfmeDeletable *TheBfmeSecondManager;				// 0x012F6DA4

// ?Gen_00510b20@@YAXXZ
void Gen_00510b20(void)
{
	delete TheBfmeCampaignManager;
}

// ?Gen_005f3140@@YAXXZ
void Gen_005f3140(void)
{
	delete TheBfmeSecondManager;
}
