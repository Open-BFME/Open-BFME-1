// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#pragma auto_inline(off)
#include "../Object/ObjectStatusBits.h"
#pragma auto_inline(on)

class BfmeOwnerYH
{
public:
	unsigned char m_bfmeHeadYH[0x10];
	Object *m_bfme10YH;
};

class BfmeHostYH
{
public:
	int bfmeApplyYH();

	unsigned char m_bfmeHeadYH[0x1c];
	BfmeOwnerYH *m_bfme1CYH;
	unsigned char m_bfmeGapYH[4];
	unsigned int m_bfme24YH;
};

int BfmeHostYH::bfmeApplyYH()
{
	if (m_bfme24YH < TheGameLogic->m_frame)
		return -1;

	BfmeOwnerYH *owner = this->m_bfme1CYH;
	Object *object = owner->m_bfme10YH;
	ObjectStatusMaskType flags;
	flags.set(22);
	object->setStatus(flags, false);

	return 0;
}
