// Nine tag-checked reference assignments.
//
// Each asks the incoming object for its type through virtual slot 13 and
// refuses it unless the answer matches one fixed tag, dropping whatever it
// already held; on a match it bumps the refcount, releases the old block and
// takes the new pointer.
//
// The tags read as ASCII when the dword is laid out little-endian -- ANIM,
// TEX, HOLD, MESH, PART, HIER, AGGR, BOX, NULL -- so the slot returns a
// FourCC, and the nine bodies differ in nothing else.
//
// Two shapes matter for the bytes. On the refusing path the clear of the held
// pointer sits INSIDE the null guard, not after it: when the pointer is
// already null the body jumps straight to the shared epilogue and never writes
// the zero. And the source pointer is re-read after the virtual call for the
// refcount bump, which survives here -- unlike the plain release family, where
// the compiler folds the second test away -- precisely because the call in
// between could have changed it.

class BfmeTagged
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual unsigned int bfmeTag(void);			// slot 13, vtable+0x34

	void bfmeRelease(void);					// retail 0x009EB7A0

	unsigned short m_bfmeRefCount;				// +0x04
};


class Gen_0090BCF0
{
public:
	Gen_0090BCF0 &operator=(const Gen_0090BCF0 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_0090DB10
{
public:
	Gen_0090DB10 &operator=(const Gen_0090DB10 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00970800
{
public:
	Gen_00970800 &operator=(const Gen_00970800 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00970E40
{
public:
	Gen_00970E40 &operator=(const Gen_00970E40 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00971220
{
public:
	Gen_00971220 &operator=(const Gen_00971220 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00971600
{
public:
	Gen_00971600 &operator=(const Gen_00971600 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00971C60
{
public:
	Gen_00971C60 &operator=(const Gen_00971C60 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_00972340
{
public:
	Gen_00972340 &operator=(const Gen_00972340 &other);

private:
	BfmeTagged *m_bfmePtr;
};

class Gen_009729D0
{
public:
	Gen_009729D0 &operator=(const Gen_009729D0 &other);

private:
	BfmeTagged *m_bfmePtr;
};

// ??4Gen_0090BCF0@@QAEAAV0@ABV0@@Z
Gen_0090BCF0 &Gen_0090BCF0::operator=(const Gen_0090BCF0 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x414E494D)			// 'ANIM'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_0090DB10@@QAEAAV0@ABV0@@Z
Gen_0090DB10 &Gen_0090DB10::operator=(const Gen_0090DB10 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x00544558)			// 'TEX'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00970800@@QAEAAV0@ABV0@@Z
Gen_00970800 &Gen_00970800::operator=(const Gen_00970800 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x484C4F44)			// 'HOLD'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00970E40@@QAEAAV0@ABV0@@Z
Gen_00970E40 &Gen_00970E40::operator=(const Gen_00970E40 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x4D455348)			// 'MESH'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00971220@@QAEAAV0@ABV0@@Z
Gen_00971220 &Gen_00971220::operator=(const Gen_00971220 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x50415254)			// 'PART'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00971600@@QAEAAV0@ABV0@@Z
Gen_00971600 &Gen_00971600::operator=(const Gen_00971600 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x48494552)			// 'HIER'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00971C60@@QAEAAV0@ABV0@@Z
Gen_00971C60 &Gen_00971C60::operator=(const Gen_00971C60 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x41474752)			// 'AGGR'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_00972340@@QAEAAV0@ABV0@@Z
Gen_00972340 &Gen_00972340::operator=(const Gen_00972340 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x00424F58)			// 'BOX'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}

// ??4Gen_009729D0@@QAEAAV0@ABV0@@Z
Gen_009729D0 &Gen_009729D0::operator=(const Gen_009729D0 &other)
{
	BfmeTagged *source = other.m_bfmePtr;

	if (source)
	{
		if (source->bfmeTag() != 0x4E554C4C)			// 'NULL'
		{
			if (m_bfmePtr)
			{
				m_bfmePtr->bfmeRelease();

				m_bfmePtr = 0;
			}

			return *this;
		}

		if (other.m_bfmePtr)
			++other.m_bfmePtr->m_bfmeRefCount;
	}

	if (m_bfmePtr)
		m_bfmePtr->bfmeRelease();

	m_bfmePtr = other.m_bfmePtr;

	return *this;
}
