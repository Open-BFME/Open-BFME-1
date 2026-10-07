// cl: /EHsc
// stlport
#include "../../Include/GameClient/Video.h"
#include <vector>

// EH-framed destructor at 0x81D040: 28-byte Video elements, destroyed through
// ILT 0x167CF -> Video::~Video at 0xC3410. Unwind cleanup releases vector
// storage through the base destructor at 0x81C890. VideoVectorDestruction.cpp
// retains the distinct no-EH compiler variant at 0x81D0F0.
template _STL::vector<Video>::~vector();
