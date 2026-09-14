// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AudioLoopUpgrade.
// Vtable 0x00CCBE24 slots name this class (?getModuleNameKey@AudioLoopUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000173F5 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000120F8 reaches cleanup body 0x002D3080.

class AudioLoopUpgrade
{
protected:
	virtual ~AudioLoopUpgrade();
private:
	friend void forceAudioLoopUpgradeDeletingDestructor();
};

void forceAudioLoopUpgradeDeletingDestructor()
{
	AudioLoopUpgrade value;
}
