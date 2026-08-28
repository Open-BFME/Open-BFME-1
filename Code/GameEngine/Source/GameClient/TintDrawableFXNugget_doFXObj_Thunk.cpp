// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of TintDrawable's object dispatch.

typedef float Real;
typedef unsigned int UnsignedInt;

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class Drawable
{
public:
	void bfmeApplyTint(RGBColor color, UnsignedInt preColorTime,
		UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
		Real frequency, Real amplitude);

	unsigned char m_unmodelled[0x114];
	UnsignedInt m_status;
};

#define BFME_OBJECT_SLOT(name) virtual void name();

class Object
{
public:
	BFME_OBJECT_SLOT(v00)
	BFME_OBJECT_SLOT(v04)
	BFME_OBJECT_SLOT(v08)
	BFME_OBJECT_SLOT(v0C)
	BFME_OBJECT_SLOT(v10)
	BFME_OBJECT_SLOT(v14)
	BFME_OBJECT_SLOT(v18)
	BFME_OBJECT_SLOT(v1C)
	BFME_OBJECT_SLOT(v20)
	BFME_OBJECT_SLOT(v24)
	virtual Drawable *getDrawable() const;
};

#undef BFME_OBJECT_SLOT

struct Coord3D;
class Matrix3D;

class TintDrawableFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, Real,
		const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unmodelled[0xB0];
	RGBColor m_color;
	UnsignedInt m_preColorTime;
	UnsignedInt m_postColorTime;
	UnsignedInt m_sustainedColorTime;
	Real m_frequency;
	Real m_amplitude;
};

// ?doFXObj@TintDrawableFXNugget@@UBEXPBVObject@@0@Z
void TintDrawableFXNugget::doFXObj(const Object *primary,
	const Object *) const
{
	if (primary && primary->getDrawable())
	{
		Drawable *tintDrawable = primary->getDrawable();
		tintDrawable->m_status |= 0x20;
		primary->getDrawable()->bfmeApplyTint(m_color, m_preColorTime,
			m_postColorTime, m_sustainedColorTime, m_frequency,
			m_amplitude);
	}
}
