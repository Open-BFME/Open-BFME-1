// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#include "matrix4.h"
class Rva008D76A0 : public Matrix4 {
public: Matrix4 inverse() const;
};
Matrix4 Rva008D76A0::inverse() const { return Matrix4::Inverse(); }
// Proven extent: 0x008D76A0..0x008D7AFB; INT3 padding on both sides. Source implements Gauss-Jordan inverse; semantic linkage name remains unproven.
