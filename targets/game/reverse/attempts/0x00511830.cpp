// ?bfmeHandleAL@BfmeOwnAL@@QAEHHEE@Z (identity unknown)
// partial score=0.7 date=2026-09-06
// 73/74. The whole control shape is recovered: a 0x15 code guard whose zero
// return sits mid-body, a three-case switch on the byte parameter with cases
// 1, 0x1c and 0x9c (the sub/dec chain reads 1, then +0x1b, then +0x80), the
// extra `& 0xc` test shared by the two high cases, and the state 1 -> 2 store
// at +0x258.
// Residue: retail materialises the return constant 1 into eax BEFORE the
// first test and then uses it as the mask (`mov eax,1` + `test al,bl`), and
// keeps the flags byte in ebx across the switch. MSVC folds the constant into
// the test (`test dl,1`) and re-reads the parameter, saving one byte and no
// callee-saved register. Tried a named int result used as mask and as every
// return value, a named unsigned char local for the flags, and a byte cast on
// the mask. This is the constant-hoisting class.
class BfmeOwnAL
{
public:
	int bfmeHandleAL(int code, unsigned char kind, unsigned char flags);

	unsigned char m_bfmeHeadAL[0x258];
	int m_bfmeStateAL;
};

int BfmeOwnAL::bfmeHandleAL(int code, unsigned char kind, unsigned char flags)
{
	if (code != 0x15)
		return 0;

	unsigned char flagBits = flags;
	int result = 1;
	int kindValue = kind;

	if ((flagBits & (unsigned char)result) == 0)
		return result;

	switch (kindValue)
	{
		case 1:
			break;

		case 0x1c:
		case 0x9c:
			if ((flagBits & 0xc) == 0)
				return result;
			break;

		default:
			return result;
	}

	if (m_bfmeStateAL == result)
		m_bfmeStateAL = 2;

	return result;
}
