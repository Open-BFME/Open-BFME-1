// Two 30-byte rows that are the same assertion site compiled into two
// different translation units, and the only rows in this slice that name
// themselves:
//
//     u2_get_diag()->fail("false", <__FILE__>, <__LINE__>);
//
// The two file strings are still in the image and are what identify the code:
//
//     0x008013F0 -> "\views\feslbuild_main\jabba\fesl\source\gamebrowser\gamebrowsergame.cpp",  line 529
//     0x00802980 -> "\views\feslbuild_main\jabba\fesl\source\gamebrowser\gamebrowserlobby.cpp", line 321
//
// so this neighbourhood is EA's FESL game-browser client, built from a
// `\views\feslbuild_main\jabba\fesl` source tree.  Both rows push the SAME
// first argument, the literal "false", which is the stringised condition of an
// assertion whose expression was the constant false -- an unconditional
// "should not get here" -- and both push a decimal line number as the third.
// The literals are DIR32 the patcher fills, but the build verifies each one
// byte-equals the string at the address it fills in, so the text above is
// checked, not assumed.
//
// The reporter is fetched by a cdecl call taking no arguments and returning a
// pointer, and the report goes through the FOURTH slot of its vftable; the
// wrappers themselves are __thiscall members that never touch `this` and never
// read their single argument, which is why nothing but the call survives.
// Neither the reporter's class nor the two callers are named by the image, so
// those names are derived from addresses.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

struct Rva008013F0Browser
{
	void assertFailed(int cookie);
};

void Rva008013F0Browser::assertFailed(int)
{
	Rva007EB810Get()->fail("false",
	                       "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowsergame.cpp",
	                       529);
}

struct Rva00802980Browser
{
	void assertFailed(int cookie);
};

void Rva00802980Browser::assertFailed(int)
{
	Rva007EB810Get()->fail("false",
	                       "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserlobby.cpp",
	                       321);
}
