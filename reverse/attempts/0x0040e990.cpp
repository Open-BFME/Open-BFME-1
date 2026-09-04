// ?bfmeKeyboardHasFlaggedKey@@YA_N_N@Z
// partial score=0.75 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Retail 0x0040E990 (63B): walk the keyboard singleton key table after a
// virtual update and report whether any down key also carries bit0 of the
// flag byte when the caller asks for that.

typedef bool Bool;

struct BfmeKeySlot
{
	unsigned char m_state;
	unsigned char m_pad1;
	unsigned char m_flags;
	unsigned char m_pad3;
	unsigned int m_pad4;
};

class BfmeKeyboard
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void updateKeys(void);

	unsigned char m_pad4[8];
	BfmeKeySlot *m_begin;
	BfmeKeySlot *m_end;
};

#define TheKeyboard (*(BfmeKeyboard **)0x012F4C50)

// ?bfmeKeyboardHasFlaggedKey@@YA_N_N@Z
Bool bfmeKeyboardHasFlaggedKey(Bool want)
{
	unsigned char found = 0;
	BfmeKeyboard *k = TheKeyboard;
	k->updateKeys();
	BfmeKeyboard *again = TheKeyboard;
	BfmeKeySlot *end = again->m_end;
	BfmeKeySlot *it = again->m_begin;
	if (it != end)
	{
		unsigned char w = *(unsigned char *)&want;
		do
		{
			if (it->m_state == 1)
			{
				if ((it->m_flags & 1) != 0)
				{
					if (w)
						return true;
				}
			}
			++it;
		} while (it != end);
	}
	return found != 0;
}
