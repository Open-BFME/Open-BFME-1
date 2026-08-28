// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: the FXList nugget parse callbacks whose Zero Hour layouts differ
// from BFME.  The out-of-line-constructor bodies are identical bar
// three fields -- an allocation size, a constructor and one FieldParse table:
//
//     push -1 ; push <__ehhandler> ; ... ; sub esp,0x88 ; push ebx,esi,edi
//     push <SIZE> ; call ??2@YAPAXI@Z ; add esp,4       ; new <Nugget>
//     xor ebx,ebx ; cmp eax,ebx ; mov [esp+0x9C],ebx    ; unwind state 0
//     je + ; mov ecx,eax ; call <CTOR> ; mov edi,eax ; jmp + ; xor edi,edi
//     mov [esp+0x9C],-1                                ; unwind state -1
//     mov [esp+0x90],ebx ; <zero two 16-dword arrays>  ; MultiIniFieldParse p
//     push ebx ; push <DERIVED TABLE> ; lea ecx,[esp+0x18] ; call add
//     push ebx ; push 0x010F2480      ; lea ecx,[esp+0x18] ; call add
//     mov ecx,[esp+0xA4] ; lea eax,[esp+0x10] ; push eax ; push edi
//     call ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z
//     mov ecx,[esp+0xA8] ; mov esi,[ecx+4] ; push 0xC ; call _M_allocate
//     lea ecx,[eax+8] ; cmp ecx,ebx ; je + ; mov [ecx],edi
//     <splice the node in front of esi> ; epilogue
//
// THE INI KEYWORD TABLE NAMES ALL EIGHT.  Each parse function is reached from
// .rdata at 0x00CF2130 through its five-byte incremental-link thunk, and that
// table is FXList's own FieldParse: sixteen `{ keyword, parse, 0, 0 }` rows plus
// `{ "PlayEvenIfShrouded", <proc>, 0, 0x10 }`.  The rows this file converts are
// LightPulse, RayEffect, DynamicDecal, TintDrawable, FXListAtBonePos,
// ParticleSystem, CursorParticleSystem and BuffNugget.  Zero Hour spells every
// one of its eight nugget classes as <keyword>FXNugget, and one of these eight
// constructors -- 0x00429F80 --
// is ALREADY claimed as ??0ParticleSystemFXNugget@@QAE@XZ by an unrelated body.
// The keyword is the evidence; the FXNugget suffix on the four BFME-only names
// is that convention, not a separate proof.
//
// THE BASE IS 0xB4 WIDE AND EVERY ROW AGREES.  The second table each row adds
// is the SAME address in all eight, and its fields -- ObjectFilter,
// SourceObjectFilter, Required/ExcludedSecondaryModelConditions,
// Required/ExcludedSourceModelConditions, StopIfNuggetPlayed -- run from 0x8 to
// 0xB0, a Bool ending at 0xB3.  Every derived table starts at 0xB4.  So the
// shared table is FXNugget's own field parse and the derived classes begin
// exactly where it ends; the sizes pushed to operator new then give each
// derived class its width.
//
// TWO STLPORT CONFIGURATION FACTS ARE LOAD-BEARING.  `_M_create_node` carries
// `_STLP_TRY`/`_STLP_UNWIND`, and MSVC 7.1 will not inline a function
// containing a try block -- retail inlines it, so retail built STLport with
// _STLP_NO_EXCEPTIONS even though the game code itself has an EH frame here.
// And `__node_alloc::allocate` is dllimport unless _STLP_USE_STATIC_LIB is
// defined, which turns retail's direct `call _M_allocate` into
// `call dword ptr [__imp_...]`.  Without both defines the body is four bytes
// short and one call indirect.
//
// THE ARGUMENT ORDER IS THE NUGGET FIRST.  The MultiIniFieldParse is
// constructed AFTER the new-expression -- the unwind state is 0 across the
// allocation and constructor and -1 by the time the two arrays are zeroed -- so
// the local is declared after the nugget, not before it.
//
// Each row leaves 193 of its 224 bytes concrete; the rest are the EH handler,
// two FieldParse tables and five calls, all relocation sites.

#include <list>

struct FieldParse;

