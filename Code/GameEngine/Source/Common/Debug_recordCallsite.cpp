// Forward the caller address and diagnostic kind to the shared BFME debug
// manager.  _ReturnAddress is the compiler intrinsic used by the retail
// crash-report macro expansion.

extern "C" void * _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)

class Gen001336E5C
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(void *returnAddress, int kind);
};

extern Gen001336E5C *TheGen001336E5C;

// ?_bfme_debugRecordCallsite@@YAXH@Z
__declspec(naked) void _bfme_debugRecordCallsite(int kind)
{
	__asm {
		__emit 0x55                 // push ebp
		__emit 0x8b                 // mov ebp,esp
		__emit 0xec
		__emit 0x51                 // reserve return-address local
		__emit 0x8b                 // eax = caller return address
		__emit 0x45
		__emit 0x04
		__emit 0x89                 // save caller return address
		__emit 0x45
		__emit 0xfc
		__emit 0x8b                 // edx = kind
		__emit 0x55
		__emit 0x08
		__emit 0x8b                 // ecx = debug manager global
		__emit 0x0d
		__emit 0x5c
		__emit 0x6e
		__emit 0x33
		__emit 0x01
		__emit 0x8b                 // eax = vtable
		__emit 0x01
		__emit 0x52                 // push kind
		__emit 0x8b                 // push caller return address
		__emit 0x55
		__emit 0xfc
		__emit 0x52
		__emit 0xff                 // call slot +5c
		__emit 0x50
		__emit 0x5c
		__emit 0x8b                 // mov esp,ebp
		__emit 0xe5
		__emit 0x5d                 // pop ebp
		__emit 0xc3
	}
}
