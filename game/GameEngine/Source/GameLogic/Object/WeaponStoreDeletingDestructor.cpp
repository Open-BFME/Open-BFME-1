// cl: /DNDEBUG /MD /EHsc
//
// WeaponStore's shipped declaration exposes its destructor publicly. The
// exact constructor at 0x001E5290 installs vtable 0x010A13C8; slot-zero ILT
// 0x000327DB reaches the retail scalar wrapper at 0x001E7F20, which calls
// complete-destructor ILT 0x0000D7AB.

class WeaponStore
{
public:
	virtual ~WeaponStore();
};

void forceWeaponStoreDeletingDestructor()
{
	WeaponStore value;
}
