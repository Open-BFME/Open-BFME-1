// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Drawable::setStealthLook, BFME's four-argument form, retail 0x00416820
// (390 B plus its six-entry case table, 416 B). Identity: the matched
// StealthUpdate::changeVisualDisguise 0x00267D80 calls ILT 0x0000F763 with
// (2, 0.2f, 0.7f, 2.0f) and ilt_oracle CONFIRMS this spelling; the body uses
// the Drawable.cpp source literal. The ZH one-argument setStealthLook stays
// in Drawable.cpp; this TU declares the BFME ABI locally. Structure follows
// ZH's switch (enum in ZH order: retail compares 4 = VISIBLE_FRIENDLY_DETECTED).
// Offsets other than the ZH-named stealth fields keep their addresses.
// The clamp is one value expression (retail keeps it on x87 and stores once),
// and the second module loop re-tests the element so cl drops the 4-byte
// loop-head pad retail does not have (shape_levers "lea or mov edi,edi nop").

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

enum StealthLookType
{
	STEALTHLOOK_NONE,
	STEALTHLOOK_VISIBLE_FRIENDLY,
	STEALTHLOOK_DISGUISED_ENEMY,
	STEALTHLOOK_VISIBLE_DETECTED,
	STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED,
	STEALTHLOOK_INVISIBLE
};

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file,
	Int line);

// Drawable's BFME module list calls an unlabelled module vtable entry at
// +0xE0.  Keeping all preceding entries explicit makes the call ABI honest
// without assigning a semantic name that the retail image does not provide.
class BfmeDrawableStealthModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0(Bool value) = 0;
};

// The call at retail +0x15B loads this Drawable as ECX and reaches the
// existing 0x000200D1 ILT.  The private declaration reproduces the proven
// Gen_00411DD0 member symbol without adding a new pin or inventing a name for
// the target body.
class Drawable;
class Gen_00411DD0
{
private:
	void bfmeChanged();
	friend class Drawable;
};

class Drawable
{
private:
	UnsignedByte m_pad000[0xB4];
	UnsignedInt m_valueB4;
	Real m_valueB8;
	Real m_valueBC;
	Real m_valueC0;
	Real m_valueC4;
	Real m_valueC8;
	Real m_valueCC;
	UnsignedInt m_valueD0;
	Int m_valueD4;
	UnsignedByte m_pad0D8[0x78];
	BfmeDrawableStealthModule **m_modules; // +0x150
	UnsignedByte m_pad154[0x08];
	StealthLookType m_stealthLook; // +0x15C
	UnsignedByte m_pad160[0x184];
	Real m_secondMaterialPassOpacity; // +0x2E4
	UnsignedByte m_pad2E8[0x33];
	Bool m_flag31B;
	UnsignedByte m_pad31C[0x92];
	Bool m_hiddenByStealth; // +0x3AE

public:
	void setStealthLook(StealthLookType look, Real first, Real second,
		Real third);
};

void Drawable::setStealthLook(StealthLookType look, Real first, Real second,
	Real third)
{
	if (look != m_stealthLook)
	{
		m_valueBC = 1.0f;
		m_valueB8 = 1.0f;
		m_valueC0 = third < 0.1f ? 0.1f : (third > 60.0f ? 60.0f : third);
		m_valueD4 = (Int)(third * 30.0f);
		m_valueD0 = m_valueB4;
		m_stealthLook = look;

		switch (look)
		{
			case STEALTHLOOK_NONE:
				m_hiddenByStealth = false;
				m_secondMaterialPassOpacity = 0.0f;
				break;

			case STEALTHLOOK_VISIBLE_FRIENDLY:
			case STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED:
				m_valueC4 = (first + second) * 0.5f;
				m_valueB8 = first;
				m_valueC8 = (second - first) * 0.5f;
				m_valueBC = second;
				m_valueCC = GetGameClientRandomValueReal(0.0f, 3.1415927f,
					"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable.cpp", 0xD9C);
				m_hiddenByStealth = false;
				if (look == STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED)
					m_secondMaterialPassOpacity = 1.0f;
				else
					m_secondMaterialPassOpacity = 0.0f;
				break;

			case STEALTHLOOK_DISGUISED_ENEMY:
				m_hiddenByStealth = false;
				m_secondMaterialPassOpacity = 0.0f;
				break;

			case STEALTHLOOK_VISIBLE_DETECTED:
				m_hiddenByStealth = false;
				m_secondMaterialPassOpacity = 1.0f;
				break;

			case STEALTHLOOK_INVISIBLE:
				m_hiddenByStealth = !m_flag31B;
				m_secondMaterialPassOpacity = 0.0f;
				break;
		}

		for (BfmeDrawableStealthModule **module = m_modules; *module; ++module)
			(*module)->slotE0(true);
		(reinterpret_cast<Gen_00411DD0 *>(this))->bfmeChanged();
		BfmeDrawableStealthModule **m2 = m_modules;
		while (*m2)
		{
			BfmeDrawableStealthModule *mod = *m2;
			if (mod)
				mod->slotE0(false);
			m2++;
		}
	}
}
