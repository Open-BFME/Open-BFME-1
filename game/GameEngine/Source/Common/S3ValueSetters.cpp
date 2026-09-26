// Nine setters in two shapes.
//
// Three notify-setters store the argument into a member, rewrite the argument
// slot with this, and tail-jump to a member of a global manager -- the slot
// rewrite is what lets the notification be a jump rather than a call.
//
// Six change-setters compare first and only store when the value actually
// differs, then call a member with no arguments. Which side of the cmp holds
// the register tells the source order: cmp al,[mem] is "value != member" and
// cmp [mem],al is "member != value".
//
// In both shapes the operand width separates the types -- al is a Bool, eax an
// int -- and the ret immediate divided by four gives the argument count.

typedef bool Bool;


class Gen_000946D0Manager
{
public:
	void bfmeNotify(void *sender);				// ILT 0x0001A7DF
};

extern Gen_000946D0Manager *TheBfmeManager_000946D0;

class Gen_000946D0
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x8];
	Bool m_bfmeValue;						// +0x8
};

class Gen_00094700Manager
{
public:
	void bfmeNotify(void *sender);				// ILT 0x0001A7DF
};

extern Gen_00094700Manager *TheBfmeManager_00094700;

class Gen_00094700
{
public:
	void bfmeSet(int value);

private:
	char m_bfmeHead[0x8];
	int m_bfmeValue;						// +0x8
};

class Gen_00094730Manager
{
public:
	void bfmeNotify(void *sender);				// ILT 0x0001A7DF
};

extern Gen_00094730Manager *TheBfmeManager_00094730;

class Gen_00094730
{
public:
	void bfmeSet(int value);

private:
	char m_bfmeHead[0x8];
	int m_bfmeValue;						// +0x8
};

class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);

private:
	void bfmeChanged(void);					// ILT 0x000200D1

	char m_bfmeHead[0x3AD];
	Bool m_bfmeValue;						// +0x3AD
};

class Gen_0041B0D0
{
public:
	void bfmeSet(Bool value);

private:
	void bfmeChanged(void);					// ILT 0x0002E564

	char m_bfmeHead[0x142];
	Bool m_bfmeValue;						// +0x142
};

class Gen_00505530
{
public:
	void bfmeSet(void *ignored, int value);

private:
	void bfmeChanged(void);					// ILT 0x00023A29

	char m_bfmeHead[0x224];
	int m_bfmeValue;						// +0x224
};

class Gen_00505550
{
public:
	void bfmeSet(void *ignored, int value);

private:
	void bfmeChanged(void);					// ILT 0x00023A29

	char m_bfmeHead[0x21C];
	int m_bfmeValue;						// +0x21C
};

class Gen_005899B0
{
public:
	void bfmeSet(int value);

private:
	void bfmeChanged(void);					// ILT 0x0001D354

	char m_bfmeHead[0x50];
	int m_bfmeValue;						// +0x50
};

class Gen_005899D0
{
public:
	void bfmeSet(int value);

private:
	void bfmeChanged(void);					// ILT 0x0000271B

	char m_bfmeHead[0x54];
	int m_bfmeValue;						// +0x54
};

// ?bfmeSet@Gen_000946D0@@QAEX_N@Z
void Gen_000946D0::bfmeSet(Bool value)
{
	m_bfmeValue = value;

	TheBfmeManager_000946D0->bfmeNotify(this);
}

// ?bfmeSet@Gen_00094700@@QAEXH@Z
void Gen_00094700::bfmeSet(int value)
{
	m_bfmeValue = value;

	TheBfmeManager_00094700->bfmeNotify(this);
}

// ?bfmeSet@Gen_00094730@@QAEXH@Z
void Gen_00094730::bfmeSet(int value)
{
	m_bfmeValue = value;

	TheBfmeManager_00094730->bfmeNotify(this);
}

// ?bfmeSet@Gen_00411DD0@@QAEX_N@Z
void Gen_00411DD0::bfmeSet(Bool value)
{
	if (value != m_bfmeValue)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}

// ?bfmeSet@Gen_0041B0D0@@QAEX_N@Z
void Gen_0041B0D0::bfmeSet(Bool value)
{
	if (m_bfmeValue != value)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}

// ?bfmeSet@Gen_00505530@@QAEXPAXH@Z
void Gen_00505530::bfmeSet(void *ignored, int value)
{
	if (m_bfmeValue != value)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}

// ?bfmeSet@Gen_00505550@@QAEXPAXH@Z
void Gen_00505550::bfmeSet(void *ignored, int value)
{
	if (m_bfmeValue != value)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}

// ?bfmeSet@Gen_005899B0@@QAEXH@Z
void Gen_005899B0::bfmeSet(int value)
{
	if (m_bfmeValue != value)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}

// ?bfmeSet@Gen_005899D0@@QAEXH@Z
void Gen_005899D0::bfmeSet(int value)
{
	if (m_bfmeValue != value)
	{
		m_bfmeValue = value;

		bfmeChanged();
	}
}
