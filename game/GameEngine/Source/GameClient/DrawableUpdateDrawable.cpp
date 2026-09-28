// ?updateDrawable@Drawable@@QAEXXZ  retail 0x0041BE60, 2437 bytes (ret at +0x984).
// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
//
// Identity: matched StealthUpdate::changeVisualDisguise (0x002AC620) reaches this
// body through ILT 0x00031C55 right after binding the replacement Drawable.
// The 0x010F1410 vtable belongs to the 0x50-byte TintEnvelope objects built here;
// TintEnvelope::play (0x004156D0) is called on them.
//
// Two retail facts shape the spelling:
//   * RGBColor::setFromInt is out of line in retail: about eight callers in
//     other TUs reach 0x00083370 through ILT 0x0002CDC7 and none inline it.
//     The 0xffffffff reset at +0x680 is that call; the flash colour at +0x428
//     is open-coded, not a setFromInt call.
//   * The TintEnvelope vtable immediate appears only in the out-of-line ctor
//     (0x00412140) and at +0x4B0 and +0x535 here; every other construction in
//     the image (colorFlash, 0x0041A2E0, xfer, +0x5DD/+0x634/+0x6B3 here)
//     calls the ctor through ILT 0x00037475. A single ctor cannot produce that
//     split, so the bit-1 and bit-8 sites use a second, inline ctor. Its
//     parameter is not witnessed (an inlined ctor leaves no argument behind).
//     No retail body is ever called as that ctor, so its name is not pinned
//     and claims no retail address.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" float __cdecl sinf(float value);

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real Normalize(void);
	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
	void sub(const Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
	void scale(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;

	void setFromInt(Int color);
};

class Matrix3D
{
	Real m_rows[12];
};

class ModelConditionFlags
{
public:
	UnsignedInt m_bits[10];
	void clearAndSet(const ModelConditionFlags &clr, const ModelConditionFlags &set);
};

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	void Set(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

class TintEnvelope
{
public:
	TintEnvelope(void);
	explicit TintEnvelope(int)
	{
		m_attackRate.Set(0, 0, 0);
		m_decayRate.Set(0, 0, 0);
		m_peakColor.Set(0, 0, 0);
		m_currentColor.Set(0, 0, 0);
		m_bfme44 = 0;
		m_bfme48 = 0;
		m_bfme4C = 0;
		m_envState = 0;
		m_sustainCounter = 0;
		m_affect = 0;
		m_bfme3C = 0;
		m_bfme40 = 0;
	}

	virtual void bfmeSnapshotSlot00(void);

	void play(const RGBColor *color, UnsignedInt attackFrames,
		UnsignedInt decayFrames, UnsignedInt sustainAtPeak);
	void update(void);
	void setPulse(Real a, Real b)
	{
		m_bfme3C = a;
		m_bfme40 = b;
	}

	Vector3 m_attackRate;
	Vector3 m_decayRate;
	Vector3 m_peakColor;
	Vector3 m_currentColor;
	UnsignedInt m_sustainCounter;
	unsigned char m_envState;
	Bool m_affect;
	Real m_bfme3C;
	Real m_bfme40;
	Int m_bfme44;
	Int m_bfme48;
	Int m_bfme4C;
};

class ModelConditionFlags;
class Drawable;
class Object;

class ObjectDrawInterface
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void replaceModelConditionState(const ModelConditionFlags &flags, Int a, Int b) = 0;
};

class DrawModule
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void setTerrainDecal(Int type) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void setTerrainDecalOpacity(Real opacity) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(const Coord3D *position, const Coord3D *second) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void bfmeSlot29(void) = 0;
	virtual void bfmeSlot30(void) = 0;
	virtual void bfmeSlot31(void) = 0;
	virtual void bfmeSlot32(void) = 0;
	virtual void bfmeSlot33(void) = 0;
	virtual void bfmeSlot34(void) = 0;
	virtual void bfmeSlot35(void) = 0;
	virtual void bfmeSlot36(void) = 0;
	virtual void bfmeSlot37(void) = 0;
	virtual void bfmeSlot38(void) = 0;
	virtual ObjectDrawInterface *getObjectDrawInterface(void) = 0;
	virtual void bfmeSlot40(void) = 0;
	virtual void bfmeSlot41(void) = 0;
	virtual void bfmeSlot42(void) = 0;
	virtual void bfmeSlot43(void) = 0;
	virtual void bfmeSlot44(void) = 0;
	virtual void bfmeSlot45(void) = 0;
	virtual void bfmeSlot46(void) = 0;
	virtual void bfmeSlot47(void) = 0;
	virtual void bfmeSlot48(void) = 0;
	virtual void bfmeSlot49(void) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual void bfmeSlot55(void) = 0;
	virtual void bfmeSlot56(void) = 0;
	virtual void bfmeSlot57(void) = 0;
	virtual void bfmeSlot58(void) = 0;
};

