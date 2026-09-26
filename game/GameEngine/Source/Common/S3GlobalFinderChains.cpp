// Four 25-byte bodies with one shape: read the word at +0xBC, hand it to a
// member of a global object, and tail-jump into a member of whatever came
// back.
//
//     mov eax, [ecx + 0xBC]
//     mov ecx, [global]
//     push eax
//     call <finder>
//     mov ecx, eax
//     jmp  <getter>
//
// All four go through the same finder, so the type it returns is the same in
// all four; only the getter differs, which is why one result class carries
// four differently named members rather than four classes carrying one each.
// The global's address rides a DIR32 relocation from retail.

class BfmeChainResult
{
public:
	void *bfmeGet_002197e0(void);					// ILT 0x00027746
	void *bfmeGet_00219890(void);					// ILT 0x0002818C
	void *bfmeGet_002198b0(void);					// ILT 0x00036165
	void *bfmeGet_002198d0(void);					// ILT 0x000456E2
};

class BfmeChainOwner
{
public:
	BfmeChainResult *bfmeFind(int key);				// ILT 0x0002F52C
};

extern BfmeChainOwner *TheBfmeChainOwner;				// 0x012F086C

class Gen_002197e0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_00219890
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_002198b0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_002198d0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

// ?bfmeLookup@Gen_002197e0@@QAEPAXXZ
void *Gen_002197e0::bfmeLookup(void)
{
	return TheBfmeChainOwner->bfmeFind(m_bfme00BC)->bfmeGet_002197e0();
}

// ?bfmeLookup@Gen_00219890@@QAEPAXXZ
void *Gen_00219890::bfmeLookup(void)
{
	return TheBfmeChainOwner->bfmeFind(m_bfme00BC)->bfmeGet_00219890();
}

// ?bfmeLookup@Gen_002198b0@@QAEPAXXZ
void *Gen_002198b0::bfmeLookup(void)
{
	return TheBfmeChainOwner->bfmeFind(m_bfme00BC)->bfmeGet_002198b0();
}

// ?bfmeLookup@Gen_002198d0@@QAEPAXXZ
void *Gen_002198d0::bfmeLookup(void)
{
	return TheBfmeChainOwner->bfmeFind(m_bfme00BC)->bfmeGet_002198d0();
}
