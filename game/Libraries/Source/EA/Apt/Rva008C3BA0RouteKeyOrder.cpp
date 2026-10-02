// cl: /DNDEBUG /MD /EHsc
// RVA 0x008C3BA0: verify the route-key string blocks are strictly ordered.
struct Rva008C3BA0StringBlock;
// The shared empty string block at 0x012D5298, defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  It is only compared
// against here, never read through this TU's incomplete view.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;
extern "C" Rva008C3BA0StringBlock *g_bfmeRouteKeys1282[];
extern "C" int __cdecl _strcmpi(const char *left, const char *right);

bool aptRouteKeysSorted008C3BA0()
{
    for (int index = 0; index < 0xb2; ++index)
    {
        Rva008C3BA0StringBlock *current = g_bfmeRouteKeys1282[index];
        if (current == (Rva008C3BA0StringBlock *)&g_rva012D5298Empty)
            return false;
        int nextIndex = index + 1;
        if (nextIndex < 0xb2)
        {
            Rva008C3BA0StringBlock *next = g_bfmeRouteKeys1282[nextIndex];
            if (current == next)
                return false;
            if (_strcmpi((const char *)current + 8, (const char *)next + 8) >= 0)
                return false;
        }
    }
    return true;
}
