// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getMusicVolume@OptionPreferences@@QAEMXZ: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp
// Lift OptionPreferences::getMusicVolume to clean C++.
//
// This body was filed as getResolution taking two Int pointers. It takes none:
// the body ends with a bare `ret`, and a thiscall member with two pointer
// arguments must end `ret 8`. The key it looks up is "MusicVolume" and every
// exit leaves its answer in st(0), so it returns Real.
//
// The getMusicVolume name was tombstoned earlier against 0x00091B40, where the
// body turned out to be the LanguageFilter getter. This is a different address,
// so that tombstone does not apply and stays as it is -- it refuted the name at
// that address, not the name itself.
//
// Same skeleton as getLanguageFilter and getMaxDisconnects: a plain shim object
// for the key driven by explicit init/destroy, because retail reserves exactly
// four bytes for it with `push ecx` and a destructor would want an unwind frame
// this function has not got; and the map pointer formed after the key is built,
// because retail holds plain `this` in esi across the constructor and only then
// does `add esi,4`.
//
// On a miss the answer comes from the audio system rather than a stored value:
// TheAudio's virtual at +0x120 returns the settings block and the volume is the
// float at +0x88, scaled by 100. On a hit the stored text goes through atof and
// is clamped at zero from below -- the `fcom` against 0.0 with `test ah,5` and
// `jp` is MSVC's less-than test, and the value never leaves st(0).

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl atof(const char *str);

// Reusing the shim names an earlier CustomMatchPreferences conversion pinned
// rather than restating the _Rb_tree and StringBase template names.
struct CustomAsciiStringShim
{
	void *m_data;
	void init(const char *s);						///< body at 0x00888BC0
	void destroy(void);								///< body at 0x00887940
};

struct CustomStringDataShim
{
	unsigned char m_header[8];						///< characters follow at +8
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value;					///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;					///< doubles as the end sentinel
	CustomMapNodeShim *find(CustomAsciiStringShim *key);	///< ILT thunk at 0x0000AEAC
};

// Only the one field this function reads is reconstructed.
struct AudioSettingsShim
{
	unsigned char m_unreconstructed_00[0x88];
	Real m_musicVolume;								///< retail settings+0x88
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual const AudioSettingsShim *getAudioSettings(void);	///< vtable +0x120
};

extern AudioManager *TheAudio;						///< retail [0x012ED668]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	Real getMusicVolume(void);
};

// ?getMusicVolume@OptionPreferences@@QAEMXZ
Real OptionPreferences::getMusicVolume(void)
{
	CustomAsciiStringShim key;
	key.init("MusicVolume");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((unsigned char *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return TheAudio->getAudioSettings()->m_musicVolume * 100.0f;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((unsigned char *)data + 8) : "";
	Real volume = (Real)atof(text);
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}
