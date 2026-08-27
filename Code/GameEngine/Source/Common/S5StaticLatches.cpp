// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: nineteen run-once latches, 0x005E83F0 through 0x005E8750, one
// every 0x30 bytes.
//
// The guard is the compiler's, not the source's: `mov cl,[g] / mov eax,1 /
// test al,cl / jne out / or [g],eax` is MSVC's function-local-static guard,
// which materialises 1 in eax so the same register serves the test and the
// set.  Hand-written flag code does not produce that pair; `if (!(g & 1))`
// compiles to `test byte ptr [g],1`.
//
// THE MISSING `mov ecx` IS THE WHOLE PUZZLE, AND ITS ANSWER IS INLINING.  A
// function-local static of class type normally loads the object's address
// into ecx before its constructor -- five bytes retail does not spend.  It is
// absent because the constructor is INLINE and never touches `this`: its
// whole body is one call, so MSVC inlines it and the object address is never
// needed.  Writing the constructor out-of-line instead lands the body at 43
// bytes with the `mov ecx` in front of the call.
//
// The destructor is inline and EMPTY, but user-declared, which is exactly
// what the bytes ask for: user-declared makes the type non-trivial so the
// static registers with atexit, and empty-and-inline makes the registered
// helper a bare `ret`.  Every one of the nineteen registers such a helper,
// and they sit at 0x00C706F0..0x00C70810 in descending order -- one per
// latch, in reverse declaration order, which is how MSVC lays them out.
//
// The guards are consecutive dwords from 0x00EF6C44 up, and the bodies are
// consecutive: nineteen statics of one translation unit, in declaration
// order.  That is why they are written as one file here.
//
// IDENTITY IS NOT RECOVERED.  Each latch is named for its own address and
// each initialiser for the ILT slot it is reached through.

void bfmeInit00015FB9( void );		// ILT 0x00015FB9
void bfmeInit0002969F( void );		// ILT 0x0002969F
void bfmeInit00014088( void );		// ILT 0x00014088
void bfmeInit00011F1D( void );		// ILT 0x00011F1D
void bfmeInit00032867( void );		// ILT 0x00032867
void bfmeInit00044BFC( void );		// ILT 0x00044BFC
void bfmeInit00016595( void );		// ILT 0x00016595
void bfmeInit000124AE( void );		// ILT 0x000124AE
void bfmeInit0000B686( void );		// ILT 0x0000B686
void bfmeInit000078A1( void );		// ILT 0x000078A1
void bfmeInit0004B0F1( void );		// ILT 0x0004B0F1
void bfmeInit0003D875( void );		// ILT 0x0003D875
void bfmeInit00036458( void );		// ILT 0x00036458
void bfmeInit000101A9( void );		// ILT 0x000101A9
void bfmeInit00011B76( void );		// ILT 0x00011B76
void bfmeInit0001361F( void );		// ILT 0x0001361F
void bfmeInit00026058( void );		// ILT 0x00026058
void bfmeInit00033479( void );		// ILT 0x00033479
void bfmeInit000340FE( void );		// ILT 0x000340FE

struct BfmeLatch005E83F0
{
	BfmeLatch005E83F0() { bfmeInit00015FB9(); }
	~BfmeLatch005E83F0() {}
};

struct BfmeLatch005E8420
{
	BfmeLatch005E8420() { bfmeInit0002969F(); }
	~BfmeLatch005E8420() {}
};

struct BfmeLatch005E8450
{
	BfmeLatch005E8450() { bfmeInit00014088(); }
	~BfmeLatch005E8450() {}
};

struct BfmeLatch005E8480
{
	BfmeLatch005E8480() { bfmeInit00011F1D(); }
	~BfmeLatch005E8480() {}
};

struct BfmeLatch005E84B0
{
	BfmeLatch005E84B0() { bfmeInit00032867(); }
	~BfmeLatch005E84B0() {}
};

struct BfmeLatch005E84E0
{
	BfmeLatch005E84E0() { bfmeInit00044BFC(); }
	~BfmeLatch005E84E0() {}
};

struct BfmeLatch005E8510
{
	BfmeLatch005E8510() { bfmeInit00016595(); }
	~BfmeLatch005E8510() {}
};

struct BfmeLatch005E8540
{
	BfmeLatch005E8540() { bfmeInit000124AE(); }
	~BfmeLatch005E8540() {}
};

struct BfmeLatch005E8570
{
	BfmeLatch005E8570() { bfmeInit0000B686(); }
	~BfmeLatch005E8570() {}
};

struct BfmeLatch005E85A0
{
	BfmeLatch005E85A0() { bfmeInit000078A1(); }
	~BfmeLatch005E85A0() {}
};

struct BfmeLatch005E85D0
{
	BfmeLatch005E85D0() { bfmeInit0004B0F1(); }
	~BfmeLatch005E85D0() {}
};

struct BfmeLatch005E8600
{
	BfmeLatch005E8600() { bfmeInit0003D875(); }
	~BfmeLatch005E8600() {}
};

struct BfmeLatch005E8630
{
	BfmeLatch005E8630() { bfmeInit00036458(); }
	~BfmeLatch005E8630() {}
};

struct BfmeLatch005E8660
{
	BfmeLatch005E8660() { bfmeInit000101A9(); }
	~BfmeLatch005E8660() {}
};

