// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BFMETransitionGroup scalar-deleting destructor at retail RVA
// 0x0048ACC0 (30 bytes). Its exact constructor at 0x0048AAD0, complete
// destructor at 0x0048AB20, and getNewGroup/setName users establish the class.
// The complete destructor is reached through ILT 0x0000BB27.

class BFMETransitionGroup
{
public:
	~BFMETransitionGroup();
};

void forceBFMETransitionGroupDelete(BFMETransitionGroup *group)
{
	delete group;
}
