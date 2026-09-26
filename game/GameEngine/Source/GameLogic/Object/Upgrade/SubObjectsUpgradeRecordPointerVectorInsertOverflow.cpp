// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oi /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The UpgradeTexture parser at 0x002D8C10 pushes a record pointer into the
// vector at its third argument. Its overflow call uses ILT 0x00007711, which
// jumps to this 265-byte body at 0x002D8820. The retail body moves four-byte
// elements and uses STLport's >128-byte large/small allocator split.
// The record's semantic type has no independent name witness yet.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Rva002D8C10Record;
template class _STL::vector<Rva002D8C10Record *>;
