// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CameraShakeSystemClass scalar-deleting destructor at retail
// 0x006E7C00 (30 bytes).  The matched constructor at 0x006D12A0 and complete
// destructor at 0x006D1900, together with the camera-shake implementation and
// CameraShakerList member, establish the class identity.

class CameraShakeSystemClass
{
public:
	~CameraShakeSystemClass();
};

void Force_CameraShakeSystemClass_Deleting_Destructor(
	CameraShakeSystemClass *value)
{
	delete value;
}
