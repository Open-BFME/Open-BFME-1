# Unsigned-byte storage at VA 0x012F81A9

The existing address-derived name `g_012F81A9` owns exactly one unsigned byte at retail VA 0x012F81A9 (RVA 0x00EF81A9). This records storage and does not claim an original EA name or a Boolean type.

## Retail facts

The reference image is the repository's retail-1.03-unpacked executable. The image SHA-256 and section bounds are recorded in `build/rlink/identity-bytes-1791443509/retail-probe-3.log`. This address is in the writable .data virtual-only tail and reads as 00 before execution. The PE base-relocation directory is empty. The complete executable file contains exactly five little-endian fields naming this byte, at file offsets 0x006E88DE, 0x006E8A11, 0x006E8A45, 0x006E8AE7 and 0x006E8AF2. Four belong to `A0 A9 81 2F 01` byte loads at VAs 0x00AE88DD, 0x00AE8A10, 0x00AE8A44 and 0x00AE8AE6. The fifth belongs to `88 0D A9 81 2F 01` at VA 0x00AE8AF0, a one-byte store of CL. All are in the matched body at RVA 0x006E8800. There are no address-taking fields, indexed references, wider accesses spanning this byte, or additional producer or consumer instructions in the executable scan. Raw results are in `guarded-probe.log` and the complete containing-body disassembly is in `retail-probe-3.log` under the same folder.

Neighboring dwords at VAs 0x012F81A0 and 0x012F81A4 belong to the average-FPS accesses and stop before this byte. The separate storage beginning at VA 0x012F81AC has its own dword writes and pointer-taking route. No byte at VA 0x012F81A8 or 0x012F81AA is absorbed by this repair; padding or adjacent display storage establishes no array extent. The complete data-row range check, DIR32 names and pin check find no overlapping owner or name inside [0x012F81A9, 0x012F81AA).

## Receiver and argument contract

The four reads and one write are performed only by the existing matched `W3DDisplay::drawThirdDebugDisplay()`. The byte is tested for zero to select a color and is updated to the zero-test's 0/1 result when the function's local flip state requires it. These operations establish a mutable byte, but do not establish an original Boolean declaration or an EA variable name. The five bytes `E9 23 8F 6B 00` at VA 0x0042F8D8 jump directly to VA 0x00AE8800. The draw dispatcher at VA 0x00AE8E1C jumps through that thunk with the W3DDisplay receiver in ECX. These route bytes and caller fields are in `routes.log`. The global storage has no receiver or arguments. The Zero Hour reference search establishes no original name for this BFME storage, so the existing opaque name and unsigned-byte declaration remain.

## Source and preservation

`spellings.log`, `ordinary-and-numeric-spellings.log` and the complete original COFF scan in `guarded-probe.log` identify only `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawThirdDebugDisplay006e8800.cpp` as an actual source user. The existing decorated spelling is `?g_012F81A9@@3EA` and occurs in one declaring game file. There is no competing recorded spelling at the address. One initialized unsigned-byte definition is appended at EOF under that exact COFF spelling using the permitted extern-C `__identifier` form, while the ordinary C++ extern declaration remains. This is one storage definition, without an alias. Original source snapshots and the complete same-path compiler object are saved in the raw-evidence folder. The data row is sized and byte-verified by ordinary `add_data_match.py` with model `gpt-6.1-sol`.

## Refutation

An additional retail producer or consumer, a wider or indexed access reaching this byte, a pointer route to it from another object, an overlapping ledger owner, a nonzero initial byte, or a changed CODE section, relocation target, readonly payload or EH graph would refute this one-byte repair. The complete-object comparison and the unchanged official source and pass-test gates passed. The corresponding baseline exemption is removed. Raw final verification is in `final-coff-012f81a9.log`, `pass-test-012f81a9.log` and `build-final-all-users.log`.
