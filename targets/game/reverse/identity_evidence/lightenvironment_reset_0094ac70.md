# LightEnvironmentClass::Reset at 0x0094AC70

The previously opaque `Gen_0094AC70::bfmeSetPair` body has the identity
`LightEnvironmentClass::Reset(const Vector3 &, const Vector3 &)`.

Matched `SimpleSceneClass::Customized_Render` at 0x00943AD0 (388 bytes),
implemented in WW3D2/scene.cpp, constructs a LightEnvironmentClass via
0x0094AAF0, invokes `lenv.Reset(Vector3(0, 0, 0), self->AmbientLight)` at
0x0094AC70, then calls its Add_Light and Pre_Render_Update methods.
The surviving Zero Hour lightenvironment.h declares the same signature.
The canonical BFME constructor independently proves the leading four bytes.

The full 64-byte leaf body at 0x0094AC70 writes zero to +4 (LightCount),
copies the first Vector3 to +8, the second to +0x164 (OutputAmbient),
clears the byte at +0, and ends with ret 8 at 0x0094ACAD. The next function
starts at 0x0094ACB0. The old opaque row has exactly this extent. No new
callee pins or invented member names are needed.
