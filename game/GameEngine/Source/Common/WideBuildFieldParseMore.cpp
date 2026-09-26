// Four more INI field-parse builders, found by re-running the proven bodies of
// WideBuildFieldParse.cpp and WideBuildFieldParsePair.cpp as a GRAMMAR rather
// than as byte strings: `push esi / mov esi,[esp+8]`, then any sequence of
// either a base-class block (`push esi / call REL32 / add esp,4`) or an
// append block (`push EXTRA / push offset TABLE / mov ecx,esi / call
// 0x00850920`), then `pop esi / ret`.  Opcode-structure grouping cannot see
// these: it keys on the exact block sequence, so a builder with three tables,
// or with the base call last, or with an extra offset too large for an imm8,
// falls out as a singleton.
//
// WHAT THE BYTES SHOW, per member:
//   0x0013E170  two tables, extras 0 and 224 -- 224 needs a `push imm32`
//   0x00212CD0  base call, then two tables, extras 92 and 0
//   0x00378170  three tables, all extra 0, no base call
//   0x00753A80  one table then the base call LAST, which fixes the source
//               order of the two statements and is not recoverable any other
//               way
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the tables are
// undefined externs whose only role is to make cl emit `push offset`.

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
public:
	void add( const WideFieldParse *fields, unsigned int extraOffset );
};

class Gen00012355
{
public:
	static void buildFieldParse( WideMulti &p );
};

class Gen00022584
{
public:
	static void buildFieldParse( WideMulti &p );
};

extern const WideFieldParse WideTblA0013E170[];
extern const WideFieldParse WideTblB0013E170[];

class Rva0013E170
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva0013E170::buildFieldParse( WideMulti &p )
{
	p.add( WideTblA0013E170, 0 );
	p.add( WideTblB0013E170, 224 );
}

extern const WideFieldParse WideTblA00212CD0[];
extern const WideFieldParse WideTblB00212CD0[];

class Rva00212CD0
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00212CD0::buildFieldParse( WideMulti &p )
{
	Gen00012355::buildFieldParse( p );
	p.add( WideTblA00212CD0, 92 );
	p.add( WideTblB00212CD0, 0 );
}

extern const WideFieldParse WideTblA00378170[];
extern const WideFieldParse WideTblB00378170[];
extern const WideFieldParse WideTblC00378170[];

class Rva00378170
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00378170::buildFieldParse( WideMulti &p )
{
	p.add( WideTblA00378170, 0 );
	p.add( WideTblB00378170, 0 );
	p.add( WideTblC00378170, 0 );
}

extern const WideFieldParse WideTblA00753A80[];

class Rva00753A80
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00753A80::buildFieldParse( WideMulti &p )
{
	p.add( WideTblA00753A80, 0 );
	Gen00022584::buildFieldParse( p );
}
