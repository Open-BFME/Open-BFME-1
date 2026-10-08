# Unsigned-byte storage at VA 0x012F4AB0

The existing address-derived name `g_012F4AB0` owns exactly one unsigned byte at retail VA 0x012F4AB0 (RVA 0x00EF4AB0). This records storage and does not claim an original EA name or a Boolean type.

## Retail facts

The reference image is the repository's retail-1.03-unpacked executable. The image SHA-256 and section bounds are recorded in `build/rlink/identity-bytes-1791443509/retail-probe-3.log`. This address is in the writable .data virtual-only tail and reads as 00 before execution. The PE base-relocation directory is empty. The complete executable file contains exactly one little-endian field naming this address, at file offset 0x00553486 (VA 0x00953486). It belongs to `C6 05 B0 4A 2F 01 01` at VA 0x00953484, a one-byte store of 1 in the callback at RVA 0x005533F0. There are no address-taking fields, indexed references, wider accesses spanning this byte, or other producer or consumer instructions in the executable scan. Raw results are in `guarded-probe.log` and the complete containing-body disassembly is in `retail-probe-3.log` under the same folder.

The neighboring singleton is accessed as a four-byte pointer at VA 0x012F4AAC, ending before this byte. Separately accessed bytes at VA 0x012F4AB2 and 0x012F4AB3 and the recorded four-byte owner at VA 0x012F4AB4 do not extend this datum. Zero padding establishes no additional ownership. The complete data-row range check, DIR32 names and pin check find no overlapping owner or name inside [0x012F4AB0, 0x012F4AB1).

The broader scan also found indexed dword loads at VAs 0x00945E86 and 0x00945E93 from bases 0x012F4A70 and 0x012F4A80. They do not reach the assigned byte: the only four retail callers of the helper, at VAs 0x00947E8F, 0x00947EAE, 0x00947ECD and 0x00947EEC, all push index 3 through the five-byte thunk at VA 0x00447974 (E9 67 E4 4F 00), which ends at VA 0x00945DE0. The highest load ends at 0x012F4A90. The neighboring block-copy body at VA 0x00945D00 writes eight dwords per block; its final block is [0x012F4A70, 0x012F4A90). The static initializer at VA 0x0106BCA0 passes that base through thunk VA 0x00434E00 (E9 3B CA 61 00) to VA 0x00A51840, whose eight dword writes stop at offset 0x1F. Raw disassembly, all caller routes and initializer bounds are in `indexed-bounds-2.log`, `index-routes.log` and `indexed-caller-bounds.log`. The raw value resembling a helper pointer at VA 0x00434488 is the relative displacement of an unrelated E9 thunk to VA 0x0087BE00, not a data pointer.

## Receiver and argument contract

The only producer is the existing matched `BfmeAptScreenOnlineLogin::_bfme_acceptLocale(const char *)` callback. It stores 1 on the path where the list selection is negative. Retail constructor RVA 0x005538A0 publishes the callback route at VA 0x00953B2A. The five bytes `E9 74 47 53 00` at VA 0x0041EC77 jump directly to VA 0x009533F0. These route bytes and caller fields are in `routes.log`. The global storage has no receiver or arguments. The Zero Hour reference search establishes no original name for this BFME storage, so the existing opaque name and unsigned-byte declaration remain.

## Source and preservation

`spellings.log`, `ordinary-and-numeric-spellings.log` and the complete original COFF scan in `guarded-probe.log` identify only `game/GameEngine/Source/GameClient/GUI/OnlineLoginAcceptLocale.cpp` as an actual source user. The existing decorated spelling is `?g_012F4AB0@@3EA` and occurs in one declaring game file. There is no competing recorded spelling at the address. One initialized unsigned-byte definition is appended at EOF under that exact COFF spelling using the permitted extern-C `__identifier` form, while the ordinary C++ extern declaration remains. This is one storage definition, without an alias. Original source snapshots and the complete same-path compiler object are saved in the raw-evidence folder. The data row is sized and byte-verified by ordinary `add_data_match.py` with model `gpt-6.1-sol`.

## Refutation

An additional retail producer or consumer, a wider or indexed access reaching this byte, a pointer route to it from another object, an overlapping ledger owner, a nonzero initial byte, or a changed CODE section, relocation target, readonly payload or EH graph would refute this one-byte repair. The complete-object comparison and the unchanged official source and pass-test gates passed. The corresponding baseline exemption is removed. Raw final verification is in `final-coff-012f4ab0.log`, `pass-test-012f4ab0.log` and `build-final-all-users.log`.
