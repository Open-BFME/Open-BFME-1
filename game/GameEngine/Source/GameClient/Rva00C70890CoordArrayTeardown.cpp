// cl: /O2 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// Retail 00C70890 tears down the 30 Coord3D elements at VA012F6E50.
// The initializing caller 005FB530 constructs the same array with stride12
// through Coord3D ctor ILT16C93 and registers this cleanup with atexit.
// The compiler emits the native vector destructor callback as _$E2.
#include "coord3d.h"
Coord3D Rva012F6E50Array[30];
