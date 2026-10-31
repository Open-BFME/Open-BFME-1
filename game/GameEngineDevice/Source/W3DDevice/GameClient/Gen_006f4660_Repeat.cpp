// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F4660. helper(a, a, a, a).

// Render2DSentenceClass::Draw_Sentence (0x0093EB50, Render2DSentenceDrawSentence.cpp);
// retail calls it with ECX passed through.
extern "C" void __identifier("?Draw_Sentence@Render2DSentenceClass@@QAEXHHHH@Z")();

// ?wrap_006f4660@@YGXH@Z
void __stdcall wrap_006f4660(int a)
{
	reinterpret_cast<void (__stdcall *)(int, int, int, int)>(
		__identifier("?Draw_Sentence@Render2DSentenceClass@@QAEXHHHH@Z"))(a, a, a, a);
}
