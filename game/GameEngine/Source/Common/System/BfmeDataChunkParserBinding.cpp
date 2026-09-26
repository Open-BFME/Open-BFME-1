// A small parser binding built as a virtual base plus three derived fields.
// Keeping the base constructor inline reproduces retail's two vtable stores
// around the parser-registration call.

typedef void (__cdecl *BfmeChunkParserVE)(void);

extern void __cdecl bfmeChunkParserVE(void);

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

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(int first, int second, int third,
		BfmeParserRegistryVE *registry, void *label, void *parentLabel);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);

private:
	int m_first;
	int m_second;
	int m_third;
};

// ??0BfmeParserBindingVE@@QAE@HHHPAVBfmeParserRegistryVE@@PAX1@Z
BfmeParserBindingVE::BfmeParserBindingVE(int first, int second, int third,
	BfmeParserRegistryVE *registry, void *label, void *parentLabel)
	: BfmeParserBindingBaseVE(registry, label, parentLabel),
	  m_first(first),
	  m_second(second),
	  m_third(third)
{
}
