// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// ?dup_00337640 (31 B), ?dup_00337670 (15 B), ?dup_003377a0 (39 B): retail keeps
// the constructor, destructor and scalar deleting destructor of LatchRestore<int>
// at these addresses. Which BFME TU emitted them is unknown (the rows keep their
// address names); the bodies are the stock Common/LatchRestore.h template, the
// same one GameState.cpp instantiates for Bool at 0x0010D330.
#include "Common/LatchRestore.h"

template class LatchRestore<int>;
