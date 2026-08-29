// cl: /DNDEBUG /MD /EHsc

typedef int Bool;
typedef float Real;

extern Real g_bfmeZeroCY;
extern Real g_bfmeScaleBK;

class Locomotor
{
public:
	Real getPreferredHeight() const;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x1cc];
	Locomotor *m_curLocomotor;
};

class Object
{
public:
	Bool bfmeHasSignificantPreferredLocomotorHeight() const;

private:
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

// Require the preferred height to exceed both zero and BFME's 0.1 threshold.
Bool Object::bfmeHasSignificantPreferredLocomotorHeight() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai)
	{
		Locomotor *locomotor = ai->m_curLocomotor;
		if (locomotor)
		{
			Real height = locomotor->getPreferredHeight();
			if (height > g_bfmeZeroCY && height > g_bfmeScaleBK)
				return true;
		}
	}
	return false;
}
