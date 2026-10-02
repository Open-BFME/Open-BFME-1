# RVA 0x004991D0: WindowVideoManager::playMovie

Identity evidence, not a conversion or byte-match claim. All addresses below
were cross-checked against the retail unpacked `lotrbfme.exe`, image base
0x00400000, using pefile and capstone. Ghidra creation at VA 0x008991D0
independently reports a 253-byte body. It ends in `ret 0x0C` at RVA
0x004992CA, with INT3 padding starting at 0x004992CD.

## BFME owner and argument evidence

The incoming ECX is saved in ESI at 0x004991EA. With that same receiver,
0x004991F7 calls ILT 0x0000A91B -> RVA 0x00498D10, the matched
`WindowVideoManager::stopAndRemoveMovie(GameWindow*)`. The first stack
argument supplies the window. This independently identifies the owner;
no owner is inferred from the anonymous body's ledger name.

At 0x0049929A the body calls ILT 0x00042131 -> RVA 0x00498C40 with
ECX = ESI+8 and the address of that same window argument, then writes its
newly allocated WindowVideo pointer into the returned mapped-value address.
The matched implementation at this address has a synthetic int/enum
hash-map name, so that name is not proof of the actual map's types. The
receiver offset and use agree with the manager's map in matched
`stopAndRemoveMovie` and `reset`.

It clears bytes at ESI+0x1D and ESI+0x1C at 0x004992A1/0x004992A4;
matched `WindowVideoManager::init` and `reset` clear the same two bytes.

The middle argument is copied twice through the matched StringBase<char>
copy constructor at RVA 0x00887B60 and released through 0x00887940.
The third stack argument is passed unchanged to the matched
`WindowVideo::init(GameWindow*, AsciiString, WindowVideoPlayType,
VideoBuffer*)`, ILT 0x00027A2F -> RVA 0x00498240. This proves the
by-value string and play-type argument roles.

## BFME operation and upstream method name

The body opens the string-named movie through the global at VA 0x0130B190
(TheVideoPlayer), slot +0x30, with an additional zero argument. On success
it obtains a buffer through TheDisplay at VA 0x012F1270, slot +0x84, also
passing zero. It supplies that buffer to slot +0x38 of the opened object,
and calls slot +0x1C if the operation fails. On success it allocates 0x14
bytes and invokes the matched WindowVideo constructor via ILT 0x0002A685
-> RVA 0x00498130, initializes that object, and inserts it into the map.

This combination identifies `playMovie` among the manager's declarations
in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h`.
The implementation in the sibling `Source/GameClient/GUI/WindowVideoManager.cpp`
performs the same stop/open/create/initialize/insert/unpause sequence.
Upstream supplies the method spelling; BFME's calls to independently matched
manager and WindowVideo methods, exact receiver offsets and string argument
handling establish the identity. The proposed symbol is
`?playMovie@WindowVideoManager@@QAEXPAVGameWindow@@VAsciiString@@W4WindowVideoPlayType@@@Z`.

## Remaining conversion blocker

The checked-in lowercase `window_video_manager.cpp` retains the upstream
separate VideoStreamInterface/VideoBuffer model and a five-argument init.
BFME's matched WindowVideo::init takes four arguments and uses slot +0x3C
of its buffer argument before setting the window's buffer. The current
`video_player.h` methods are nonvirtual, and its upstream allocation path
cannot reproduce the retail virtual calls described above. Correcting the
shared interface model affects other bodies and requires a full gate.
No interface slot name is proved merely by its offset in this note.

A scan of executable sections found only ILT RVA 0x00005F1F jumping to
this body, no direct transfers to that stub, and no absolute pointer to
either entry. There is therefore no matched caller for the method. No
source or ledger identity has been changed on this evidence-only pass.
