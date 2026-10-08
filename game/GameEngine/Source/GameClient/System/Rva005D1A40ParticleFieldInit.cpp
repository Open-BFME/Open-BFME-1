// cl: /DNDEBUG /MD /EHsc
//
// 0x005D1A40 (34 B) is the out-of-line copy of the particle-system field
// table setup that parseParticleSystemDefinition (0x005D1A70) inlines: it
// takes the category buffer in EAX (MSVC's internal-linkage register
// convention for a static helper), fills categories 0-5 through
// bfmeCategoryHead1054 (ILT 0x0001F7C6 -> 0x005D19D0) and copies the
// 32-byte "System" FieldParse table recorded at VA 0x0110F92C to +0x90.
// No caller reaches it in retail; the probe caller below only anchors the
// register convention and is not a ledger claim.  Identity unproven, so the
// name keeps the address.

struct BfmeCategoryHead1054;

struct ParticleSystemFieldTable
{
	const void *slots[8];
};

extern const ParticleSystemFieldTable g_0110F92C;
extern void j_0001f7c6(void) throw();

static __declspec(noinline) void rva005D1A40InitParticleFields(
	BfmeCategoryHead1054 *categories)
{
	typedef void (*Function)(BfmeCategoryHead1054 *);
	union { void (*raw)(void); Function typed; } fn;
	fn.raw = j_0001f7c6;
	fn.typed(categories);
	*(ParticleSystemFieldTable *)((unsigned char *)categories + 0x90) =
		g_0110F92C;
}

void rva005D1A40ProbeCaller(BfmeCategoryHead1054 *categories)
{
	rva005D1A40InitParticleFields(categories);
}
