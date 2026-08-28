// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object nonnegative preferred-locomotor-height query, retail
// 0x001BE030, 49 bytes. BFME stores AIUpdateInterface at Object +0x204 and
// its current Locomotor at AIUpdateInterface +0x1CC. The canonical
// Locomotor::getPreferredHeight call reaches a four-byte body that reads the
// retail m_preferredHeight field at +0x3C. Null links and nonpositive values
// return the shared 0.0f constant.
//
// Four callers use this value in movement, toppling, and wheel-transform code,
// but none exposes the Object wrapper's retail spelling. The bfme-prefixed name
// is deliberately descriptive. This no-argument thiscall also cannot prove
// cv-qualification; const records the observed query-only behavior.

typedef int Int;
typedef float Real;

extern Real g_bfmeZeroCY; // retail 0x01075350

class Locomotor
{
public:
	Real getPreferredHeight() const;
};

class AIUpdateInterface
{
public:
	unsigned char m_bfmePrefix[0x1CC];
	Locomotor *m_curLocomotor; // +0x1CC
};

class Object
{
public:
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;

private:
	Int m_bfmeObjectPrefix[0x204 / sizeof(Int)];
	AIUpdateInterface *m_ai; // +0x204
};

// ?bfmeGetNonnegativePreferredLocomotorHeight@Object@@QBEMXZ
Real Object::bfmeGetNonnegativePreferredLocomotorHeight() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai != 0)
	{
		Locomotor *locomotor = ai->m_curLocomotor;
		if (locomotor != 0)
		{
			Real height = locomotor->getPreferredHeight();
			if (height > g_bfmeZeroCY)
				return height;
		}
	}
	return g_bfmeZeroCY;
}
