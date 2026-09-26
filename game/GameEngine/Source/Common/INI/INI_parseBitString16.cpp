// cl: /O2 /EHsc /DNDEBUG /MD

class INI
{
public:
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString16(INI *ini, void *instance, void *store, const void *userData);
};

__declspec(noinline) void INI::parseBitString32(INI *ini, void *instance, void *store, const void *userData)
{
	*(unsigned int *)store = userData && ini && instance ? 1 : 0;
}

// ?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString16(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	unsigned int tmp;
	INI::parseBitString32(ini, 0, &tmp, userData);
	if (tmp & 0xffff0000)
		throw 1;
	*(unsigned short *)store = (unsigned short)tmp;
}
