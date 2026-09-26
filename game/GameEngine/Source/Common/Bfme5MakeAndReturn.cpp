// Six make-and-return bodies.
//
// Each is a single new expression: allocate, test the block, construct it with
// this, and hand it back -- with the failed allocation returning zero through
// its own epilogue. The unwind frame and the state word going to zero are what
// hold the raw block so it can be freed if the constructor throws, which is
// why an empty-looking one-line function is ninety-odd bytes.
//
// The pushed size is the class width and the only reason one of the six is
// three bytes shorter: 0x40 fits in a byte, 0x148 and the rest do not.


class Gen_0035B680;

class BfmeCreated_0035B680
{
public:
	BfmeCreated_0035B680(Gen_0035B680 *owner);	// retail 0x0002F333

private:
	int m_bfmeFields[0x10];
};

class Gen_0035B680
{
public:
	BfmeCreated_0035B680 *bfmeCreate(void);
};

class Gen_0091A5A0;

class BfmeCreated_0091A5A0
{
public:
	BfmeCreated_0091A5A0(Gen_0091A5A0 *owner);	// retail 0x00919F40

private:
	int m_bfmeFields[0x68];
};

class Gen_0091A5A0
{
public:
	BfmeCreated_0091A5A0 *bfmeCreate(void);
};

class Gen_0092CEF0;

class BfmeCreated_0092CEF0
{
public:
	BfmeCreated_0092CEF0(Gen_0092CEF0 *owner);	// retail 0x0092CD00

private:
	int m_bfmeFields[0xC6];
};

class Gen_0092CEF0
{
public:
	BfmeCreated_0092CEF0 *bfmeCreate(void);
};

class Gen_009513E0;

class BfmeCreated_009513E0
{
public:
	BfmeCreated_009513E0(Gen_009513E0 *owner);	// retail 0x009510A0

private:
	int m_bfmeFields[0x52];
};

class Gen_009513E0
{
public:
	BfmeCreated_009513E0 *bfmeCreate(void);
};

class Gen_00957FB0;

class BfmeCreated_00957FB0
{
public:
	BfmeCreated_00957FB0(Gen_00957FB0 *owner);	// retail 0x00957F40

private:
	int m_bfmeFields[0x53];
};

class Gen_00957FB0
{
public:
	BfmeCreated_00957FB0 *bfmeCreate(void);
};

class Gen_0097D920;

class BfmeCreated_0097D920
{
public:
	BfmeCreated_0097D920(Gen_0097D920 *owner);	// retail 0x0097D850

private:
	int m_bfmeFields[0x5C];
};

class Gen_0097D920
{
public:
	BfmeCreated_0097D920 *bfmeCreate(void);
};

// ?bfmeCreate@Gen_0035B680@@QAEPAVBfmeCreated_0035B680@@XZ
BfmeCreated_0035B680 *Gen_0035B680::bfmeCreate(void)
{
	return new BfmeCreated_0035B680(this);
}

// ?bfmeCreate@Gen_0091A5A0@@QAEPAVBfmeCreated_0091A5A0@@XZ
BfmeCreated_0091A5A0 *Gen_0091A5A0::bfmeCreate(void)
{
	return new BfmeCreated_0091A5A0(this);
}

// ?bfmeCreate@Gen_0092CEF0@@QAEPAVBfmeCreated_0092CEF0@@XZ
BfmeCreated_0092CEF0 *Gen_0092CEF0::bfmeCreate(void)
{
	return new BfmeCreated_0092CEF0(this);
}

// ?bfmeCreate@Gen_009513E0@@QAEPAVBfmeCreated_009513E0@@XZ
BfmeCreated_009513E0 *Gen_009513E0::bfmeCreate(void)
{
	return new BfmeCreated_009513E0(this);
}

// ?bfmeCreate@Gen_00957FB0@@QAEPAVBfmeCreated_00957FB0@@XZ
BfmeCreated_00957FB0 *Gen_00957FB0::bfmeCreate(void)
{
	return new BfmeCreated_00957FB0(this);
}

// ?bfmeCreate@Gen_0097D920@@QAEPAVBfmeCreated_0097D920@@XZ
BfmeCreated_0097D920 *Gen_0097D920::bfmeCreate(void)
{
	return new BfmeCreated_0097D920(this);
}
