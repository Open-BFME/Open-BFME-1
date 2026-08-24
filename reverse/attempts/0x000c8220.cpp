// ?readFromDict@Handicap@@QAEXPBVDict@@@Z
// partial score=0.99 date=2026-08-24
void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[HANDICAP_TYPE_COUNT] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[THING_TYPE_COUNT] =
	{
		"GENERIC",
		"BUILDINGS",
	};

	StringBase<char> c;
	c.m_data = 0;

	for (int i = 0; i < HANDICAP_TYPE_COUNT; ++i)
	{
		for (int j = 0; j < THING_TYPE_COUNT; ++j)
		{
			c.releaseBuffer();
			c.set("HANDICAP_", 9);
			c.concat(htNames[i], (int)strlen(htNames[i]));
			c.concat("_", 1);
			c.concat(ttNames[j], (int)strlen(ttNames[j]));
			NameKeyType k = TheNameKeyGenerator->nameToKey(c.str());
			bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
