struct Rva0088D8E0Record
{
	void *field0;
	unsigned int field4;
	unsigned int field8;
	unsigned char flagC;
	unsigned char flagD;
};

void __cdecl initialize0088D8E0(Rva0088D8E0Record *record, void *field0,
	unsigned int field4, unsigned int field8)
{
	record->field0 = field0;
	record->field4 = field4;
	record->field8 = field8;
	record->flagC = 1;
	record->flagD = 1;
}
