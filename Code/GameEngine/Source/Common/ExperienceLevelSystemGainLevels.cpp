// cl: /DNDEBUG /MD /EHs-c-
//
// Open-BFME5: ExperienceLevelSystem::gainLevels at retail 0x00381220 (41B).
// Same TU as gainLevel body 0x00381050 (ILT 0x00027237). Signature is
// (Object*, Int count, Bool showFx); loops count times calling gainLevel.

class Object;

class ExperienceLevelSystem
{
public:
	void gainLevel(Object *obj, bool showFx);
	void gainLevels(Object *obj, int count, bool showFx);
};

// ?gainLevels@ExperienceLevelSystem@@QAEXPAVObject@@H_N@Z
void ExperienceLevelSystem::gainLevels(Object *obj, int count, bool showFx)
{
	for (; count > 0; --count)
		gainLevel(obj, showFx);
}
