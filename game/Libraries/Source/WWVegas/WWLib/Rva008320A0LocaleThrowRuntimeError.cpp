// ?_M_throw_runtime_error@locale@_STL@@SAXPBD@Z
// Open-BFME7: STLport locale::_M_throw_runtime_error at 0x008320A0 (88 B gap):
// the TU was built with exceptions off so the runtime_error throw vanished
// and only the "bad locale name: " buffer build survives.
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" __declspec(dllimport) char* __cdecl strncat(char*, const char*, unsigned int);
#pragma intrinsic(strcpy, strlen)
namespace _STL {
class locale {
public:
	static void _M_throw_runtime_error(const char* name);
};
void locale::_M_throw_runtime_error(const char* name)
{
	char buf[256];
	if (name) {
		const char* prefix = "bad locale name: ";
		strcpy(buf, prefix);
		strncat(buf, name, sizeof(buf) - strlen(prefix));
	}
}
}
