// Four 14-byte bodies with one shape: compare the word at +0x24 against 2,
// return false when it matches, and otherwise tail-jump to another predicate.
//
//     cmp dword ptr [ecx + 0x24], 2
//     jne  <tail>
//     xor  al, al
//     ret
//     <tail>: jmp ...
//
// The jne skips exactly the three bytes of the false return, so the false case
// is the fall-through and the deferral is the branch -- which is what writing
// the equality test first and the call last gives. ret with nothing to pop and
// ecx never reloaded make these argument-less members.
//
// All four defer through ILT 0x0002FE05 to SpecialAbilityUpdate's matched
// continuePreparation body at 0x002A71E0. Keep the callers' identities while
// referring to that one protected member with its defining spelling.

class SpecialAbilityUpdate
{
	friend class Gen_00267680;
	friend class Gen_0026c0d0;
	friend class Gen_0026c5d0;
	friend class Gen_002983b0;

protected:
	bool continuePreparation();
};

class Gen_00267680
{
public:
	bool bfmeAllows(void);

private:
	char m_bfmeHead[0x24];
	int m_bfme0024;							// +0x24
};

class Gen_0026c0d0
{
public:
	bool bfmeAllows(void);

private:
	char m_bfmeHead[0x24];
	int m_bfme0024;							// +0x24
};

class Gen_0026c5d0
{
public:
	bool bfmeAllows(void);

private:
	char m_bfmeHead[0x24];
	int m_bfme0024;							// +0x24
};

class Gen_002983b0
{
public:
	bool bfmeAllows(void);

private:
	char m_bfmeHead[0x24];
	int m_bfme0024;							// +0x24
};

// ?bfmeAllows@Gen_00267680@@QAE_NXZ
bool Gen_00267680::bfmeAllows(void)
{
	if (m_bfme0024 == 2)
		return false;

	return reinterpret_cast<SpecialAbilityUpdate *>(this)->continuePreparation();
}

// ?bfmeAllows@Gen_0026c0d0@@QAE_NXZ
bool Gen_0026c0d0::bfmeAllows(void)
{
	if (m_bfme0024 == 2)
		return false;

	return reinterpret_cast<SpecialAbilityUpdate *>(this)->continuePreparation();
}

// ?bfmeAllows@Gen_0026c5d0@@QAE_NXZ
bool Gen_0026c5d0::bfmeAllows(void)
{
	if (m_bfme0024 == 2)
		return false;

	return reinterpret_cast<SpecialAbilityUpdate *>(this)->continuePreparation();
}

// ?bfmeAllows@Gen_002983b0@@QAE_NXZ
bool Gen_002983b0::bfmeAllows(void)
{
	if (m_bfme0024 == 2)
		return false;

	return reinterpret_cast<SpecialAbilityUpdate *>(this)->continuePreparation();
}