class ClientUpdateModule
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual Bool bfmeSlot09(void) = 0;
	virtual void clientUpdate(void) = 0;
};

class ClientRoot4120
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void destroyDrawable(Drawable *draw) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual UnsignedInt getFrame(void) = 0;
};

class Object
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual Drawable *getDrawable(void) = 0;

	const Coord3D *bfmeGetPosition421AE(Coord3D *position, Coord3D *second);
	Object *bfmeResolveMeleeTarget(Int which);

	unsigned char m_bfmeHead04[0x04];
	Matrix3D m_transform;
	unsigned char m_bfmePad38[0x118 - 0x38];
	UnsignedInt m_bfmeStatus118;
	unsigned char m_bfmePad11C[0x344 - 0x11C];
	UnsignedInt m_bfmeStatus344;
};

class GameEngine
{
public:
	unsigned char m_bfmePad00[0x30];
	Int m_bfme30;
};

class GameLogic
{
public:
	unsigned char m_bfmePad00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;
extern GameEngine *TheGameEngine;
extern ClientRoot4120 *TheGameClient;
extern const RGBColor g_rva00CF1058TintColor;
extern const RGBColor g_rva00CF1064TintColor;
extern Real g_rva00EB4F98;

class Thing
{
public:
	void rva00132200(const Matrix3D *transform);
};

template <class T>
inline const T &bfmeMin(const T &a, const T &b)
{
	return a < b ? a : b;
}

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return a < b ? b : a;
}

class Drawable : public Thing
{
public:
	void updateDrawable(void);
	void colorFlash(const RGBColor *color, UnsignedInt decayFrames = 4,
		UnsignedInt attackFrames = 0, UnsignedInt sustainAtPeak = 0);
	void bfmeSetOpacity412430(Real opacity);
	void bfmeRefresh411CD0(void);

	void **getModuleList(Int which) { return m_modules150[which]; }
	DrawModule **getDrawModules(void) { return (DrawModule **)getModuleList(0); }
	ClientUpdateModule **getClientUpdateModules(void) { return (ClientUpdateModule **)getModuleList(1); }

	void setTerrainDecal(Int type)
	{
		if (m_terrainDecalTypeA8 == type)
			return;
		m_terrainDecalTypeA8 = type;
		DrawModule **dm = getDrawModules();
		if (*dm)
			(*dm)->setTerrainDecal(type);
	}

	void bfmeBlend(Real target)
	{
		Real total = m_bfmeC0 * 30.0f;
		Real ratio = (total - (Real)m_bfmeD4) / total;
		if (m_bfmeD4 > 0)
			--m_bfmeD4;
		m_bfmeB4 = (1.0f - ratio) * m_bfmeD0 + ratio * target;
	}

