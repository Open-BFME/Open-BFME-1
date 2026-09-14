// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SkirmishScreenState scalar-deleting destructor at retail RVA
// 0x00529310 (30 bytes). Its exact constructor at 0x00528F60, complete
// destructor at 0x00529110, and recovered Skirmish screen method family
// establish the class. The complete destructor ILT is 0x0000B42E.

class SkirmishScreenState
{
public:
	~SkirmishScreenState();
};

void forceSkirmishScreenStateDelete(SkirmishScreenState *state)
{
	delete state;
}
