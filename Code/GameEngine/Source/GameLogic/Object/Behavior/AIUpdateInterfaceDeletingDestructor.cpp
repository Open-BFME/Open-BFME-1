// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: AIUpdateInterface scalar-deleting destructor at retail RVA
// 0x0027FAC0 (30 bytes). Its exact constructor at 0x0027F4B0, complete
// destructor at 0x0027EF60, pool, module registration, extensive method
// family, and vtable 0x00CBA8A8 establish the class. Dtor ILT: 0x0001C774.

class AIUpdateInterface
{
public:
	virtual ~AIUpdateInterface();
};

void forceAIUpdateInterfaceDeletingDestructor()
{
	AIUpdateInterface value;
}
