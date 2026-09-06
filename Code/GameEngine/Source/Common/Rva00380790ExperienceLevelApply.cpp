// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc-
//
// Retail 0x00380790.  This is the address-derived ExperienceLevelSystem
// wrapper beside the exact 0x0037FE30 pending-record body.  The first call is
// the independently named findLevel(const AsciiString &) member; the rest of
// the body is the same level-application tail as retail 0x00380510.

typedef bool Bool;
typedef int Int;
typedef float Real;

class AsciiString
{
private:
	char *m_text;
};

class BfmeExperienceLevelDefinition
{
public:
	char m_pad00[0x10];
	Int m_experience;
	char m_pad14[0x64];
	void *m_effectData;
	char m_pad7C[0x50];
	Int m_level;
};

class Arg1
{
public:
	char m_pad00[0x10];
	Int m_experience;
	char m_pad14[0x64];
	void *m_effectData;
	char m_pad7C[0x50];
	Int m_level;
};

class BfmeThingCF
{
public:
	void bfmeSendCF(void *effectData);
};

class ExperienceTracker
{
public:
	void bfmeSetCurrentExperience(Real experience);
	void bfmeSetScalarIndex(Int index);
};

class ObjectView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual BfmeThingCF *getExperienceEffect() = 0;

	char m_pad04[0x20C];
	ExperienceTracker *m_tracker;
};

class Rva0037FE30
{
public:
	void record(Arg1 *arg1, ObjectView *object, Bool showEffect);
};

class ExperienceLevelSystem
{
public:
	BfmeExperienceLevelDefinition *findLevel(const AsciiString &name);
	void rva00380790(const AsciiString &name, ObjectView *object,
		Bool showEffect);
};


void ExperienceLevelSystem::rva00380790(const AsciiString &name,
	ObjectView *object, Bool showEffect)
{
	BfmeExperienceLevelDefinition *level = findLevel(name);
	if (!level)
		return;
	if (!object)
		return;

	((Rva0037FE30 *)this)->record((Arg1 *)level, object, showEffect);
	BfmeThingCF *effect = object->getExperienceEffect();
	if (effect)
		effect->bfmeSendCF((void *)&level->m_effectData);
	object->m_tracker->bfmeSetCurrentExperience((Real)level->m_experience);
	object->m_tracker->bfmeSetScalarIndex(level->m_level);
}