struct BfmeLatch005E8690
{
	BfmeLatch005E8690() { bfmeInit00011B76(); }
	~BfmeLatch005E8690() {}
};

struct BfmeLatch005E86C0
{
	BfmeLatch005E86C0() { bfmeInit0001361F(); }
	~BfmeLatch005E86C0() {}
};

struct BfmeLatch005E86F0
{
	BfmeLatch005E86F0() { bfmeInit00026058(); }
	~BfmeLatch005E86F0() {}
};

struct BfmeLatch005E8720
{
	BfmeLatch005E8720() { bfmeInit00033479(); }
	~BfmeLatch005E8720() {}
};

struct BfmeLatch005E8750
{
	BfmeLatch005E8750() { bfmeInit000340FE(); }
	~BfmeLatch005E8750() {}
};

// ?bfmeEnsure005E83F0@@YAXXZ		guard 0x00EF6C44, atexit helper 0x00C70810
void bfmeEnsure005E83F0( void )
{
	static BfmeLatch005E83F0 s_latch;
}

// ?bfmeEnsure005E8420@@YAXXZ present-unmatched; guard 0x00EF6C48, atexit helper 0x00C70800
void bfmeEnsure005E8420( void )
{
	static BfmeLatch005E8420 s_latch;
}

// ?bfmeEnsure005E8450@@YAXXZ present-unmatched; guard 0x00EF6C4C, atexit helper 0x00C707F0
void bfmeEnsure005E8450( void )
{
	static BfmeLatch005E8450 s_latch;
}

// ?bfmeEnsure005E8480@@YAXXZ		guard 0x00EF6C50, atexit helper 0x00C707E0
void bfmeEnsure005E8480( void )
{
	static BfmeLatch005E8480 s_latch;
}

// ?bfmeEnsure005E84B0@@YAXXZ		guard 0x00EF6C54, atexit helper 0x00C707D0
void bfmeEnsure005E84B0( void )
{
	static BfmeLatch005E84B0 s_latch;
}

// ?bfmeEnsure005E84E0@@YAXXZ present-unmatched; guard 0x00EF6C58, atexit helper 0x00C707C0
void bfmeEnsure005E84E0( void )
{
	static BfmeLatch005E84E0 s_latch;
}

// ?bfmeEnsure005E8510@@YAXXZ		guard 0x00EF6C5C, atexit helper 0x00C707B0
void bfmeEnsure005E8510( void )
{
	static BfmeLatch005E8510 s_latch;
}

// ?bfmeEnsure005E8540@@YAXXZ		guard 0x00EF6C60, atexit helper 0x00C707A0
void bfmeEnsure005E8540( void )
{
	static BfmeLatch005E8540 s_latch;
}

// ?bfmeEnsure005E8570@@YAXXZ		guard 0x00EF6C64, atexit helper 0x00C70790
void bfmeEnsure005E8570( void )
{
	static BfmeLatch005E8570 s_latch;
}

// ?bfmeEnsure005E85A0@@YAXXZ		guard 0x00EF6C68, atexit helper 0x00C70780
void bfmeEnsure005E85A0( void )
{
	static BfmeLatch005E85A0 s_latch;
}

// ?bfmeEnsure005E85D0@@YAXXZ		guard 0x00EF6C6C, atexit helper 0x00C70770
void bfmeEnsure005E85D0( void )
{
	static BfmeLatch005E85D0 s_latch;
}

// ?bfmeEnsure005E8600@@YAXXZ		guard 0x00EF6C70, atexit helper 0x00C70760
void bfmeEnsure005E8600( void )
{
	static BfmeLatch005E8600 s_latch;
}

// ?bfmeEnsure005E8630@@YAXXZ present-unmatched; guard 0x00EF6C74, atexit helper 0x00C70750
void bfmeEnsure005E8630( void )
{
	static BfmeLatch005E8630 s_latch;
}

// ?bfmeEnsure005E8660@@YAXXZ present-unmatched; guard 0x00EF6C78, atexit helper 0x00C70740
void bfmeEnsure005E8660( void )
{
	static BfmeLatch005E8660 s_latch;
}

// ?bfmeEnsure005E8690@@YAXXZ		guard 0x00EF6C7C, atexit helper 0x00C70730
void bfmeEnsure005E8690( void )
{
	static BfmeLatch005E8690 s_latch;
}

// ?bfmeEnsure005E86C0@@YAXXZ		guard 0x00EF6C80, atexit helper 0x00C70720
void bfmeEnsure005E86C0( void )
{
	static BfmeLatch005E86C0 s_latch;
}

// ?bfmeEnsure005E86F0@@YAXXZ present-unmatched; guard 0x00EF6C84, atexit helper 0x00C70710
void bfmeEnsure005E86F0( void )
{
	static BfmeLatch005E86F0 s_latch;
}

// ?bfmeEnsure005E8720@@YAXXZ		guard 0x00EF6C88, atexit helper 0x00C70700
void bfmeEnsure005E8720( void )
{
	static BfmeLatch005E8720 s_latch;
}

// ?bfmeEnsure005E8750@@YAXXZ		guard 0x00EF6C8C, atexit helper 0x00C706F0
void bfmeEnsure005E8750( void )
{
	static BfmeLatch005E8750 s_latch;
}
