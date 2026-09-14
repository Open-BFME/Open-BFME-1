// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: RousingSpeechUpdate scalar-deleting destructor at retail RVA
// 0x00264E70 (30 bytes).  The exact constructor at 0x00264BF0 installs
// primary vtable 0x010B6D90 whose slot zero routes here; the matched
// complete destructor at 0x00264DA0 clears the speech-object list before
// the SpecialAbilityUpdate base chain is unwound.

class RousingSpeechUpdate
{
public:
	virtual ~RousingSpeechUpdate();
};

void forceRousingSpeechUpdateDeletingDestructor()
{
	RousingSpeechUpdate value;
}
