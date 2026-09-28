// cl: /DNDEBUG /MD /O2
// Each wrapper is an independent padding-delimited 10-byte function.
// Retail REL32 destinations: 00026F35 -> 000B31F0 (AudioEventRTS dtor);
// 0004A241 -> 00201F10 (zero-argument member); 0001F5B9 -> 00755920
// (Gen007558B0 dtor); 0003B2B9 -> 00077FB0 -> 000235E7 -> 000775F0 (tree dtor).
// Existing callee names/pins are reused; the wrappers retain opaque identities.
class AudioEventRTS { public: ~AudioEventRTS(); };
class Gen_00201f10 { public: void m(); };
class Gen007558B0 { public: ~Gen007558B0(); };
class Gen0003B2B9 { public: void handle(); };
extern AudioEventRTS Rva012F0BE8;
extern AudioEventRTS Rva012F0C70;
extern AudioEventRTS Rva012F0D00;
extern AudioEventRTS Rva012F0D90;
extern AudioEventRTS Rva012F0E18;
extern AudioEventRTS Rva012F0EA8;
extern AudioEventRTS Rva012F0F50;
void Rva00C6FE80() { Rva012F0BE8.~AudioEventRTS(); }
void Rva00C6FE90() { Rva012F0C70.~AudioEventRTS(); }
void Rva00C6FEA0() { Rva012F0D00.~AudioEventRTS(); }
void Rva00C6FEB0() { Rva012F0D90.~AudioEventRTS(); }
void Rva00C6FEC0() { Rva012F0E18.~AudioEventRTS(); }
void Rva00C6FED0() { Rva012F0EA8.~AudioEventRTS(); }
void Rva00C6FEE0() { Rva012F0F50.~AudioEventRTS(); }
extern Gen_00201f10 Rva012F9D9C;
extern Gen007558B0 Rva01304B74;
extern Gen0003B2B9 Rva01305A58;
extern Gen0003B2B9 Rva01305A68;
void Rva00C70A40() { Rva012F9D9C.m(); }
void Rva00C70A80() { Rva01304B74.~Gen007558B0(); }
void Rva00C70A90() { Rva01305A58.handle(); }
void Rva00C70AA0() { Rva01305A68.handle(); }
