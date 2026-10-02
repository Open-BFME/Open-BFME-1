// Open-BFME5 conversions.

// The 4-byte member at +4 of each entry is a narrow string: retail's call goes
// to StringBase<char>::set (0x00887C90, ?set@?$StringBase@D@@QAEXABV1@@Z), the
// same body the entry's siblings call, so the placeholder BfmeStrVSM is spelled
// as the real StringBase<char> the WWLib header declares.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeEntVSM
{
	int m_bfme00;
	StringBase<char> m_bfme04;
};

class BfmeOwnVSM
{
public:
	char m_bfmePad000[0xf0];
	BfmeEntVSM *m_bfmef0;
	BfmeEntVSM *m_bfmef4;
};

class BfmeIterVSM
{
public:
	char bfmeFetchVSM(int index, BfmeEntVSM *out);
};

char BfmeIterVSM::bfmeFetchVSM(int index, BfmeEntVSM *out)
{
	BfmeOwnVSM *owner = *(BfmeOwnVSM **)((char *)this - 8);
	BfmeEntVSM *entry;

	if (index < 0 || index >= owner->m_bfmef4 - owner->m_bfmef0)
		return 0;

	entry = &(*(BfmeOwnVSM **)((char *)this - 8))->m_bfmef0[index];
	out->m_bfme00 = entry->m_bfme00;
	out->m_bfme04.set(entry->m_bfme04);

	return 1;
}
