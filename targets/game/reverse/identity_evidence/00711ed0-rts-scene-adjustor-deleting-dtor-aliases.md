# RTS2DScene / RTS3DScene WBAI adjustor thunks (s555)

Retail 0x00711ED0 and 0x00713500 are 11-byte this-adjusting entries
(`81 E9 08 01 00 00` sub ecx,0x108; `E9 rel32` jmp). Each jmp lands on an ILT
entry (0x000299B0 / 0x000080FD) that routes to the scalar deleting destructor
??_GRTS2DScene@@UAEPAXI@Z (0x007120D0, W3DScene.cpp) /
??_GRTS3DScene@@UAEPAXI@Z (0x007158C0, RTS3DSceneDestructorThunk.cpp). The only
references to the thunks are the ILT entries 0x00013F75 / 0x000206DF; nothing
calls or jumps to the +6 bytes, which earlier carried 5-byte gen-thunk scaffold
rows (retired in deleted_rows.csv).

`ilt_oracle.py check` CONFIRMS (exact) ??_ERTS2DScene@@WBAI@AEPAXI@Z at
0x00711ED0 and ??_ERTS3DScene@@WBAI@AEPAXI@Z at 0x00713500 (0x108 = WBAI@,
public virtual this-adjustor of the vector deleting destructor slot).
RTS2DSceneDestructorThunk.cpp and RTS3DSceneDestructorThunk.cpp already emit
these COMDATs (11 bytes); their REL32 names ??_E<Class>@@UAEPAXI@Z, the weak
external that defaults to ??_G in the same object. The ??_E pins (at the ILT entries the thunks jump to, route= the ??_G
bodies) are that weak alias, not a second identity: the bodies stay ??_G (same recipe as
00956cf0-w7-adjustor-deleting-dtor-aliases.md).

pin-identity-override: ??_ERTS3DScene@@UAEPAXI@Z 0x000080FD caller=0x00713500 the WBAI adjustor thunk 0x00713500 (RTS3DSceneDestructorThunk.cpp) jumps via ILT 0x000080FD to 0x007158C0 through the weak alias ??_E that defaults to ??_GRTS3DScene in the same object
pin-identity-override: ??_ERTS2DScene@@UAEPAXI@Z 0x000299B0 caller=0x00711ED0 the WBAI adjustor thunk 0x00711ED0 (RTS2DSceneDestructorThunk.cpp) jumps via ILT 0x000299B0 to 0x007120D0 through the weak alias ??_E that defaults to ??_GRTS2DScene in the same object
