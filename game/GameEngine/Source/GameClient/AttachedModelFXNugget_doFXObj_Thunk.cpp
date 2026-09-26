// ?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z
// Open-BFME5: clean C++ conversion of the AttachedModel object dispatch.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

class Drawable
{
public:
	void attachModel(AsciiString, bool, int);
};

#define BFME_OBJECT_SLOT( name ) virtual void name();
class Object
{
public:
	BFME_OBJECT_SLOT(v00) BFME_OBJECT_SLOT(v04)
	BFME_OBJECT_SLOT(v08) BFME_OBJECT_SLOT(v0C)
	BFME_OBJECT_SLOT(v10) BFME_OBJECT_SLOT(v14)
	BFME_OBJECT_SLOT(v18) BFME_OBJECT_SLOT(v1C)
	BFME_OBJECT_SLOT(v20) BFME_OBJECT_SLOT(v24)
	virtual Drawable *getDrawable() const;
};
#undef BFME_OBJECT_SLOT

class AttachedModelFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos();
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unmodelled[0xB0];
	AsciiString m_modelName;
	bool m_randomlyRotate;
	unsigned char m_padding[3];
	int m_expireTimer;
};

// ?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z
void AttachedModelFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		if (primary->getDrawable())
			primary->getDrawable()->attachModel(m_modelName, m_randomlyRotate,
				m_expireTimer);
	}
}
