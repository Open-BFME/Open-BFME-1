extern "C" void *bfmeVftEAX[];

class BfmeRefEAX
{
public:
	virtual void __stdcall bfmeSlot0EAX();
	virtual void __stdcall bfmeSlot1EAX();
	virtual void __stdcall bfmeReleaseEAX();
};

extern int g_bfmeCountEAX;
extern BfmeRefEAX *g_bfmeAEAX;
extern BfmeRefEAX *g_bfmeBEAX;

class MaterialPassClass
{
public:
	~MaterialPassClass();

	void *volatile m_bfmeVftEAX;
};

class BfmeHostEAX : public MaterialPassClass
{
public:
	~BfmeHostEAX();
};

BfmeHostEAX::~BfmeHostEAX()
{
	m_bfmeVftEAX = bfmeVftEAX;

	if (--g_bfmeCountEAX == 0)
	{
		if (g_bfmeAEAX != 0)
			g_bfmeAEAX->bfmeReleaseEAX();

		g_bfmeAEAX = 0;

		if (g_bfmeBEAX != 0)
			g_bfmeBEAX->bfmeReleaseEAX();

		g_bfmeBEAX = 0;
	}
}
