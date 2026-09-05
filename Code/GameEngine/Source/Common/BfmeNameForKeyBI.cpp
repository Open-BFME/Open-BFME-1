// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the name-for-key lookup at retail 0x007696B0, 62 bytes.  A hit
// writes its name straight into our caller's return slot; a miss copies the
// shared default.

class StringBaseNarrowBI
{
protected:
	StringBaseNarrowBI(const StringBaseNarrowBI &other) throw();

	~StringBaseNarrowBI(void) throw();

	char *m_bfmeNarrowBI;
};

class AsciiStringBI : public StringBaseNarrowBI
{
public:
	AsciiStringBI(const AsciiStringBI &other) throw() : StringBaseNarrowBI(other)
	{
	}

	~AsciiStringBI(void) throw()
	{
	}
};

extern AsciiStringBI g_bfmeDefaultBI;			// retail 0x01336E50

class BfmeThingBI
{
public:
	AsciiStringBI bfmeNameBI(void) throw();
};

BfmeThingBI *__stdcall bfmeLookupBI(int key) throw();

// ?bfmeNameForBI@@YG?AVAsciiStringBI@@H@Z
AsciiStringBI __stdcall bfmeNameForBI(int key)
{
	BfmeThingBI *thing = bfmeLookupBI(key);

	if (thing != 0)
		return thing->bfmeNameBI();

	return g_bfmeDefaultBI;
}