	unsigned char m_bfmePad00[0x64];
	TintEnvelope *m_selectionFlashEnvelope64;
	TintEnvelope *m_colorTintEnvelope;
	RGBColor m_tintColor6C;
	UnsignedInt m_tintAttack78;
	UnsignedInt m_tintDecay7C;
	UnsignedInt m_tintSustain80;
	Real m_tintParam84;
	Real m_tintParam88;
	unsigned char m_bfmePad8C[0xA8 - 0x8C];
	Int m_terrainDecalTypeA8;
	unsigned char m_bfmePadAC[0x04];
	Real m_opacityB0;
	Real m_bfmeB4;
	Real m_bfmeB8;
	Real m_bfmeBC;
	Real m_bfmeC0;
	Real m_bfmeC4;
	Real m_bfmeC8;
	Real m_bfmeCC;
	Real m_bfmeD0;
	UnsignedInt m_bfmeD4;
	unsigned char m_bfmePadD8[0x04];
	Real m_decalFadeRateDC;
	Real m_decalOpacityE0;
	unsigned char m_bfmeE4;
	unsigned char m_bfmePadE5[0xF4 - 0xE5];
	Real m_bfmeF4;
	Real m_bfmeF8;
	Object *m_object;
	unsigned char m_bfmePad100[0x114 - 0x100];
	UnsignedInt m_tintStatus114;
	UnsignedInt m_prevTintStatus118;
	unsigned char m_bfmePad11C[0x124 - 0x11C];
	Int m_fadeMode124;
	UnsignedInt m_timeElapsedFade128;
	UnsignedInt m_timeToFade12C;
	UnsignedInt m_bfme130;
	unsigned char m_bfmePad134[0x150 - 0x134];
	void **m_modules150[2];
	unsigned char m_bfmePad158[0x160 - 0x158];
	Int m_flashCount160;
	Int m_flashColor164;
	unsigned char m_bfmePad168[0x250 - 0x168];
	ModelConditionFlags m_conditionState250;
	ModelConditionFlags m_conditionClear278;
	ModelConditionFlags m_conditionSet2A0;
	unsigned char m_bfmePad2C8[0x2DC - 0x2C8];
	UnsignedInt m_expirationDate2DC;
	unsigned char m_bfmePad2E0[0x308 - 0x2E0];
	UnsignedInt m_lastFadeFrame308;
	UnsignedInt m_lastDecalFrame30C;
	unsigned char m_bfmePad310[0x319 - 0x310];
	unsigned char m_bfme319;
	unsigned char m_bfmePad31A[0x3AC - 0x31A];
	unsigned char m_bfme3AC;
	Bool m_bfme3AD;
	unsigned char m_bfmePad3AE[0x3B1 - 0x3AE];
	unsigned char m_bfme3B1;
	unsigned char m_bfme3B2;
	unsigned char m_bfme3B3;
};

