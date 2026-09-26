// cl: /DNDEBUG /MD /EHsc

// Retail 0x002C5240, 126 bytes, __thiscall taking one const AICommandParms*
// and cleaning 4 bytes (ret 4). Shares its "this-0x20" Root view and the
// AICommandParms layout with the already-landed sibling
// Rva002C45E0Dispatch.cpp (its own gate() call is the SAME vtable slot,
// 0x210/4 = 132, right after that file's 132 rootPad stubs), so this file
// redeclares that class locally (separate TU, no ODR issue in this
// scaffold-per-function build) and gives its slot-19 stub a real two-int
// signature (vtable slot 0x4c/4 = 19) since THIS body is direct evidence for
// that slot's arity that the sibling file's stub does not need. Also calls
// the already-landed BfmeB1004::bfmeGo1004B() (BfmeConv1004.cpp) on the same
// "this-0x20" pointer, and, non-virtually (ClassName::method, matching the
// idiom the sibling file itself uses for aiDoCommand), the sibling's own
// Rva002C45E0::dispatch on the OUTER this. The command==0x42 arm reaches the
// already-pinned but still-unconverted BfmeHostESE::bfmeDoAESE
// (BfmeConv1969.cpp declares the class; 0x002C4FD0 itself is still a dump).
// No caller or vtable-install evidence names this function's own identity,
// so it and its owning class stay address-derived.

struct AICommandParms
{
	int m_cmd;
	int m_cmdSource;
	char m_pos[12];
	void *m_obj;
};

