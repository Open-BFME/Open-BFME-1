// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getSoundVolume@OptionPreferences@@QAEMXZ: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp
// Lift the OptionPreferences::getSoundVolume naked dump to clean C++.
//
// The preferences-getter opening is the family's, but both ends are new. The
// missing-key default is not a stored field: it calls TheAudio's virtual at
// vtable +0x120 and scales the sound effects volume it returns by 100, so the
// preference is a percentage while the audio settings hold a fraction.
//
// The present-key path runs the mapped string through atof and floors the
// result at zero. The local is a float even though atof returns a double:
// retail loads the floor constant with `fcom dword` and `fld dword`, and a
// double local makes both of those qword loads instead. MSVC never spills the
// value to narrow it -- it stays in st(0) across the whole tail -- so the only
// evidence of the local's type is the width of those two constant loads.
//
// The `fcom / fnstsw ax / test ah,5 / jp` sequence is MSVC's unordered-safe
// less-than: C0 and C2 are both clear when st(0) is greater or equal, so even
// parity means keep the value and odd means replace it.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, str() inlines to
// "m_data ? m_data+8 : empty", and the default volume sits at settings+0x80.

extern "C" __declspec(dllimport) double __cdecl atof(const char *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();

	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const;
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;								///< retail this+0x00
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioSettings.h
class AudioSettings
{
public:
	unsigned char m_unreconstructed_00[0x80];
	float m_defaultSoundVolume;				///< retail this+0x80
};

// Only the virtual at +0x120 is reconstructed; the slots ahead of it are
// declared to place it and are never defined or called.
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

	virtual const AudioSettings *getAudioSettings(void) const;	///< vtable +0x120
};

extern AudioManager *TheAudio;							///< retail [0x012ED668]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	float getSoundVolume(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getSoundVolume@OptionPreferences@@QAEMXZ
float OptionPreferences::getSoundVolume(void)
{
	PreferenceNode *it;
	{
		AsciiString key("SFXVolume");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheAudio->getAudioSettings()->m_defaultSoundVolume * 100.0f;

	float volume = atof(it->m_value.str());
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}

	return volume;
}
