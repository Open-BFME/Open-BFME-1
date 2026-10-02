// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Glo012F7048Type::test, retail 0x00609350, 12 bytes.
//
// Three instructions: load the global at 0x012F706C and hand back the byte at
// +0x288. The method is a thiscall by its decorated name but never touches
// `this' -- the answer comes entirely out of the global.

typedef bool Bool;

// This TU's local view of the pointee: only the byte at +0x288 is read.
class BfmeGameCW
{
public:
	unsigned char m_unmodelled_000[0x288];
	Bool m_flag;						// +0x288
};

// retail 0x012F706C: the global is EA's `LivingWorldManager
// *TheLivingWorldManager`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManager.cpp, so
// that is the one spelling this TU links against.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Glo012F7048Type
{
public:
	Bool test(void);
};

Bool Glo012F7048Type::test(void)
{
	return reinterpret_cast< BfmeGameCW * >( TheLivingWorldManager )->m_flag;
}
