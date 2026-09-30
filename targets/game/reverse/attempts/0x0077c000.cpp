// ?_M_insert_overflow@?$vector@UModelConditionInfo@@V?$allocator@UModelConditionInfo@@@_STL@@@_STL@@IAEXPAUModelConditionInfo@@ABU3@ABU__false_type@2@I_N@Z
// partial score=1.0 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Instantiating vector<ModelConditionInfo>::_M_insert_overflow at retail 0x0077C000.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct ModelConditionInfo
{
	ModelConditionInfo(const ModelConditionInfo &);
	~ModelConditionInfo();

	char m_body[0x128];
};

void ModelConditionInfoVectorInsertOverflowAnchor(
	_STL::vector<ModelConditionInfo> &items, const ModelConditionInfo &value)
{
	items.insert(items.begin(), value);
}
