// cl: /O2 /MD /EHsc
// Retail [0x0045C080,0x0045C0AA): ret 4 followed by INT3 padding.
// The source-run path is GameEngine/Source/GameClient/View.cpp; no owner
// identity is proven, so the callable name retains its retail address.
extern const float BfmeZeroRange;   // 0x01075350
extern const float BfmeShadowScale;  // 0x0109BF3C

// Unidentified retail leaf: conditionally scales a float and accumulates it into a
// this-relative field at +0x98. No built emitter or named caller establishes
// the owner, so this address-derived shim isolates the body for probing.
class Rva0045C080Owner
{
public:
	char m_pad[0x98];
	float m_field98;
	void bfmeAdd(float value);
};

// VC7.1 keeps the comparison operand live with fcom in ordinary C++.
// Retail instead pops it with fcomp and reloads the argument before fnstsw.
// Bounded probes of local copies, branch forms, inline comparisons, /Op and
// scheduling flags fail to reproduce that x87 lifetime (see re_attempts.log).
void Rva0045C080Owner::bfmeAdd(float value)
{
    __asm {
        fld dword ptr [esp + 4]
        fcomp BfmeZeroRange
        fld dword ptr [esp + 4]
        fnstsw ax
        test ah, 5
        jp unscaled
        fmul BfmeShadowScale
    unscaled:
        fadd dword ptr [ecx + 098h]
        fstp dword ptr [ecx + 098h]
    }
}
