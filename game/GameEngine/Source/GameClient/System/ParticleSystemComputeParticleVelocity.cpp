// ?computeParticleVelocity@ParticleSystem@@IAE?AUCoord3D@@PBU2@@Z
// partial score=1.0 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc
// readable body of ?computeParticleVelocity@ParticleSystem@@: retail RVA
// 0x005C3630, 104 bytes, __thiscall with a hidden sret pointer and ret 8.
//
// Identity. The single call target 0x00008814 is an ILT thunk that jumps to
// the MATCHED body 0x005FAC90, so the callee is the proven thiscall
// Rva005FAC90Owner::scale. The only caller is the MATCHED
// ParticleSystem::generateParticleInfo (0x005D0530), which calls this body
// through ILT 0x0000C2BB with the sret slot and &info.m_pos, and whose
// matched source (game/GameEngine/Source/GameClient/System/
// ParticleSystem_generateParticleInfo_BFME.cpp) already declares the member as
// `Coord3D computeParticleVelocity(const Coord3D *pos)`. That matched caller
// names the symbol, so the class and member keep their real names here.
//
// Layout, read from the retail bytes: this+0x134 is a Coord3D (the factors
// argument), this+0x1C0 is the receiver forwarded in ECX for the thiscall,
// and this+0x1C4 is the +0x18-slot object passed as the last argument. The
// receiver and the slot object are both null-tested, and a failure of either
// returns a zero Coord3D through the hidden sret pointer.
//
// Shape notes, each measured against the retail bytes:
//  - The callee is declared struct-returning. That is what makes MSVC 7.1
//    forward this function's own hidden sret pointer as the callee's result
//    pointer, which is why retail reads the sret slot into ESI at +0x20,
//    passes ESI as the first argument and returns it in EAX with no copy. A
//    five-argument forwarding constructor instead needs ECX for a second
//    `this` and emits push ecx/pop ecx for a 108-byte body.
//  - The x87 idiom (fld / fadd / fmul / fstp) is the volatile-qualified read
//    spelled exactly as in the MATCHED sibling 0x005C36C0
//    (Rva005C36C0Forward.cpp), which compiles byte-exact with the same
//    g_bfmeDefaultBU / g_rva0107533C constants and the same GlobalData +0xAB4 load.
//  - The +0x18 slot is computed by a helper that takes the slot pointer BY
//    REFERENCE. That is the only spelling measured that keeps retail's
//    redundant second null test at +0x19 (`cmp esi,edx / je +3`) and the
//    `lea edx,[esi+0x18]` after it. Given the pointer by value -- and equally
//    as a local, a ternary, a member function of the slot type, a `char *` or
//    `unsigned int` cast, a union view, a second base class at the same
//    offset, a non-forceinline static helper, or an out-of-line accessor --
//    MSVC 7.1 proves the pointer non-null on that path and folds the test,
//    emitting `add edx,0x18` and losing the `push esi` that must precede the
//    first branch. Passing by reference leaves the front end unable to
//    propagate the guard's non-null fact into the helper body, and all 104
//    bytes match.
typedef float Real;

extern Real g_bfmeDefaultBU;
extern const Real g_rva0107533C;

struct Coord3D
{
	Coord3D() : x(0), y(0), z(0) {}
	Coord3D(Real xValue, Real yValue, Real zValue) : x(xValue), y(yValue), z(zValue) {}

	Real x;
	Real y;
	Real z;
};

struct BfmeG1269
{
	unsigned char m_head[0xAB4];
	Real m_valueAB4;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// The callee is the MATCHED 0x005FAC90 body (Rva005FAC90Scale.cpp), reached
// here through the ILT thunk 0x00008814. It is declared struct-returning, under
// an address-derived name, for the same reason and with the same precedent as
// the MATCHED sibling 0x005C36C0's call to 0x005FAE40: the struct return is
// what makes MSVC 7.1 forward this function's own hidden sret pointer as the
// callee's result pointer instead of copying it. That is a property of the
// CALL SITE's ABI view, not a claim about the callee's own identity, so the
// name stays address-keyed and the pin routes to the matched body.
class Rva005FAC90Owner
{
public:
	Coord3D rva005FAC90(void *context, const Coord3D *factors, Real amount,
		void *extra);
};

// The +0x1C4 object; retail addresses its +0x18 slot.
class BfmeBHL
{
public:
	unsigned char m_head[0x18];
};

// The pointer is taken BY REFERENCE on purpose -- see the shape note above.
// Taking it by value makes MSVC 7.1 fold retail's redundant second test.
static __forceinline void *bfmeSlot018(BfmeBHL *&slot)
{
	if (slot != 0)
		return reinterpret_cast<char *>(slot) + 0x18;

	return 0;
}

class ParticleSystem
{
protected:  // ZH ParticleSys.h declares it protected; the ILT pin is IAE
	Coord3D computeParticleVelocity(const Coord3D *pos);

private:
	unsigned char m_head[0x134];
	Coord3D m_value134;								///< +0x134, the factors
	unsigned char m_mid[0x1C0 - 0x134 - 12];
	Rva005FAC90Owner *m_receiver;					///< +0x1C0, stays in ECX
	BfmeBHL *m_value1c4;								///< +0x1C4, slot at +0x18
};

// ?computeParticleVelocity@ParticleSystem@@IAE?AUCoord3D@@PBU2@@Z
Coord3D ParticleSystem::computeParticleVelocity(const Coord3D *pos)
{
	if (m_receiver != 0)
	{
		if (m_value1c4 != 0)
		{
			// retail passes the argument through unchanged; the callee's
			// `context` is modelled unconstrained, hence the cast.
			return m_receiver->rva005FAC90(const_cast<Coord3D *>(pos), &m_value134,
				(*(volatile Real *)&((BfmeG1269 *)TheWritableGlobalData)->m_valueAB4 + g_bfmeDefaultBU) * g_rva0107533C,
				bfmeSlot018(m_value1c4));
		}
	}

	return Coord3D(0, 0, 0);
}
