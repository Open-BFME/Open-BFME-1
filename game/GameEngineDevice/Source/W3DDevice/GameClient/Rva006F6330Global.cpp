// cl: /DNDEBUG /MD
//
// Retail's pointer at VA 0x012F8228: W3DDisplay::init (0x006ED5B0) stores
// `new Rva006F6330` into it and W3DDisplay's destructor deletes it as a
// W3DFileSystem; Open_W3D_File (0x006F6BA0) and 0x006F6AB0 test it for null.
// Defined once here under the address-derived name the init/destructor TUs use.

class Rva006F6330;

Rva006F6330 *TheRva006F6330;
