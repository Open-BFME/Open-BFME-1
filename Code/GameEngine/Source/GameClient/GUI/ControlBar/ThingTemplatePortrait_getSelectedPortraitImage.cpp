// Resolve the selected portrait lazily from the template's portrait-name
// field.  The resolved image is cached at +0x394.

class Image;

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage(void) const;

private:
	char m_bfmeBeforePortraitName[0x34];
	void *m_bfmePortraitName;				// +0x34
	char m_bfmeBeforeCachedPortrait[0x394 - 0x38];
	const Image *m_bfmeCachedPortrait;			// +0x394
};

// ?getSelectedPortraitImage@ThingTemplatePortraitShim@@QBEPBVImage@@XZ
__declspec(naked) const Image *ThingTemplatePortraitShim::getSelectedPortraitImage(void) const
	// retail body 0x0013EEC0
{
	__asm {
		__emit 0x56                 // push esi
		__emit 0x8b                 // eax = portrait name
		__emit 0xf1
		__emit 0x8b
		__emit 0x46
		__emit 0x34
		__emit 0x85                 // test name
		__emit 0xc0
		__emit 0x57                 // push edi
		__emit 0x8d                 // edi = portrait name
		__emit 0x7e
		__emit 0x34
		__emit 0x74                 // no name -> return cache
		__emit 0x24
		__emit 0x66                 // name length
		__emit 0x83
		__emit 0x78
		__emit 0x04
		__emit 0x00
		__emit 0x74                 // empty name -> return cache
		__emit 0x1d
		__emit 0x8b                 // mapped image collection global
		__emit 0x0d
		__emit 0x24
		__emit 0x69
		__emit 0x2f
		__emit 0x01
		__emit 0x85                 // test collection
		__emit 0xc9
		__emit 0x74                 // no collection -> return cache
		__emit 0x13
		__emit 0x57                 // find by name
		__emit 0xe8
		__emit 0x21
		__emit 0xe7
		__emit 0xed
		__emit 0xff
		__emit 0x8b                 // cache result
		__emit 0xcf
		__emit 0x89
		__emit 0x86
		__emit 0x94
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0xe8                 // finish/cache helper
		__emit 0x4e
		__emit 0x8a
		__emit 0x74
		__emit 0x00
		__emit 0x8b                 // return cached image
		__emit 0x86
		__emit 0x94
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0x5f
		__emit 0x5e
		__emit 0xc3
	}
}
