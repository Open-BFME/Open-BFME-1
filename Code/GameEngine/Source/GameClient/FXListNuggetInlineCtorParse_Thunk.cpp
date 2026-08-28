// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: seven more FXList nugget parse callbacks, the ones whose derived
// constructor is INLINE.  Same body as FXListNuggetParse_Thunk.cpp -- allocate,
// build a MultiIniFieldParse from the derived table then FXNugget's shared one,
// initFromINIMulti, push_back onto the FXList -- with the constructor spelled
// out instead of called:
//
//     push <SIZE> ; call ??2@YAPAXI@Z
//     ... je + ; mov ecx,<this> ; call 0x00428590   ; FXNugget's constructor
//     mov [<this>],<DERIVED VFTABLE>
//     <the derived class's own member initialisers>
//   [ mov [<this>+4],<N> ]                          ; a BASE field, so last
//     ...
//
// THE INI KEYWORD TABLE NAMES ALL SEVEN.  Their five-byte incremental-link
// thunks appear in FXList's own FieldParse table at 0x00CF2130 under the
// keywords Sound, EvaEvent, ViewShake, CameraShakerVolume, AttachedModel, Laser
// and TerrainScorch; Zero Hour spells every nugget class <keyword>FXNugget.
//
// THE BASE CONSTRUCTOR IS 0x00428590, NOT THE 9-BYTE BODY THE LEDGER NAMES.
// `??0FXNugget@@QAE@XZ` currently sits on 0x00061D90, which is
// `mov eax,ecx / mov [eax],0 / ret` -- nine bytes that identical-code folding
// shares with hundreds of other one-pointer constructors, and which is the Zero
// Hour FXNugget the ported FXList.cpp describes.  BFME's is 225 bytes at
// 0x00428590: an EH frame, its own vftable at 0x010F23A0, and subobjects from
// +8 on.  All fifteen nugget parse callbacks reach it, and the shared FieldParse
// table they add runs 0x8..0xB3, so that is the constructor of the 0xB4-wide
// base these classes derive from.  A second symbols.csv pin records it; the
// existing row is left alone.
//
// THE FIELD AT +4 IS THE BASE'S AND IT IS WRITTEN LAST.  EvaEvent stores 1,
// CameraShakerVolume 5, and the 401-byte ParticleSysBone row stores 9 -- a
// discriminator the base carries.  It lands after the derived class's own
// initialisers because MSVC runs the member-initialiser list before the
// constructor body, so it is an assignment in the body and not a list entry.
//
// The two STLport defines on the `cl:` line are the same ones
// FXListNuggetParse_Thunk.cpp needs: without _STLP_NO_EXCEPTIONS the list's
// _M_create_node keeps its try block and cannot be inlined, and without
// _STLP_USE_STATIC_LIB the node allocator is reached through __imp_.
//
// Identity beyond the keyword is not recovered: the member names carry their
// offsets.

#include <list>

struct FieldParse;

extern const FieldParse FXNuggetFieldParse[];
extern const FieldParse SoundFXNuggetFieldParse[];
extern const FieldParse EvaEventFXNuggetFieldParse[];
extern const FieldParse ViewShakeFXNuggetFieldParse[];
extern const FieldParse CameraShakerVolumeFXNuggetFieldParse[];
extern const FieldParse AttachedModelFXNuggetFieldParse[];
extern const FieldParse LaserFXNuggetFieldParse[];
extern const FieldParse TerrainScorchFXNuggetFieldParse[];

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
	FXNugget();
	virtual void v0();

	int m_field04;
	char m_unreconstructed_08[ 0xb4 - 8 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	int m_unreconstructed_00;
	std::list<FXNugget *> m_nuggets;

	void addFXNugget( FXNugget *fxn ) { m_nuggets.push_back( fxn ); }
};

// "Sound", parse at 0x0042BBE0, 0xB8 bytes wide
class SoundFXNugget : public FXNugget
{
public:
	SoundFXNugget() : m_soundName( 0 )
	{
		m_field04 = 1;
	}

	static void parse( INI *, void *, void *, const void * );

private:
	char *m_soundName;
};

void SoundFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	SoundFXNugget *nugget = new SoundFXNugget;
	MultiIniFieldParse fields;
	fields.add( SoundFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "ViewShake", parse at 0x0042C320, 0xB8 bytes wide
class ViewShakeFXNugget : public FXNugget
{
public:
	ViewShakeFXNugget() : m_shake( 1 )
	{
		m_field04 = 6;
	}

	static void parse( INI *, void *, void *, const void * );

private:
	int m_shake;
};

void ViewShakeFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	ViewShakeFXNugget *nugget = new ViewShakeFXNugget;
	MultiIniFieldParse fields;
	fields.add( ViewShakeFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "EvaEvent", parse at 0x0042BAA0, 0xC0 bytes wide
class EvaEventFXNugget : public FXNugget
{
public:
	EvaEventFXNugget() : m_fieldB4( -1 ), m_fieldB8( -1 ), m_fieldBC( -1 )
	{
		m_field04 = 1;
	}

	static void parse( INI *, void *, void *, const void * );

	int m_fieldB4, m_fieldB8, m_fieldBC;
};

void EvaEventFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	EvaEventFXNugget *nugget = new EvaEventFXNugget;
	MultiIniFieldParse fields;
	fields.add( EvaEventFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "CameraShakerVolume", parse at 0x0042C1C0, 0xCC bytes wide
class CameraShakerVolumeFXNugget : public FXNugget
{
public:
	// The three HIGHER fields are written first, which a single initialiser
	// list cannot do -- it follows declaration order, and declaration order
	// follows layout.  So 0xC0..0xC8 are the list and 0xB4..0xBC are the body.
	CameraShakerVolumeFXNugget()
		: m_fieldC0( 0 ), m_fieldC4( 0 ), m_fieldC8( 0 )
	{
		m_fieldB4 = 0;
		m_fieldB8 = 0;
		m_fieldBC = 0;
		m_field04 = 5;
	}

	static void parse( INI *, void *, void *, const void * );

	int m_fieldB4, m_fieldB8, m_fieldBC;
	int m_fieldC0, m_fieldC4, m_fieldC8;
};

void CameraShakerVolumeFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	CameraShakerVolumeFXNugget *nugget = new CameraShakerVolumeFXNugget;
	MultiIniFieldParse fields;
	fields.add( CameraShakerVolumeFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "AttachedModel", parse at 0x0042C460, 0xC0 bytes wide
class AttachedModelFXNugget : public FXNugget
{
public:
	AttachedModelFXNugget() : m_fieldB4( 0 ), m_fieldB8( 0 ), m_fieldBC( 0x28 )
	{
	}

	static void parse( INI *, void *, void *, const void * );

	int m_fieldB4;
	char m_fieldB8;
	int m_fieldBC;
};

void AttachedModelFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	AttachedModelFXNugget *nugget = new AttachedModelFXNugget;
	MultiIniFieldParse fields;
	fields.add( AttachedModelFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "Laser", parse at 0x0042C090, 0xC8 bytes wide
class LaserFXNugget : public FXNugget
{
public:
	LaserFXNugget() : m_fieldB4( 0 ), m_fieldB8( 0 )
	{
	}

	static void parse( INI *, void *, void *, const void * );

	int m_fieldB4;
	char m_fieldB8;
	char m_unreconstructed_b9[ 0xc8 - 0xbc + 3 ];
};

void LaserFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	LaserFXNugget *nugget = new LaserFXNugget;
	MultiIniFieldParse fields;
	fields.add( LaserFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}

// "TerrainScorch", parse at 0x0042C600, 0xBC bytes wide
class TerrainScorchFXNugget : public FXNugget
{
public:
	TerrainScorchFXNugget() : m_scorch( -1 ), m_radius( 0 )
	{
		m_field04 = 7;
	}

	static void parse( INI *, void *, void *, const void * );

private:
	int m_scorch;
	float m_radius;
};

void TerrainScorchFXNugget::parse( INI *ini, void *instance, void *, const void * )
{
	TerrainScorchFXNugget *nugget = new TerrainScorchFXNugget;
	MultiIniFieldParse fields;
	fields.add( TerrainScorchFXNuggetFieldParse );
	fields.add( FXNuggetFieldParse );
	ini->initFromINIMulti( nugget, fields );
	( (FXList *)instance )->addFXNugget( nugget );
}