class Root
{
public:
	virtual void rootPad0() = 0;
	virtual void rootPad1() = 0;
	virtual void rootPad2() = 0;
	virtual void rootPad3() = 0;
	virtual void rootPad4() = 0;
	virtual void rootPad5() = 0;
	virtual void rootPad6() = 0;
	virtual void rootPad7() = 0;
	virtual void rootPad8() = 0;
	virtual void rootPad9() = 0;
	virtual void rootPad10() = 0;
	virtual void rootPad11() = 0;
	virtual void rootPad12() = 0;
	virtual void rootPad13() = 0;
	virtual void rootPad14() = 0;
	virtual void rootPad15() = 0;
	virtual void rootPad16() = 0;
	virtual void rootPad17() = 0;
	virtual void rootPad18() = 0;
	virtual void rootStep19(void *obj, int cmdSource) = 0;
	virtual void rootPad20() = 0;
	virtual void rootPad21() = 0;
	virtual void rootPad22() = 0;
	virtual void rootPad23() = 0;
	virtual void rootPad24() = 0;
	virtual void rootPad25() = 0;
	virtual void rootPad26() = 0;
	virtual void rootPad27() = 0;
	virtual void rootPad28() = 0;
	virtual void rootPad29() = 0;
	virtual void rootPad30() = 0;
	virtual void rootPad31() = 0;
	virtual void rootPad32() = 0;
	virtual void rootPad33() = 0;
	virtual void rootPad34() = 0;
	virtual void rootPad35() = 0;
	virtual void rootPad36() = 0;
	virtual void rootPad37() = 0;
	virtual void rootPad38() = 0;
	virtual void rootPad39() = 0;
	virtual void rootPad40() = 0;
	virtual void rootPad41() = 0;
	virtual void rootPad42() = 0;
	virtual void rootPad43() = 0;
	virtual void rootPad44() = 0;
	virtual void rootPad45() = 0;
	virtual void rootPad46() = 0;
	virtual void rootPad47() = 0;
	virtual void rootPad48() = 0;
	virtual void rootPad49() = 0;
	virtual void rootPad50() = 0;
	virtual void rootPad51() = 0;
	virtual void rootPad52() = 0;
	virtual void rootPad53() = 0;
	virtual void rootPad54() = 0;
	virtual void rootPad55() = 0;
	virtual void rootPad56() = 0;
	virtual void rootPad57() = 0;
	virtual void rootPad58() = 0;
	virtual void rootPad59() = 0;
	virtual void rootPad60() = 0;
	virtual void rootPad61() = 0;
	virtual void rootPad62() = 0;
	virtual void rootPad63() = 0;
	virtual void rootPad64() = 0;
	virtual void rootPad65() = 0;
	virtual void rootPad66() = 0;
	virtual void rootPad67() = 0;
	virtual void rootPad68() = 0;
	virtual void rootPad69() = 0;
	virtual void rootPad70() = 0;
	virtual void rootPad71() = 0;
	virtual void rootPad72() = 0;
	virtual void rootPad73() = 0;
	virtual void rootPad74() = 0;
	virtual void rootPad75() = 0;
	virtual void rootPad76() = 0;
	virtual void rootPad77() = 0;
	virtual void rootPad78() = 0;
	virtual void rootPad79() = 0;
	virtual void rootPad80() = 0;
	virtual void rootPad81() = 0;
	virtual void rootPad82() = 0;
	virtual void rootPad83() = 0;
	virtual void rootPad84() = 0;
	virtual void rootPad85() = 0;
	virtual void rootPad86() = 0;
	virtual void rootPad87() = 0;
	virtual void rootPad88() = 0;
	virtual void rootPad89() = 0;
	virtual void rootPad90() = 0;
	virtual void rootPad91() = 0;
	virtual void rootPad92() = 0;
	virtual void rootPad93() = 0;
	virtual void rootPad94() = 0;
	virtual void rootPad95() = 0;
	virtual void rootPad96() = 0;
	virtual void rootPad97() = 0;
	virtual void rootPad98() = 0;
	virtual void rootPad99() = 0;
	virtual void rootPad100() = 0;
	virtual void rootPad101() = 0;
	virtual void rootPad102() = 0;
	virtual void rootPad103() = 0;
	virtual void rootPad104() = 0;
	virtual void rootPad105() = 0;
	virtual void rootPad106() = 0;
	virtual void rootPad107() = 0;
	virtual void rootPad108() = 0;
	virtual void rootPad109() = 0;
	virtual void rootPad110() = 0;
	virtual void rootPad111() = 0;
	virtual void rootPad112() = 0;
	virtual void rootPad113() = 0;
	virtual void rootPad114() = 0;
	virtual void rootPad115() = 0;
	virtual void rootPad116() = 0;
	virtual void rootPad117() = 0;
	virtual void rootPad118() = 0;
	virtual void rootPad119() = 0;
	virtual void rootPad120() = 0;
	virtual void rootPad121() = 0;
	virtual void rootPad122() = 0;
	virtual void rootPad123() = 0;
	virtual void rootPad124() = 0;
	virtual void rootPad125() = 0;
	virtual void rootPad126() = 0;
	virtual void rootPad127() = 0;
	virtual void rootPad128() = 0;
	virtual void rootPad129() = 0;
	virtual void rootPad130() = 0;
	virtual void rootPad131() = 0;
	virtual bool gate(const AICommandParms *parms) = 0;
};

class BfmeB1004
{
public:
	void bfmeGo1004B();
};

class Rva002C45E0
{
public:
	virtual void dispatch(const AICommandParms *parms);
};

class BfmeThingESE;

class BfmeHostESE
{
public:
	void bfmeDoAESE(BfmeThingESE *thing, void *ctx);
};

class Rva002C5240Owner
{
public:
	void rvaHandleCommand(const AICommandParms *command);

private:
	unsigned char m_prefix[0x328];
	int m_328;   // +0x328
};

// ?rvaHandleCommand@Rva002C5240Owner@@QAEXPBUAICommandParms@@@Z
void Rva002C5240Owner::rvaHandleCommand(const AICommandParms *command)
{
	Root *root = (Root *)((char *)this - 0x20);
	if (!root->gate(command))
		return;

	if (command->m_cmd == 0x13)
	{
		void *obj = command->m_obj;
		if (obj != 0 && m_328 == *(int *)((char *)obj + 0x74))
			return;
	}

	((BfmeB1004 *)root)->bfmeGo1004B();

	switch (command->m_cmd)
	{
	case 0x13:
		((BfmeHostESE *)root)->bfmeDoAESE(
				(BfmeThingESE *)command->m_obj, (void *)command->m_cmdSource);
		return;

	case 0x42:
		root->rootStep19(command->m_obj, command->m_cmdSource);
		return;

	default:
		((Rva002C45E0 *)this)->Rva002C45E0::dispatch(command);
		return;
	}
}
