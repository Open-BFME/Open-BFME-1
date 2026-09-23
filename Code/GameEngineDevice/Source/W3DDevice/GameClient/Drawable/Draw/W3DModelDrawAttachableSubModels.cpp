// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: W3DModelDraw attachable-submodel pass, retail 0x00769720, 863 bytes.
//
// OWNER. Both callers are slot 61 (+0xF4) of the W3DModelDraw vtable family:
// 0x00778590 (shared by the six tables at 0x01122EA8, 0x01123390, 0x01123D38,
// 0x011256D0, 0x01125AB0, 0x011265B0) calls it through ILT 0x00009129 at
// +0x8BE, and the override at 0x00755F70 (table 0x01122470) at +0x5CE, each
// with its own `this` in ecx right after looping over the render object's
// Get_Num_Bones. The body reads m_renderObject at +0x34, the witnessed
// W3DModelDraw layout (name_oracle W3DModelDraw+0x34). No surviving name
// proves the method's spelling, so it keeps the address token.
//
// WHAT IT DOES, straight off retail. For each 0x6C-byte record in the vector
// at module data +0x08 whose (condition flags & mask) equals its value, look
// the record's bone up by name; pick one model from the record's weighted list
// with a roll in [0,100) seeded from the drawable's word at +0x2F0 (three
// 1103515245/12345 LCG steps, >>10, %100); create it, clear its collision
// type recursively, and attach it to the bone at the record's offset. A
// missing bone or model is reported ("Could not find bone '" / "Could not find
// model '" ... "' for attachable submodel in " + the render object's name) and
// the record's value flags are flipped, so the match cannot succeed again.
//
// SPELLINGS THE BYTES DECIDE. The three LCG steps are three statements: a
// `for (i < 3)` loop compiles to the same arithmetic but swaps the registers
// of the weighted-choice scan (end in eax, weight in ecx; retail has them the
// other way round). The value flip is `bitset<304>::flip()` twice: MSVC keeps
// the bone-miss call out of line (REL32 through ILT 0x0003A788 to 0x001C3CD0)
// and inlines the model-miss one, exactly as retail does.
//
// RenderObjClass is a slot shim rather than WW3D2/rendobj.h: that header pulls
// WWLib/always.h, whose placement operator new[] collides with STLport's <new>
// (C2084 either include order), and STLport is required for the bitset<304>
// flip symbol. Slots: Delete_This 0 (WWLib/refcount.h), Get_Name 6 (+0x18),
// Add_Sub_Object_To_Bone(subobj, int bone, const Vector3 *) 37 (+0x94),
// _bfme_ro_v40 40 (+0xA0), Get_Bone_Index 49 (+0xC4), all per the reconciled
// BFME rendobj.h; Set_Collision_Type 120 (+0x1E0) per W3DModelDraw::setSelectable
// at 0x0075C2B0, which pairs it with Get_Collision_Type at +0x1DC.

#include <bitset>
#include <vector>

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

// Retail's empty-string sentinel (DIR32 at +0x121, +0x182, +0x223, +0x27B).
extern char Rva006A16B0Empty[];

