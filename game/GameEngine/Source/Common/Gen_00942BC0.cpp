// Clean reconstruction of the conditional forwarding helper at retail RVA
// 0x00942BC0.  The owning type is not recovered (address-derived Gen_00942BC0),
// but the callee is: retail's single call target (callees.py) is the matched
// Render2DSentenceClass::Build_Sentence_Not_Centered body at 0x00942430.
//
// The callee is a __thiscall that returns Vector2 by value through a hidden
// result pointer, so retail pushes five stack slots (result pointer, then the
// four arguments) and ends the callee with ret 0x14.  The function-pointer /
// member-pointer union below is a byte-shape device: it makes MSVC 7.1 emit
// exactly those five pushes plus a __thiscall (ECX = this passed straight
// through, never written), constant-folded to a direct call.  __identifier
// names the real symbol, so the call's reloc lands on the matched body and no
// pin is needed.

extern "C" void __identifier("?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z")();

class Gen_00942BC0
{
public:
	void process(void *first, void *second, void *third);
};

void Gen_00942BC0::process(void *first, void *second, void *third)
{
	int local[2];
	if (first != 0)
	{
		union
		{
			void (*entry)();
			void (Gen_00942BC0::*member)(int *, void *, void *, void *, int);
		} call;
		call.entry = __identifier("?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z");
		(this->*call.member)(local, first, second, third, 0);
	}
}
