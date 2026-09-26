// cl: /DNDEBUG /MD /EHsc
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int offset = 0);
};

extern const FieldParse g_voiceFieldParse[];

__declspec(noinline) const FieldParse *getVoiceFieldParse()
{
	return g_voiceFieldParse;
}

// Registration and field keys establish the RandomSoundSelectorClientBehavior role; the original class spelling is unknown.
class Rva00607A00ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse g_randomSoundSelectorFieldParse[];

void Rva00607A00ModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_randomSoundSelectorFieldParse);
	parse.add(getVoiceFieldParse(), 8);
}
