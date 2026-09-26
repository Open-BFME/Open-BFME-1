// ?purgeFinishedSounds@Rva0069D1C0Owner@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: 0x0069D1C0 (93 B gap): walk the STLport list of Miles quick
// handles at this+0x9bc and unload+erase every handle whose AIL_quick_status
// reports done (1).
#define _STLP_NO_EXCEPTIONS 1
#include <list>
extern "C" __declspec(dllimport) int __stdcall AIL_quick_status(void* handle);
extern "C" __declspec(dllimport) void __stdcall AIL_quick_unload(void* handle);
struct Rva0069D1C0Owner {
	char m_pad[0x9bc];
	_STL::list<void*> m_sounds;
	void purgeFinishedSounds();
};
void Rva0069D1C0Owner::purgeFinishedSounds()
{
	_STL::list<void*>::iterator it = m_sounds.begin();
	while (it != m_sounds.end()) {
		if (AIL_quick_status(*it) == 1) {
			AIL_quick_unload(*it);
			it = m_sounds.erase(it);
		} else {
			++it;
		}
	}
}