void Drawable::updateDrawable(void)
{
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	Object *obj = m_object;

	if (TheGameEngine->m_bfme30 == 1 && m_bfme3B3)
	{
		m_conditionState250.clearAndSet(m_conditionClear278, m_conditionSet2A0);
		for (DrawModule **dm = getDrawModules(); *dm; ++dm)
		{
			ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
			if (di)
				di->replaceModelConditionState(m_conditionState250, 0, 0);
		}
		m_bfme3B3 = 0;
	}

	if (obj && (obj->m_bfmeStatus118 & 0x10))
	{
		for (DrawModule **dm = getDrawModules(); *dm; ++dm)
			(*dm)->bfmeSlot58();
	}

	if (m_bfme3B1)
	{
		if (obj && !m_bfme319)
		{
			rva00132200(&obj->m_transform);
			m_bfme319 = 1;
		}
		for (ClientUpdateModule **cu = getClientUpdateModules(); cu && *cu; ++cu)
			(*cu)->clientUpdate();
		m_bfme3B2 = 1;
	}
	else
	{
		for (ClientUpdateModule **cu = getClientUpdateModules(); cu && *cu; ++cu)
		{
			if (!(*cu)->bfmeSlot09())
				(*cu)->clientUpdate();
		}
		if (m_bfme3B2)
		{
			m_bfme3B2 = 0;
			for (DrawModule **dm = getDrawModules(); *dm; ++dm)
				(*dm)->bfmeSlot33();
		}
	}

	if (m_fadeMode124 != 0)
	{
		UnsignedInt frame = TheGameClient->getFrame();
		UnsignedInt delta = frame - m_lastFadeFrame308;
		m_lastFadeFrame308 = frame;
		m_timeElapsedFade128 = bfmeMin(m_timeElapsedFade128 + delta, m_timeToFade12C);
		if (m_fadeMode124 < 3)
		{
			UnsignedInt numer = (m_fadeMode124 == 1) ? m_timeElapsedFade128 :
				(m_timeToFade12C - m_timeElapsedFade128);
			m_opacityB0 = (Real)numer / (Real)m_timeToFade12C;
			if (m_timeElapsedFade128 >= m_timeToFade12C)
				m_fadeMode124 = 0;
		}
		else if (m_timeToFade12C == m_timeElapsedFade128)
		{
			Bool hidden = (m_fadeMode124 == 4);
			if (hidden != m_bfme3AD)
			{
				m_bfme3AD = hidden;
				bfmeRefresh411CD0();
			}
			if (m_fadeMode124 == 5)
			{
				m_opacityB0 = 0.0f;
				m_fadeMode124 = 1;
				m_timeToFade12C = m_bfme130;
				m_timeElapsedFade128 = 0;
				m_lastFadeFrame308 = TheGameClient->getFrame();
			}
		}
	}

	if (m_bfmeE4)
	{
		m_bfmeF4 += m_bfmeF8;
		if (m_bfmeF4 < 0.0f)
			m_bfmeF4 = 0.0f;
		if (m_bfmeF4 > 1.0f)
			m_bfmeF4 = 1.0f;
		bfmeSetOpacity412430(m_bfmeF4);
	}

	if (m_terrainDecalTypeA8 != 7)
	{
		DrawModule **dm = getDrawModules();
		if (*dm)
		{
			if (m_decalFadeRateDC != 0.0f)
			{
				UnsignedInt frame = TheGameClient->getFrame();
				Int delta = frame - m_lastDecalFrame30C;
				Int one = 1;
				Int steps = bfmeMax(delta, one);
				m_lastDecalFrame30C = frame;
				(*dm)->setTerrainDecalOpacity(m_decalOpacityE0);
				m_decalOpacityE0 += steps * m_decalFadeRateDC;
			}

			if (m_decalFadeRateDC < 0.0f && m_decalOpacityE0 <= 0.0f)
			{
				m_decalFadeRateDC = 0.0f;
				m_decalOpacityE0 = 0.0f;
				setTerrainDecal(7);
			}
			else if (m_decalFadeRateDC > 0.0f && m_decalOpacityE0 >= 1.0f)
			{
				m_decalOpacityE0 = 1.0f;
				m_decalFadeRateDC = 0.0f;
				(*dm)->setTerrainDecalOpacity(m_decalOpacityE0);
			}
		}
	}
	else
		m_decalOpacityE0 = 0.0f;

	if (m_expirationDate2DC != 0 && now >= m_expirationDate2DC)
	{
		TheGameClient->destroyDrawable(this);
		return;
	}

	if (m_flashCount160 > 0 && (TheGameClient->getFrame() % 15) == 0)
	{
		RGBColor tmp;
		const Real scale = 1.0f / 255.0f;
		tmp.red = (Real)((m_flashColor164 >> 16) & 0xff) * scale;
		tmp.green = (Real)((m_flashColor164 >> 8) & 0xff) * scale;
		tmp.blue = (Real)(m_flashColor164 & 0xff) * scale;
		colorFlash(&tmp);
		m_flashCount160--;
	}

	if (m_prevTintStatus118 != m_tintStatus114)
	{
		if (m_tintStatus114 & 0x1)
		{
			if (m_colorTintEnvelope == 0)
				m_colorTintEnvelope = new TintEnvelope(0);
			m_colorTintEnvelope->play(&g_rva00CF1058TintColor, 30, 30, 0xfffffffe);
			m_colorTintEnvelope->setPulse(0.0f, 0.0f);
		}
		else if (m_tintStatus114 & 0x8)
		{
			if (m_colorTintEnvelope == 0)
				m_colorTintEnvelope = new TintEnvelope(0);
			m_colorTintEnvelope->play(&g_rva00CF1064TintColor, 30, 30, 300);
			m_colorTintEnvelope->setPulse(0.25f, 0.05f);
			m_tintStatus114 = 0;
			m_prevTintStatus118 = 0;
		}
		else if (m_tintStatus114 & 0x10)
		{
			if (m_colorTintEnvelope == 0)
				m_colorTintEnvelope = new TintEnvelope;
			m_colorTintEnvelope->play(&g_rva00CF1064TintColor, 30, 30, 9999);
			m_colorTintEnvelope->setPulse(0.0f, 0.0f);
			m_tintStatus114 = 0;
			m_prevTintStatus118 = 0;
		}
		else if (m_tintStatus114 & 0x20)
		{
			if (m_colorTintEnvelope == 0)
				m_colorTintEnvelope = new TintEnvelope;
			m_colorTintEnvelope->play(&m_tintColor6C, m_tintAttack78, m_tintDecay7C, m_tintSustain80);
			m_colorTintEnvelope->setPulse(m_tintParam84, m_tintParam88);
			m_tintStatus114 = 0;
			m_prevTintStatus118 = 0;
			m_tintColor6C.setFromInt(0xffffffff);
			m_tintAttack78 = 0;
			m_tintDecay7C = 0;
			m_tintSustain80 = 0;
			m_tintParam84 = 0.0f;
			m_tintParam88 = 0.0f;
		}
		else
		{
			if (m_colorTintEnvelope == 0)
				m_colorTintEnvelope = new TintEnvelope;
			m_colorTintEnvelope->m_envState = 2;
		}
	}

	m_prevTintStatus118 = m_tintStatus114;
	if (obj && !(obj->m_bfmeStatus344 & 0x1))
		m_tintStatus114 &= ~0x2;

	if (m_colorTintEnvelope)
		m_colorTintEnvelope->update();
	if (m_selectionFlashEnvelope64)
		m_selectionFlashEnvelope64->update();

	if (m_bfmeB8 != m_bfmeBC)
	{
		Real target = sinf(m_bfmeCC) * m_bfmeC8 + m_bfmeC4;
		bfmeBlend(target);
		m_bfmeCC += g_rva00EB4F98 / m_bfmeC0 * 3.14159265359f;
	}
	else
	{
		Real same = (m_bfmeB8 == m_bfmeBC);
		if (same == 1.0f && m_bfmeB4 < 1.0f)
			bfmeBlend(1.0f);
	}

	if (obj)
	{
		if (m_bfme3AC)
		{
			Coord3D position;
			Coord3D second;
			const Coord3D *where = obj->bfmeGetPosition421AE(&position, &second);
			DrawModule **dm = getDrawModules();
			if (*dm)
				(*dm)->bfmeSlot22(where, &second);
			return;
		}

		Object *other = obj->bfmeResolveMeleeTarget(1);
		if (other)
		{
			Drawable *otherDraw = other->getDrawable();
			if (otherDraw && otherDraw->m_bfme3AC)
			{
				Coord3D offset;
				Coord3D position;
				Coord3D second;
				other->bfmeGetPosition421AE(&offset, 0);
				obj->bfmeGetPosition421AE(&position, 0);
				offset.sub(&position);
				if (offset.x * offset.x + offset.y * offset.y + offset.z * offset.z > 0.01f)
				{
					offset.Normalize();
					offset.scale(10.0f);
					position.add(&offset);
				}
				DrawModule **dm = getDrawModules();
				if (*dm)
					(*dm)->bfmeSlot22(&position, &second);
			}
		}
	}
}
