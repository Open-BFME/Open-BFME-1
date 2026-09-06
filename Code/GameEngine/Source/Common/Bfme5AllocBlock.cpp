// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Source /D_STLP_USE_STATIC_LIB

class BfmeAllocGlobal
{
public:
	virtual void *allocate(unsigned int bytes, void *metadata);
};

extern BfmeAllocGlobal *g_bfmeAllocGlobal;
extern "C" __declspec(dllimport) void * __cdecl u2_import_0135944C(unsigned int bytes);

// ?bfmeAllocBlock@@YAPAXI@Z
void * __cdecl bfmeAllocBlock(unsigned int bytes)
{
	BfmeAllocGlobal *global = g_bfmeAllocGlobal;
	if (global)
	{
		unsigned int metadata[3] = { 0, 0, 0 };
		return global->allocate(bytes, metadata);
	}
	return u2_import_0135944C(bytes);
}
