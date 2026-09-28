// A small parser binding built as a virtual base plus three derived fields.
// Keeping the base constructor inline reproduces retail's two vtable stores
// around the parser-registration call.
// Parameter types (identity_evidence/parser_binding_ctor_001920c0.md): the
// retail caller 0x0019B030 passes a by-value 8-byte SidesList member callback,
// and binding vtable 0x0109BFD4 is the one the SidesList loaders 0x0019EC80
// and 0x0074ACB0 install inline. The class name stays address-free but unproven.

typedef void (__cdecl *BfmeChunkParserVE)(void);

extern void __cdecl bfmeChunkParserVE(void);

class AsciiString;
class DataChunkInput;
struct DataChunkInfo;
class SidesList;

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *label, void *parentLabel,
		BfmeChunkParserVE parser, void *userData);
};

class BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry,
		void *label, void *parentLabel)
		: m_registry(registry)
	{
		m_token = registry->bfmeRegister(
			label, parentLabel, bfmeChunkParserVE, this);
	}

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);

private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef bool (SidesList::*BfmeSidesListChunkCallback)(DataChunkInput &, DataChunkInfo *);

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
		DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);

private:
	SidesList *m_owner;
	BfmeSidesListChunkCallback m_callback;
};

// ??0BfmeParserBindingVE@@QAE@PAVSidesList@@P81@AE_NAAVDataChunkInput@@PAUDataChunkInfo@@@ZPAV2@ABVAsciiString@@5@Z
BfmeParserBindingVE::BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
	DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel)
	: BfmeParserBindingBaseVE((BfmeParserRegistryVE *)input, (void *)&label, (void *)&parentLabel),
	  m_owner(owner),
	  m_callback(callback)
{
}
