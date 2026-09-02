// ?setModelConditionFlags@Object@@QAEXABV?$BitFlags@$0BEA@@@@Z
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x001B6EB0: BFME Object::setModelConditionFlags.  Zero a 320-bit
// BitFlags local (ten dwords) and forward to clearAndSetModelConditionFlags.

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

class Object
{
public:
	void setModelConditionFlags(const BitFlags<320> &set);
	void clearAndSetModelConditionFlags(const BitFlags<320> &clr, const BitFlags<320> &set);
};

void Object::setModelConditionFlags(const BitFlags<320> &set)
{
	BitFlags<320> flagsToClear;
	flagsToClear.m_bits[0] = 0;
	flagsToClear.m_bits[1] = 0;
	flagsToClear.m_bits[2] = 0;
	flagsToClear.m_bits[3] = 0;
	flagsToClear.m_bits[4] = 0;
	flagsToClear.m_bits[5] = 0;
	flagsToClear.m_bits[6] = 0;
	flagsToClear.m_bits[7] = 0;
	flagsToClear.m_bits[8] = 0;
	flagsToClear.m_bits[9] = 0;
	clearAndSetModelConditionFlags(flagsToClear, set);
}
