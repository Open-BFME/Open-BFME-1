# TextureFilterClass::Apply at 0x00920BC0

The 331-byte BFME 1 body reads the three verified texture filter tables
through the receiver's first three dwords. It applies texture stage
states 6, 5 and 7 (minification, magnification and mip), then states 1
and 2 from the two address modes. Its one stack argument supplies the
stage and RET 4 consumes it. The eight-byte thunk at 0x0090C610 adds 28
to ECX and jumps directly here. The matched shader-state and terrain
callers supply the stage through that thunk.

BFME 2 dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce identifies the same
operation as TextureFilterClass::Apply(unsigned int) at 0x0013EA30 in
Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp. Zero Hour has the
same method and TextureClass::Apply forwards its stage to Filter.Apply.
BFME 1 uses its own declared class, DX8 state calls and table strides.

0x00920BC0 ?handle@Gen00920BC0@@QAEXH@Z -> ?Apply@TextureFilterClass@@QAEXI@Z
0x0090C610 ?invoke@Rva0090C610@@QAEXXZ -> ?invoke@Rva0090C610@@QAEXI@Z
