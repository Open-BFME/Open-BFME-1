// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include <list>

class Drawable;
typedef std::list<Drawable *> DrawableList;
typedef std::list<Drawable *>::const_iterator DrawableListCIt;

class BFMESelectionRedirectTemplate : public Overridable
{
private:
	unsigned char m_opaque[0xD4 - sizeof(Overridable)];
	UnsignedInt m_flags;
public:
	__forceinline UnsignedInt getFlags() const { return m_flags; }
};

class BFMESelectionRedirect
{
private:
	const BFMESelectionRedirectTemplate *m_template;
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
	virtual Drawable *selectionDrawable() = 0;

	__forceinline const BFMESelectionRedirectTemplate *getTemplate() const
	{
		const Overridable *value = reinterpret_cast<const Overridable *>(m_template);
		if (value == 0)
			return 0;
		if (value->getNextOverride() != 0)
			value = value->getFinalOverride();
		return reinterpret_cast<const BFMESelectionRedirectTemplate *>(value);
	}
};

class BFMESelectionObject
{
private:
	unsigned char m_opaque[0x214];
	BFMESelectionRedirect *m_selectionRedirect;
public:
	__forceinline BFMESelectionRedirect *getSelectionRedirect() const { return m_selectionRedirect; }
};

class Drawable
{
public:
	unsigned char m_beforeObject[0xFC];
	BFMESelectionObject *m_object;
	unsigned char m_beforeSelected[0x3AC - 0x100];
	Bool m_selected;
};

Bool areAllSelected(const DrawableList& listToCheck)
{
	DrawableListCIt it;
	Drawable *draw;
	for (it = listToCheck.begin(); it != listToCheck.end(); ++it) {
		draw = *it;
		if (draw == 0)
			continue;
		if (draw->m_object != 0) {
			BFMESelectionRedirect *redirect = draw->m_object->getSelectionRedirect();
			if (redirect != 0) {
				const BFMESelectionRedirectTemplate *redirectTemplate = redirect->getTemplate();
				if ((redirectTemplate->getFlags() & 0x1000) != 0) {
					Drawable *replacement = redirect->selectionDrawable();
					if (replacement != 0)
						draw = replacement;
				}
			}
		}
		if (!draw->m_selected)
			return FALSE;
	}
	return TRUE;
}
