// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateSoloNexus@InGameUI@@IAEXPAVDrawable@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

enum KindOfType
{
	KINDOF_MOB_NEXUS = 46,
	KINDOF_IGNORED_IN_GUI = 47
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		return m_nextOverride ? m_nextOverride->getFinalOverride() : this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned int mobNexusMask() const
	{
		return m_kindOf[1] & 0x4000;
	}

	unsigned int ignoredInGUIMask() const
	{
		return m_kindOf[1] & 0x8000;
	}

private:
	char m_unused[0xc0];
	unsigned int m_kindOf[2];
};

template <class T> class Override
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}

private:
	const T *m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf(KindOfType type) const;

protected:
	void *m_vtable;
	Override<ThingTemplate> m_template;

	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	const ThingTemplate *getTemplateForKindOf() const
	{
		return getTemplate();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	DrawableID getID() const;

	Object *getObject() const
	{
		return m_object;
	}

private:
	char m_unused[0xfc];
	Object *m_object;
};

struct DrawableListNode
{
	DrawableListNode *next;
	DrawableListNode *previous;
	Drawable *drawable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
protected:
	void evaluateSoloNexus(Drawable *newlyAddedDrawable);

private:
	char m_unusedBeforeSelection[0x18];
	DrawableListNode *m_selectedDrawables;
	char m_unusedBeforeSoloNexus[0x1388];
	DrawableID m_soloNexusSelectedDrawableID;
};

void InGameUI::evaluateSoloNexus(Drawable *newlyAddedDrawable)
{
	m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;

	if (newlyAddedDrawable)
	{
		const Object *newObject = newlyAddedDrawable->getObject();
		if (newObject && !newObject->isKindOf(KINDOF_MOB_NEXUS)
				&& !newObject->isKindOf(KINDOF_IGNORED_IN_GUI))
			return;
	}

	unsigned short nexusesFound = 0;
	for (DrawableListNode *it = m_selectedDrawables->next;
			it != m_selectedDrawables; it = it->next)
	{
		Drawable *drawable = it->drawable;
		const Object *object = drawable->getObject();
		if (!object)
			continue;

		if (object->getTemplateForKindOf()->mobNexusMask())
		{
			if (++nexusesFound == 1)
				m_soloNexusSelectedDrawableID = drawable->getID();
			else
			{
				m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
				return;
			}
		}
		else if (!object->getTemplateForKindOf()->ignoredInGUIMask())
		{
			m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
			return;
		}
	}
}
