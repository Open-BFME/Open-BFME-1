// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// AttackPriorityInfo::setPriority -- the recovered BFME spelling of the Zero
// Hour body at ScriptEngine.cpp:168.
//
// Identity: ?setPriority@AttackPriorityInfo@@QAEXPBVThingTemplate@@H@Z, proven
// by the ILT pin at 0x0001600E (pin_consistency: consistent) and by the five
// matched callers, including the byte-matched AttackPriorityInfo::xfer at
// 0x0034EDA0.  See
// targets/game/reverse/identity_evidence/0034ece0-attackpriorityinfo-setpriority.md
//
// Two codegen facts carry the 146-byte body, both measured:
//
// 1. The resolved key is an Overridable-valued TEMPORARY that the map subscript
//    casts at the call.  Typing the temporary `const ThingTemplate *` instead
//    makes MSVC 7.1 store the ternary result into the address-taken slot in
//    each arm (mov [esp+0x18],eax / jmp / mov [esp+0x18],edi), 148 bytes.  With
//    the temporary at the base type the value stays in a register across the
//    branch and retail's phi appears: call getFinalOverride / jmp / mov eax,edi
//    / mov [esp+0x18],eax.  The `thing` parameter is never assigned; a separate
//    temporary keeps it in EDI.
//
// 2. That temporary must be declared in its own block AFTER the lazy
//    allocation.  At function scope it takes a real frame slot and MSVC emits
//    `push ecx` plus the `push -1 / push handler / mov eax,fs:[0]` SEH
//    prologue (149 bytes).  In the inner block it reuses the dead `thing`
//    argument home at [esp+0x18] -- the same slot retail's new-expression
//    pointer used at +0x32 -- with no frame slot at all.
//
// The two declared callees below are spelled to MATCH the retail ILT names
// exactly, which is what makes their relocations resolve at the retail
// addresses instead of compiling to a zero displacement:
//
//   Overridable::getFinalOverride  -> ?getFinalOverride@Overridable@@QBEPBV1@XZ
//     pinned at 0x000022BB (E9 stub -> 0x00087A80).  The declared RETURN TYPE
//     is what mangles the name: `const Overridable *` gives QBEPBV1@XZ and
//     hits the existing pin, while `const void *` gives QBEPBXXZ and does not.
//     Declared, never defined, so the vendored Overridable.h inline
//     (Common/Overridable.h:61) cannot unroll the recursive walk into this
//     body and the call survives.
//   AttackPriorityMap::AttackPriorityMap()
//     -> ??0?$map@PBVThingTemplate@@HU?$less@...@QAE@XZ, pinned at 0x0000C928
//     (E9 stub -> 0x000E9C30, the 54-byte _Rb_tree header ctor tg_000e9c30);
//     the same mangled name is already in targets/game/reverse/
//     dir32_addresses.csv at VA 0x0040C928.  The call at +0x45 is the only
//     one in the image that reaches 0x000E9C30 through a thunk.
//
// `Overridable` and `ThingTemplate` are declared here rather than included
// from the vendored headers on purpose: including Common/Overridable.h would
// inline getFinalOverride and change the bytes, and the layout of the
// undeclared members is never touched -- m_priorityMap sits at +0x0c and
// m_nextOverride at +0x04, the two offsets the body reads.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
};

typedef std::map<const ThingTemplate *, Int> AttackPriorityMap;
typedef _STL::pair<const ThingTemplate * const, Int> AttackPriorityValue;
typedef _STL::_Rb_tree<const ThingTemplate *, AttackPriorityValue,
	_STL::_Select1st<AttackPriorityValue>, _STL::less<const ThingTemplate *>,
	_STL::allocator<AttackPriorityValue> > AttackPriorityTree;
namespace _STL
{
template <> AttackPriorityTree::~_Rb_tree();
}

class AttackPriorityInfo
{
public:
	void setPriority(const ThingTemplate *thing, Int priority);

private:
	char m_unreconstructed_00[0x0c];
	AttackPriorityMap *m_priorityMap;
};

// ?setPriority@AttackPriorityInfo@@QAEXPBVThingTemplate@@H@Z
void AttackPriorityInfo::setPriority(const ThingTemplate *thing, Int priority)
{
	if (thing == 0)
		return;

	if (m_priorityMap == 0)
		m_priorityMap = new AttackPriorityMap;

	{
		Overridable *self = (Overridable *)thing;
		const void *key = self->m_nextOverride != 0 ?
			(const void *)self->m_nextOverride->getFinalOverride() : (const void *)self;
		(*m_priorityMap)[(const ThingTemplate *)key] = priority;
	}
}
