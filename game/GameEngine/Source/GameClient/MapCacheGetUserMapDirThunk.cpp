// cl: /DNDEBUG /MD /O2 /EHsc
// Re-homed from ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ so the 318B
// retail body at 0x00451460 can carry that name. This file keeps the 5-byte
// ILT trampoline as a tail call.

class AsciiString;

class MapCache
{
public:
	AsciiString getUserMapDir() const;
};

// In this MSVC 7.1 x86 view, the nonvirtual member pointer is the code
// pointer. Reading it as a raw function preserves incoming ECX and the stack.
union MapCacheGetUserMapDirTarget
{
	AsciiString (MapCache::*member)() const;
	void (*function)();
};

void j_000139e9()
{
	MapCacheGetUserMapDirTarget target;
	target.member = &MapCache::getUserMapDir;
	target.function();
}
