// Address-derived LuaEventNugget field parser at 0x002DCF10.
//
// The Weapon FieldParse table names its caller at 0x001E6240 as the
// LuaEventNugget parser. That caller passes its freshly allocated
// Made001E6240 object here, and this body builds the canonical 0x84-byte
// MultiIniFieldParse before calling INI::initFromINIMulti at 0x00851910.
// The helper's semantic name remains unknown, so keep its established
// address-derived identity rather than inventing one.

struct FieldParse;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		Count = 0;
		for (int i = 0; i < 16; ++i)
		{
			Offsets[i] = 0;
			Fields[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *Fields[16];
	unsigned int Offsets[16];
	unsigned int Count;
};

class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

class Made001E6240;

extern "C" char q4Fields001E6240[];

void q4Notify001E6240(void *reader, Made001E6240 *nugget, int, int)
{
	MultiIniFieldParse fields;
	fields.add((const FieldParse *)q4Fields001E6240);
	((INI *)reader)->initFromINIMulti(nugget, fields);
}
