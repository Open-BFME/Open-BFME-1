// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LargeGroupAudioUnusedKnownKeys scalar-deleting destructor at
// retail RVA 0x003CDEA0 (30 bytes). The exact default/copy constructors at
// 0x003CD450/0x003CD590 install vtable 0x010EE0FC and the matched complete
// destructor at 0x003CDED0 tears down the key-map member at +0x0C. The
// authored constructor/destructor/collector TUs establish this named class
// and its layout.

class LargeGroupAudioUnusedKnownKeys
{
public:
	virtual ~LargeGroupAudioUnusedKnownKeys();
};

void forceLargeGroupAudioUnusedKnownKeysDeletingDestructor()
{
	LargeGroupAudioUnusedKnownKeys value;
}
