// Clean reconstruction of the conditional forwarding helper at retail RVA
// 0x00942BC0.  The owning type and callee identity are not recovered; the
// address-derived declarations preserve the observed five-argument call.

// Existing object symbol for retail00942430. Its body consumes ECX and
// returns with ret20; the caller supplies the first stack slot as an out-buffer.
extern "C" void bfme_Render2DSentence_BuildNotCentered_942430();

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
		call.entry = bfme_Render2DSentence_BuildNotCentered_942430;
		(this->*call.member)(local, first, second, third, 0);
	}
}
