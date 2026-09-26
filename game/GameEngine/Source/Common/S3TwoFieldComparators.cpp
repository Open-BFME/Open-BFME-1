// Four bodies the ledger had split three ways -- a comparison, an eight-byte
// return TRUE aliased to W3DShadowGeometry::init, and a five-byte return FALSE
// aliased to AIUpdateInterface::getAiFreeToExit. The branches inside the first
// part target the third, so all three are one function.
//
// Three of them compare two fields against the same two fields of the
// argument. Their offsets are the only thing that differs -- +0x00 with a
// 16-bit second field, +0x04 and +0x08, +0x08 and +0x0C -- and the 16-bit one
// is a word compare, so that field really is a short.
//
// The fourth reads a function pointer at +0x1E8 and, when it is set, calls it
// with this and the argument through a cdecl frame the caller cleans. A null
// pointer is the only way it answers false.
//
// mov eax,1 rather than mov al,1 makes all four int-width.

class Gen_000970a0
{
public:
	int bfmeEquals(const Gen_000970a0 *other) const;

private:
	int m_bfme0000;							// +0x00
	short m_bfme0004;						// +0x04
};

class Gen_004b2190
{
public:
	int bfmeEquals(const Gen_004b2190 *other) const;

private:
	char m_bfmeHead[0x04];
	int m_bfme0004;							// +0x04
	int m_bfme0008;							// +0x08
};

class Gen_004c1180
{
public:
	int bfmeEquals(const Gen_004c1180 *other) const;

private:
	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	int m_bfme000C;							// +0x0C
};

class Gen_00477d30;

typedef void (__cdecl *BfmeHandler)(Gen_00477d30 *owner, void *argument);

class Gen_00477d30
{
public:
	int bfmeDispatch(void *argument);

private:
	char m_bfmeHead[0x1E8];
	BfmeHandler m_bfmeHandler;					// +0x1E8
};

// ?bfmeEquals@Gen_000970a0@@QBEHPBV1@@Z
int Gen_000970a0::bfmeEquals(const Gen_000970a0 *other) const
{
	if (m_bfme0000 == other->m_bfme0000 && m_bfme0004 == other->m_bfme0004)
		return 1;

	return 0;
}

// ?bfmeEquals@Gen_004b2190@@QBEHPBV1@@Z
int Gen_004b2190::bfmeEquals(const Gen_004b2190 *other) const
{
	if (m_bfme0004 == other->m_bfme0004 && m_bfme0008 == other->m_bfme0008)
		return 1;

	return 0;
}

// ?bfmeEquals@Gen_004c1180@@QBEHPBV1@@Z
int Gen_004c1180::bfmeEquals(const Gen_004c1180 *other) const
{
	if (m_bfme0008 == other->m_bfme0008 && m_bfme000C == other->m_bfme000C)
		return 1;

	return 0;
}

// ?bfmeDispatch@Gen_00477d30@@QAEHPAX@Z
int Gen_00477d30::bfmeDispatch(void *argument)
{
	if (m_bfmeHandler)
	{
		m_bfmeHandler(this, argument);

		return 1;
	}

	return 0;
}
