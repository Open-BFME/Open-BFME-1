// ??4?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.97 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Partial stash for 0x00170228 (vector<ScienceType>::operator=): probe proved
// `template class _STL::vector<ScienceType>` over `enum ScienceType
// {SCIENCE_INVALID=0}` (the ParsePrerequisiteScienceThunk.cpp spelling) is
// instruction-EXACT 261B/6-relocs at the CORRECTED extent 0x00170200/261B
// (lift_extents.csv: start 0x00170200 is 16-aligned after int3; the ledger's
// 0x00170228/221B starts 40B inside the body). Remaining for a landing:
// boundary retraction to 0x00170200/261B plus TU-local alias decls binding the
// STL-spelled helpers to retail bfmeMake_0016FF30 (0x16FF30), tg_0016f680
// (0x16F680), tg_000cd160 (0xCD160) and the node-alloc pair, per the
// ArmorTemplateSetVectorInsertOverflowBody.cpp pattern.

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

template class _STL::vector<ScienceType>;