extern const FieldParse FXNuggetFieldParse[];
extern const FieldParse LightPulseFXNuggetFieldParse[];
extern const FieldParse RayEffectFXNuggetFieldParse[];
extern const FieldParse DynamicDecalFXNuggetFieldParse[];
extern const FieldParse TintDrawableFXNuggetFieldParse[];
extern const FieldParse FXListAtBonePosFXNuggetFieldParse[];
extern const FieldParse ParticleSystemFXNuggetFieldParse[];
extern const FieldParse CursorParticleSystemFXNuggetFieldParse[];
extern const FieldParse BuffNuggetFXNuggetFieldParse[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		Count = 0;
		for (int i = 0; i < 16; ++i) {
			Offsets[i] = 0;
			Fields[i] = 0;
		}
	}
	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *Fields[16];
	unsigned int Offsets[16];
	unsigned int Count;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	char m_unreconstructed_00[ 0xb4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	int m_unreconstructed_00;
	std::list<FXNugget *> m_nuggets;

	void addFXNugget( FXNugget *fxn ) { m_nuggets.push_back( fxn ); }
};

// "LightPulse", parse at 0x0042BE30, 0xD0 bytes wide
class LightPulseFXNugget : public FXNugget
{
public:
	LightPulseFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x1c ];
};

void LightPulseFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	LightPulseFXNugget *nugget = new LightPulseFXNugget;
	MultiIniFieldParse fields;
	fields.add( LightPulseFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "RayEffect", parse at 0x0042BD10, 208 bytes wide
class RayEffectFXNugget : public FXNugget
{
public:
	RayEffectFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x1c ];
};

void RayEffectFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	RayEffectFXNugget *nugget = new RayEffectFXNugget;
	MultiIniFieldParse fields;
	fields.add( RayEffectFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "DynamicDecal", parse at 0x0042BF50, 248 bytes wide
class DynamicDecalFXNugget : public FXNugget
{
public:
	DynamicDecalFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x44 ];
};

void DynamicDecalFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	DynamicDecalFXNugget *nugget = new DynamicDecalFXNugget;
	MultiIniFieldParse fields;
	fields.add( DynamicDecalFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "TintDrawable", parse at 0x0042C740, 212 bytes wide
class TintDrawableFXNugget : public FXNugget
{
public:
	TintDrawableFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x20 ];
};

void TintDrawableFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	TintDrawableFXNugget *nugget = new TintDrawableFXNugget;
	MultiIniFieldParse fields;
	fields.add( TintDrawableFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "FXListAtBonePos", parse at 0x0042C860, 188 bytes wide
class FXListAtBonePosFXNugget : public FXNugget
{
public:
	FXListAtBonePosFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x8 ];
};

void FXListAtBonePosFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	FXListAtBonePosFXNugget *nugget = new FXListAtBonePosFXNugget;
	MultiIniFieldParse fields;
	fields.add( FXListAtBonePosFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "ParticleSystem", parse at 0x0042CB80, 296 bytes wide
class ParticleSystemFXNugget : public FXNugget
{
public:
	ParticleSystemFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x74 ];
};

void ParticleSystemFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	ParticleSystemFXNugget *nugget = new ParticleSystemFXNugget;
	MultiIniFieldParse fields;
	fields.add( ParticleSystemFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "CursorParticleSystem", parse at 0x0042CCA0, 236 bytes wide
class CursorParticleSystemFXNugget : public FXNugget
{
public:
	CursorParticleSystemFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x38 ];
};

void CursorParticleSystemFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	CursorParticleSystemFXNugget *nugget = new CursorParticleSystemFXNugget;
	MultiIniFieldParse fields;
	fields.add( CursorParticleSystemFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "BuffNugget", parse at 0x0042D680, 244 bytes wide
class BuffNuggetFXNugget : public FXNugget
{
public:
	BuffNuggetFXNugget();
	static void parse( INI *, void *, void *, const void * );

private:
	char m_unreconstructed_b4[ 0x40 ];
};

void BuffNuggetFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	BuffNuggetFXNugget *nugget = new BuffNuggetFXNugget;
	MultiIniFieldParse fields;
	fields.add( BuffNuggetFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}
