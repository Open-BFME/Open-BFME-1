// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#include "meshgeometry.h"

class Rva0092C320
{
public:
 virtual void method(char *text);
 unsigned char m_unreconstructed04[0xc4];
 MeshGeometryClass *m_targetC8;
};

void Rva0092C320::method(char *text)
{
 m_targetC8->Set_User_Text(text);
}

// Boundary and ABI evidence: identity_evidence/006e9b80-0092c320-wrappers.md.
