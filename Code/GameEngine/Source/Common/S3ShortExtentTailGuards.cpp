// cl: /DNDEBUG /MD /EHs-c-

// Two more bodies whose rows stopped five bytes short of the E9 their own
// branch targets -- the same mistake the twelve deque push_backs had.
//
// 0x00249C10 reads a byte at +0xF4, returns false when it is set, and
// otherwise tail-jumps to TransportContain::isSpecificRiderFreeToExit. A
// tail jump to a named base member is a QUALIFIED base call, not a virtual
// one, so this is an override that short-circuits and then defers.
//
// 0x002D60A0 reads two pointers at NEGATIVE displacements from this, -0x08
// and -0x0C. Members never sit before this, so this is not the whole object:
// it is a sub-object whose owner holds those two pointers in front of it, and
// the body is written that way -- the owner recovered by subtracting 0x0C,
// which folds back into the same two displacements. It compares a word two
// dereferences deep against one a single dereference deep and defers on less
// than -- written as an early return false on greater-or-equal, which is what
// puts the deferral last and leaves the false path falling through.
//
// Both classes take their names from their own addresses; nothing in the image
// names them.

class Object;

// ---- 0x00249C10 -------------------------------------------------------------

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
protected:
	virtual bool isSpecificRiderFreeToExit(Object *object);		// ILT 0x000249DD
};

class Gen_00249c10 : public TransportContain
{
protected:
	virtual bool isSpecificRiderFreeToExit(Object *object);

private:
	char m_bfmeHead[0xF4 - 0x04];
	bool m_bfmeLocked;						// +0xF4
};

// ?isSpecificRiderFreeToExit@Gen_00249c10@@MAE_NPAVObject@@@Z
bool Gen_00249c10::isSpecificRiderFreeToExit(Object *object)
{
	if (m_bfmeLocked)
		return false;

	return TransportContain::isSpecificRiderFreeToExit(object);
}

// ---- 0x002D60A0 -------------------------------------------------------------

class Gen_002d60a0Inner
{
public:
	char m_bfmeHead[0x28];
	int m_bfme0028;							// +0x28
};

class Gen_002d60a0Held
{
public:
	char m_bfmeHead[0x210];
	Gen_002d60a0Inner *m_bfmeInner;					// +0x210
};

class Gen_002d60a0Limit
{
public:
	char m_bfmeHead[0x74];
	int m_bfme0074;							// +0x74
};

class Gen_002d60a0Owner
{
public:
	Gen_002d60a0Limit *m_bfmeLimit;					// this - 0x0C
	Gen_002d60a0Held *m_bfmeHeld;					// this - 0x08
};

class Gen_002d60a0
{
public:
	bool bfmeCheck(Object *object);

private:
	bool bfmeDefer(Object *object);					// ILT 0x0000204F
};

// ?bfmeCheck@Gen_002d60a0@@QAE_NPAVObject@@@Z
bool Gen_002d60a0::bfmeCheck(Object *object)
{
	Gen_002d60a0Owner *owner = (Gen_002d60a0Owner *)((char *)this - 0x0C);

	if (owner->m_bfmeHeld->m_bfmeInner->m_bfme0028 >= owner->m_bfmeLimit->m_bfme0074)
		return false;

	return bfmeDefer(object);
}
