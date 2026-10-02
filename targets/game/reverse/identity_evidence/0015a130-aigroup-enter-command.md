# RVA 0x0015A130: AIGroup receiver, player MSG_ENTER command route

This is an owner/operation proof for the already matched address-derived
`Rva0015A190Owner::rva0015A130`. It does not prove an original method spelling.
The retail bytes were read with pefile/capstone; Ghidra read_memory at VA
0x0055A130 returned the identical 66-byte sequence. Image base: 0x00400000.
The body ends in `ret 8` at RVA 0x0015A16F and INT3 starts at 0x0015A172.

## Independent AIGroup owner

In the retail GameLogic message dispatcher at RVA 0x00397540, call
0x003975D0 uses ILT 0x0003B570 -> RVA 0x0014C630, the matched clean C++
`AI::createGroup()` returning `AIGroup*`. Its result is copied into EBP at
0x003975D9 and saved at [ESP+0x18] at 0x003975DE, after the intervening push.
When the stack returns to its original depth, this is the local at ESP+0x14. The MSG_ENTER branch loads this same local into ESI at
0x00398140. It passes that value in ECX at 0x00398158 to the call at
0x0039815A, ILT 0x0000DD0A -> RVA 0x0015A130.

Thus the candidate's receiver is an AIGroup returned by an independently
matched factory method, rather than an owner inferred from its opaque name.
The second stack argument is zero; the first is the object found from message
argument 1 by the dispatcher.

## Native MSG_ENTER branch

The dispatch range at 0x00398087 subtracts 0x417 from EDI (message type),
checks the result against 0x18, then jumps through VA 0x0079A324. Table
entry 20, VA 0x0079A374, contains VA 0x0079811F. Thus message **0x42B =
1067** selects the branch that calls the candidate.

The matched clean C++ `GameMessage::getCommandTypeAsAsciiString`, RVA
0x0008B600, maps 1067 to the shipped literal `MSG_ENTER` in
`game/GameEngine/Source/Common/System/message_stream_commandName.cpp:213`.
The dispatcher itself is a certified dump, so its C++ spelling is not a
clean-caller name witness; the index and branch above come from native bytes.

The helper queries the object's +0x1FC contain interface through slot +0x144,
then submits a 16-byte packet {virtual result, zero flag, object, object} to
ILT 0x00048C43 -> RVA 0x00159AD0 with the same AIGroup receiver and zero as
the other argument. The packet therefore implements a player entry command
path; the virtual result's exact BFME member name remains unproved.

## Why this is not a rename to groupEnter

`AIGroup::groupEnter(Object*, CommandSourceType)` already has an independently
proved 229-byte body at RVA 0x00156440. Its clean C++ callers include the
matched `ScriptActions::doTeamEnterNamed` at 0x002F2AE0 and
`ScriptActions::doTeamGarrisonSpecificBuilding` at 0x002FD9D0, which call
its ILT 0x0003756A. That function snapshots members and calls aiEnter on
each one. The 66-byte candidate instead asks the contain interface for a
command and submits a packet to a common helper.

MSG_ENTER identifies the operation, not the method spelling. No second
`groupEnter` claim is introduced, and no canonical AIGroup header or source
is changed. A later BFME declaration or independently named caller can name
this distinct command wrapper.
