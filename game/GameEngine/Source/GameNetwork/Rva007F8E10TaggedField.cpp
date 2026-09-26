// cl: /O2
// Returns the field associated with a FESL message category. The six literal
// tags and the field offsets come directly from the retail comparisons/loads.
struct Rva007F8E10Fields
{
	char pad[0x234];
	unsigned int at234;
	unsigned int at238;
	unsigned int at23c;
	unsigned int at240;
	unsigned int at244;
	unsigned int at248;
};

struct Rva007F8E10Message
{
	char pad[0x1c];
	int category;
};

unsigned int __stdcall Rva007F8E10TaggedField(const Rva007F8E10Fields *fields,
	const Rva007F8E10Message *message)
{
	switch (message->category)
	{
	case 0x6664626b: return fields->at248; // 'fdbk'
	case 0x636c7562: return fields->at240; // 'club'
	case 0x61636374: return fields->at234; // 'acct'
	case 0x66737973: return fields->at244; // 'fsys'
	case 0x72656370: return fields->at23c; // 'recp'
	case 0x72616e6b: return fields->at238; // 'rank'
	default: return 0;
	}
}
