// ??0BfmeRecordEQP@@QAE@HHHHHHH@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 79/79 bytes; ONE transposition: retail emits xor ecx,ecx after the [eax+0xc]
// store and the a5 load, MSVC emits it before both. No pins needed.
struct BfmeRecordEQP
{
	BfmeRecordEQP(int owner, int kind, int source, int target,
		int amount, int stamp, int extra);

	int m_bfmeOwnerEQP;
	int m_bfmeKindEQP;
	int m_bfmeSourceEQP;
	int m_bfmeTargetEQP;
	int m_bfmeNextEQP;
	int m_bfmePrevEQP;
	int m_bfmeHeadEQP;
	int m_bfmeTailEQP;
	int m_bfmeAmountEQP;
	char m_bfmeActiveEQP;
	int m_bfmeCountEQP;
	int m_bfmeIndexEQP;
	int m_bfmeStateEQP;
	int m_bfmeStampEQP;
	int m_bfmeExtraEQP;
};

BfmeRecordEQP::BfmeRecordEQP(int owner, int kind, int source, int target,
	int amount, int stamp, int extra)
	: m_bfmeOwnerEQP(owner), m_bfmeKindEQP(kind), m_bfmeSourceEQP(source),
	  m_bfmeTargetEQP(target), m_bfmeNextEQP(0), m_bfmePrevEQP(0),
	  m_bfmeHeadEQP(0), m_bfmeTailEQP(0), m_bfmeAmountEQP(amount),
	  m_bfmeActiveEQP(0), m_bfmeCountEQP(0), m_bfmeIndexEQP(0),
	  m_bfmeStateEQP(0), m_bfmeStampEQP(stamp), m_bfmeExtraEQP(extra)
{
}
