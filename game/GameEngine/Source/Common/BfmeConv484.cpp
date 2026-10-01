// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
enum NameKeyType { };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *what);
};

extern NameKeyGenerator *g_bfmeSinkBLC;

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
	void *m_bfmeGot;
};

void BfmeThingBLC::bfmeGoBLC(void *what)
{
	// The key is stored through a void* hand-off; the retail body returns the
	// NameKeyType in eax and this file only forwards it, so the cast is free.
	m_bfmeGot = (void *)g_bfmeSinkBLC->nameToKey((const char *)what);
}
