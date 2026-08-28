// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?allowsObservers@CustomMatchPreferences@@QAE_NXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Grok promote from masm_dumps — retail 0x000AC510 size 95
// was: Code/masm_dumps/CustomMatchPreferences_allowsObservers.asm

struct CustomAsciiStringShim {
	void *data;
	void init(const char *);
	void destroy(void);
};

struct CustomMapNodeShim {
	unsigned char padding[0x14];
	void *value;
};

struct CustomPreferenceMapShim {
	CustomMapNodeShim *sentinel;
	CustomMapNodeShim *find(CustomAsciiStringShim *);
};

class CustomMatchPreferences { public: bool allowsObservers(void); };

typedef int (__cdecl *CustomStringCompare)(const char *, const char *);

// ?allowsObservers@CustomMatchPreferences@@QAE_NXZ
bool CustomMatchPreferences::allowsObservers(void)
{
	unsigned char keyStorage[sizeof(CustomAsciiStringShim)];
	CustomAsciiStringShim *key = (CustomAsciiStringShim *)keyStorage;
	key->init((const char *)0x010811E8);
	CustomPreferenceMapShim *map = (CustomPreferenceMapShim *)this;
	map = (CustomPreferenceMapShim *)((unsigned char *)map + 4);
	CustomMapNodeShim *node = map->find(key);
	key->destroy();
	if (node == map->sentinel)
		return true;
	node = *(CustomMapNodeShim **)((unsigned char *)node + 0x14);
	const char *text = node ? (const char *)((unsigned char *)node + 8)
		: (const char *)0x0107388B;
	unsigned char result = (unsigned char)(((CustomStringCompare)*(void **)0x0135933C)(
		text, (const char *)0x01080FC0) == 0);
	return result;
}

