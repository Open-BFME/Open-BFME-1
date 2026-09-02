// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z
// partial score=0.7 date=2026-09-02
// Open-BFME banked attempt: ScriptActions::doTeamSetRepulsor, retail 0x002FD570.
// BLOCKER SHARED BY EVERY BODY IN THIS FAMILY: the DLINK team-member walk.
//
// Retail iterates a team's members through a pointer-to-member-function of a
// VIRTUALLY INHERITED Object, which is why the constants 0x00401140 and
// 0xFFFFFF9C (-100) appear literally in a dozen bodies of d_002f6330.asm:
//
//     mov ecx, 0x00401140          ; PMF field 0: the dlink_next thunk
//     mov edx, 0xFFFFFF9C          ; PMF field 2: delta = -100
//     xor edi, edi                 ; PMF field 1: vbtable index = 0
//   loop:
//     mov ecx, [eax + 0x68]        ; Object's vbptr sits at +0x68
//     mov edx, [ecx + edi]         ; vbtable[vbindex]
//     add edx, ebp                 ; + delta
//     lea ecx, [edx + eax + 0x68]  ; this = obj + 0x68 + vbtable[i] + delta
//     call esi                     ; PMF field 0
//
// This exact instruction sequence IS reproducible from clean C++.  Measured
// with MSVC 7.1 in build/pmf_probe.cpp:
//
//     class Object;
//     class ObjectDlinkBase { public: Object *dlink_next_TeamMemberList() const; };
//     class ObjectFields { public: unsigned char m_pad[0x68]; };
//     class Object : public ObjectFields, public virtual ObjectDlinkBase { ... };
//     typedef Object *(Object::*GetNextFunc)() const;
//
// Passing the PMF as a parameter emits retail's register form exactly
// (mov eax,[obj+vbptr]; mov ecx,[eax+idx]; add ecx,delta; add ecx,obj; call pfn)
// and the 0x68 prefix class puts the vbptr where retail has it.
//
// WHAT IS STILL MISSING: retail's PMF constants are vbindex = 0 and
// delta = -100.  A single virtual base compiles to vbindex = 4 and a folded
// delta, so BFME's Object carries a vbase layout this reconstruction does not
// have yet.  Recovering it is shared-header-scale work -- it is not local to
// any one of these bodies -- but it unlocks all of them at once:
// 0x002FDDB0 doTeamStop, 0x002FC4C0 doAffectObjectPanelFlagsTeam,
// 0x002FD570 doTeamSetRepulsor, 0x002FD790 (arm 96, ZH PLAYER_HUNT),
// 0x002F6850, 0x002F6A70, 0x002F6B90, 0x002F6EB0, 0x002F7280, 0x002F73D0,
// 0x002F7530, 0x002F75D0, 0x002F7670 and 0x002FAD50.

// The ZH body below is structurally confirmed against retail instruction
// for instruction; only the walk above blocks the byte match.
void ScriptActions::doTeamSetRepulsor(const AsciiString& teamName, Bool repulsor)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theSrcTeam) {
		return;
	}

	if (theSrcTeam) 
	{
		for (DLINK_ITERATOR<Object> iter = theSrcTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj) 
			{
				continue;
			}
			obj->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_REPULSOR ), repulsor );
		}
	}

}