// Retail inlines AsciiString::str() at every use; ascii_string.h forwards it
// to the out-of-line StringBase<char>::str().
static const char *inlineStr(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text ? text + 8 : Rva006A16B0Empty;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <size_t NUMBITS>
class BitFlags
{
public:
	_STL::bitset<NUMBITS> m_bits;
};

// BFME's model-condition set is 304 bits (parseModelConditionFlags at 0x0076A580
// takes a BitFlags<304>); the ten-word copy and compare here are that width.
typedef BitFlags<304> ModelConditionFlags;

struct Vector3
{
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual const char *Get_Name() const;
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual int Add_Sub_Object_To_Bone(RenderObjClass *subobj, int bone_index, const Vector3 *offset);
	virtual void slot38(); virtual void slot39();
	virtual void _bfme_ro_v40();
	virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48();
	virtual int Get_Bone_Index(const char *bonename);
	virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115();
	virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void Set_Collision_Type(int type, bool recurse);

	// WWLib/refcount.h: inline in retail, Delete_This at slot 0.
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

RenderObjClass *Create_Render_Obj(const char *name);

// The release-build report stream: TheBfmeAwakenDebug (0x01336E5C) slot 0x60,
// then slot 0x6C hands back the log that the message parts are streamed into.
class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

// 8-byte element of the record's model list: the name handed to
// Create_Render_Obj and the weight subtracted from the percent roll.
struct AttachableSubModelChoice00769720
{
	AsciiString m_modelName;
	UnsignedInt m_percent;
};

// 0x6C-byte record: +0x00 bone name, +0x04 attach offset, +0x10 model list,
// +0x1C condition mask, +0x44 condition value.
struct AttachableSubModel00769720
{
	AsciiString m_boneName;
	Vector3 m_offset;
	_STL::vector<AttachableSubModelChoice00769720> m_models;
	ModelConditionFlags m_conditionMask;
	mutable ModelConditionFlags m_conditionValue;
};

class Drawable
{
public:
	unsigned char m_pad000[0x2f0];
	UnsignedInt m_dword2F0;		// seeds the model roll
};

class W3DModelDrawModuleData
{
public:
	unsigned char m_pad00[0x08];
	_STL::vector<AttachableSubModel00769720> m_attachableSubModels;
};

class W3DModelDraw
{
public:
	void rva00769720();

private:
	unsigned char m_pad00[0x04];
	const W3DModelDrawModuleData *m_moduleData;	// Module +0x04
	Drawable *m_drawable;				// DrawableModule +0x08
	unsigned char m_pad0C[0x34 - 0x0C];
	RenderObjClass *m_renderObject;			// +0x34
	unsigned char m_pad38[0x148 - 0x38];
	ModelConditionFlags m_conditionFlags148;
};

// ?rva00769720@W3DModelDraw@@QAEXXZ
void W3DModelDraw::rva00769720()
{
	if (m_moduleData->m_attachableSubModels.empty() || m_renderObject == 0)
		return;

	m_renderObject->_bfme_ro_v40();

	const Drawable *draw = m_drawable;
	const W3DModelDrawModuleData *d = m_moduleData;
	for (_STL::vector<AttachableSubModel00769720>::const_iterator it = d->m_attachableSubModels.begin();
		it != d->m_attachableSubModels.end(); ++it)
	{
		ModelConditionFlags tmp = m_conditionFlags148;
		tmp.m_bits &= it->m_conditionMask.m_bits;
		if (!(tmp.m_bits == it->m_conditionValue.m_bits))
			continue;

		Int bone = m_renderObject->Get_Bone_Index(inlineStr(it->m_boneName));
		if (bone == 0)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				TheBfmeAwakenDebug->slot6C(bone, bone)
					->slot38("Could not find bone '")
					->slot38(inlineStr(it->m_boneName))
					->slot38("' for attachable submodel in ")
					->slot38(m_renderObject->Get_Name())
					->slot4C(2);
			}
			it->m_conditionValue.m_bits.flip();
			continue;
		}

		UnsignedInt seed = draw->m_dword2F0;
		seed = seed * 0x41c64e6d + 0x3039;
		seed = seed * 0x41c64e6d + 0x3039;
		seed = seed * 0x41c64e6d + 0x3039;
		UnsignedInt roll = (seed >> 10) % 100;

		_STL::vector<AttachableSubModelChoice00769720>::const_iterator choice = it->m_models.begin();
		for (; choice != it->m_models.end(); ++choice)
		{
			if (roll < choice->m_percent)
				break;
			roll -= choice->m_percent;
		}

		RenderObjClass *robj = Create_Render_Obj(inlineStr(choice->m_modelName));
		if (robj == 0)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				TheBfmeAwakenDebug->slot6C((Int)robj, (Int)robj)
					->slot38("Could not find model '")
					->slot38(inlineStr(choice->m_modelName))
					->slot38("' for attachable submodel in ")
					->slot38(m_renderObject->Get_Name())
					->slot4C(2);
			}
			it->m_conditionValue.m_bits.flip();
			continue;
		}

		robj->Set_Collision_Type(0, true);
		m_renderObject->Add_Sub_Object_To_Bone(robj, bone, &it->m_offset);
		robj->Release_Ref();
	}
}
