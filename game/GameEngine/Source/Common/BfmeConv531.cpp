class BfmeSinkBUB
{
public:
	bool bfmeAskBUB(void *what);
};

// Retail's 0x012F0888 global is the ledger's TheExperienceLevelSystem.
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// Retail calls ILT 0x0001E64B, which the ledger defines as ?j_0001e64b@@YAXXZ.
extern void j_0001e64b();
typedef bool (BfmeSinkBUB::*BfmeAskBUBCall)(void *);
template<class T> T iltMemberCall(void (*p)()) { union { void (*plain)(); T member; } call; call.plain = p; return call.member; }

bool __stdcall bfmeGoBUB(void *what)
{
	BfmeSinkBUB *sink = (BfmeSinkBUB *)TheExperienceLevelSystem;
	if (sink != 0 && (sink->*iltMemberCall<BfmeAskBUBCall>(j_0001e64b))(what))
		return true;
	return false;
}
