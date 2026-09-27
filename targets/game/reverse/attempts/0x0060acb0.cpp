// ?create@Rva0060ACB0Owner@@SGPAVRva0060ACB0Object@@ABVAsciiString@@MMPAVRva0060ACB0Record@@H_N@Z
// partial score=0.96 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug

#include "string_base.h"
#include "vector3.h"

template <> inline StringBase<char>::StringBase()
{
	m_data = 0;
}

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) throw() : StringBase<char>(other) {}
	~AsciiString() throw() {}
	const char *str() const { return StringBase<char>::str(); }
	void __cdecl format(AsciiString fmt, ...);
	void set(const AsciiString &other) { StringBase<char>::set(other); }
};

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

class RenderObjClass;
class BfmeHostESM;
class BfmeGameCW;
class Rva003BC9A0;

extern "C" void *bfmeVftableBG[];
extern float g_01075954;
extern BfmeHostESM *g_bfmeStateDF;
extern BfmeGameCW *g_bfmeGameCW;
extern Rva003BC9A0 *Glo012F1028;

class Rva0061DA30Base
{
public:
	Rva0061DA30Base(AsciiString name) throw();
};

class Rva0060ACB0Object : public Rva0061DA30Base
{
public:
	__forceinline Rva0060ACB0Object(const AsciiString &name)
		: Rva0061DA30Base(name)
	{
		m_vftable = (int *)bfmeVftableBG;
		m_flagA0 = 0;
		m_fieldA4 = 0;
		m_fieldA8 = 0;
		m_nameData = 0;
	}

	int *volatile m_vftable;
	int m_word04;
	RenderObjClass *m_renderObject;
	char m_pad0c[0x1c];
	int m_field28;
	char m_pad2c[0x68];
	Vector3 m_field94;
	volatile char m_flagA0;
	char m_padA1[3];
	int m_fieldA4;
	float m_fieldA8;
	int m_nameData;
};

class Rva0060ACB0ObjectView
{
public:
	virtual void slot00(AsciiString);
	virtual void slot04(AsciiString);
	virtual void slot08(AsciiString);
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C(Vector3);
};

class Rva0060ACB0Record
{
public:
	AsciiString m_name0;
	AsciiString m_name4;
	AsciiString m_name8;
	float m_x;
	float m_scale;
	bool m_register;
	bool m_go;
	bool m_rotate;
	float m_angle;
};

struct Rva0060ACB0UnitFrame
{
	Vector3 m_unit;
};

class BfmeAnimationHolder
{
public:
	void applyScalePayload(float);
	void applyRotationPayload(float);
};

class BfmeThingNB
{
public:
	void bfmeGoNB(char);
};

class Rva003BC9A0
{
public:
	int advance();
};

class BfmeHostView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28(RenderObjClass *);
};

class BfmeGameCW
{
public:
	void rva00616240(void *, int, int);
};

void Rva00739B30(RenderObjClass *, bool);

class Rva0060ACB0Owner
{
public:
	static Rva0060ACB0Object *__stdcall create(const AsciiString &name, float x, float y,
		Rva0060ACB0Record *record, int id, bool registerObject);
};

Rva0060ACB0Object *__stdcall Rva0060ACB0Owner::create(const AsciiString &name, float x,
	float y, Rva0060ACB0Record *record, int id, bool registerObject)
{
	AsciiString objectName;
	objectName.format("%s:%d", name.str(), id);
	Rva0060ACB0Object *object = new Rva0060ACB0Object(objectName);
	if (object == 0)
		return object;
	Rva0060ACB0ObjectView *view =
		reinterpret_cast<Rva0060ACB0ObjectView *>(object);
	view->slot00(record->m_name0);
	view->slot04(record->m_name4);
	Rva00739B30(object->m_renderObject, false);
	object->m_fieldA8 = record->m_x;
	view->slot1C(Vector3(y, x, record->m_x));
	reinterpret_cast<BfmeAnimationHolder *>(object)->applyScalePayload(record->m_scale);

	AsciiString animationName;
	animationName.format("%s.%s", record->m_name0.str(), record->m_name0.str());
	view->slot08(animationName);
	RenderObjClass *renderObject = object->m_renderObject;
	reinterpret_cast<BfmeHostView *>(g_bfmeStateDF)->slot28(renderObject);
	object->m_fieldA4 = Glo012F1028->advance();
	if (record->m_register)
	{
		if (registerObject)
			g_bfmeGameCW->rva00616240(object, 1, object->m_fieldA4);
		else
			g_bfmeGameCW->rva00616240(object, 0, object->m_fieldA4);
	}
	reinterpret_cast<BfmeThingNB *>(object)->bfmeGoNB(record->m_go == 0);
	reinterpret_cast<AsciiString *>(&object->m_nameData)->set(record->m_name8);
	if (record->m_rotate)
	{
		Rva0060ACB0UnitFrame unitFrame;
		unitFrame.m_unit = Vector3(1.0f, 1.0f, 1.0f);
		volatile Vector3 *unitView = &unitFrame.m_unit;
		object->m_field94.X = unitView->X;
		object->m_field94.Y = unitView->Y;
		object->m_field94.Z = unitView->Z;
		object->m_field28 = 1;
		reinterpret_cast<BfmeAnimationHolder *>(object)->applyRotationPayload(
			record->m_angle * g_01075954);
	}
	return object;
}
