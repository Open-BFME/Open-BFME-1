#ifndef OPENBFME_REFERENCE_SHIMS_DX8STATE_DX8STATE_H
#define OPENBFME_REFERENCE_SHIMS_DX8STATE_DX8STATE_H

// DX8Wrapper's state declarations belong to the canonical WW3D header.  The
// BFME render callers need to inspect the protected counters, so widen access
// only while that header is included; do not duplicate the class here.
#define protected public
#define private public
#include "../../../game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef private
#undef protected

#endif // OPENBFME_REFERENCE_SHIMS_DX8STATE_DX8STATE_H
