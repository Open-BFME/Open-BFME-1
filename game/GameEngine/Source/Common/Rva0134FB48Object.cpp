// cl: /O2 /MD
// The 60-byte object at VA 0x0134FB48 that Rva00C6E34DInitialize constructs in place
// through the retail constructor at 0x009F6ADB. This TU defines the storage as a plain
// aggregate, so the compiler emits no dynamic initializer for it; the constructor is
// declared in Rva00C6E31EInitializers.cpp.

class Rva009F6ADBObject
{
public:
	unsigned char storage[60];
};

Rva009F6ADBObject g_rva0134FB48;
