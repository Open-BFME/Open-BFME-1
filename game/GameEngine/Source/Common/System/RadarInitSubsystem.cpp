// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// Clean C++ reconstruction of the BFME Radar initSubsystem instantiation.
// The Radar object uses Snapshot as its first base and SubsystemInterface as
// its second base, so the registrar adjusts the object pointer by four bytes.

#include "PreRTS.h"
#include "subsystem_interface.h"

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();
};

class Radar : public Snapshot, public SubsystemInterface
{
};

template void initSubsystem<Radar>(Radar *&, AsciiString, Radar *, Xfer *,
	const char *, const char *, const char *);
