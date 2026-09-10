// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Full149B at658A0 ends65935 with INT3 padding; this is a standalone
// vector destructor, not a polymorphic module-data destructor.
// SubsystemLegendEntry calls it through26AB2 at78245/78252/7825F.
// The body releases four-byte AsciiString elements through887940, then
// uses the STLport128-byte allocator threshold and buffer deallocator.
#include <vector>
#include "ascii_string.h"
typedef char AsciiStringMustBeFourBytes[sizeof(AsciiString) == 4 ? 1 : -1];
typedef char StringVectorMustBeTwelveBytes[sizeof(_STL::vector<AsciiString>) == 12 ? 1 : -1];

// ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ
template _STL::vector<AsciiString>::~vector();
