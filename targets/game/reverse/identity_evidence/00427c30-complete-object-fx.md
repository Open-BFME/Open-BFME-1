# Complete FXNugget::doFXObj and its four-argument callback

The old24B claim cuts MOV EAX,[ESP+10] at427C46. Retail follows both null
and non-null secondary-object paths through virtual CALL [EDI+04] and
RET8. Final RET8 at427C6D, thenINT3 at427C70, proves64 contiguous bytes.
Ghidra's created function independently covers64B. The GeneralsMD FXList.cpp
twin supplies the same doFXObj identity, Object/Coord3D/Matrix3D types,
position/transform handling, zero speed, and doFXPos callback name.

The retail wrapper pushes four arguments on either path. The shared ZH
FXNugget declaration adds a fifth overrideRadius parameter with a default,
which compiles an extra argument beyond the old prefix. Do not change that
shared header: use an address-qualified local view of only slot0 and the
four-argument const doFXPos callback at slot04.

Independent ABI witness: the SoundFXNugget table at RVA CF33D8 has slot1
at VA10F33DC containing ILT VA4130D9, which enters4289B0. The separately
matched four-argument SoundFXNugget::doFXPos body4289B0/119B ends RET16 at
428A24 thenINT3 at428A27. Its source is SoundFXNugget_doFXObj_Thunk.cpp.
This proves the callback's argument width independently of this wrapper's
new code or its byte comparison. The source retains all existing canonical
Object/Coord3D/Matrix3D declarations and the original object field accesses.

No direct calls occur (tools/callees.py); no new pins, shared-header edits,
or invented semantic type names are required. The complete source gate
must verify the corrected64B row and every existing sibling claim.
