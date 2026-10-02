// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source /D_STLP_USE_STATIC_LIB

class BfmeAllocGlobal
{
public:
	virtual void *allocate(unsigned int bytes, void *metadata);
};

// The global this TU reads is the same storage the setter at Rva 0x009A58C0
// writes and BfmeConv930.cpp reads; its one defining name is the tiny store's
// member, redeclared here exactly as TinyGlobalStores.cpp defines it.
class Rva009A58C0
{
public:
	static void store( int value );
	static int s_value;
};

extern "C" __declspec(dllimport) void * __cdecl malloc(unsigned int bytes);

// ?bfmeAllocBlock@@YAPAXI@Z
void * __cdecl bfmeAllocBlock(unsigned int bytes)
{
	BfmeAllocGlobal *global = (BfmeAllocGlobal *)Rva009A58C0::s_value;
	if (global)
	{
		unsigned int metadata[3] = { 0, 0, 0 };
		return global->allocate(bytes, metadata);
	}
	return malloc(bytes);
}
