#!/usr/bin/env python3
"""Check that selected CRT pins really land on their MSVCR71 imports.

``reverse/symbols.csv`` is an additive candidate list.  A pin can therefore
name a body that happens to produce the right relocation while still being a
different CRT helper.  This guard checks the small group of compiler helpers
whose names are easy to confuse: it reads the import directory from the
retail PE, follows a bounded chain of incremental-link ``E9`` jumps, and then
resolves the terminal ``FF 25`` indirect jump through the PE's IAT.

The addresses are deliberately read from ``symbols.csv``.  Nothing in this
module depends on a hard-coded RVA for an IAT slot or a compiler thunk.
"""

from __future__ import annotations

import argparse
import csv
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402


# The decorated compiler names in symbols.csv do not always spell the import
# name exactly: MSVC's import table drops the leading decoration on these
# entries, and drops ``@8`` from the stdcall throw helper.
EXPECTED_IMPORTS = {
    "__CIacos": "_CIacos",
    "__CIasin": "_CIasin",
    "__CIfmod": "_CIfmod",
    "__CIpow": "_CIpow",
    "__CxxThrowException@8": "_CxxThrowException",
}
EXPECTED_DLL = "msvcr71.dll"
MAX_E9_HOPS = 4


class PEFormatError(ValueError):
    """The baseline image is not a readable PE32 import image."""


class PinCheckError(ValueError):
    """A pin does not have the expected E9 -> FF25 import shape."""

    def __init__(self, status, message):
        super().__init__(message)
        self.status = status


@dataclass(frozen=True)
class ImportedSymbol:
    dll: str
    name: str | None
    ordinal: int | None
    iat_rva: int


@dataclass(frozen=True)
class PinResult:
    symbol: str
    address: int
    expected_dll: str
    expected_name: str
    status: str
    chain: tuple[int, ...]
    terminal_rva: int | None = None
    iat_rva: int | None = None
    actual_dll: str | None = None
    actual_name: str | None = None
    detail: str = ""

    @property
    def ok(self):
        return self.status == "ok"


class PEImage:
    """Small dependency-free PE reader for the image and import directory."""

    def __init__(self, data, image_base, sections, imports):
        self.data = bytes(data)
        self.image_base = image_base
        self.sections = sections
        self.imports = imports

        text = next((s for s in sections if s["name"] == ".text"), None)
        if text is None:
            raise PEFormatError("PE has no .text section")
        self.text_low = text["rva"]
        # Thunk bytes must be backed by the file.  Virtual tail padding can
        # extend beyond raw bytes and must not count as a readable .text body.
        self.text_high = text["rva"] + text["raw_size"]

    @classmethod
    def from_path(cls, path):
        return cls.from_bytes(Path(path).read_bytes())

    @classmethod
    def from_bytes(cls, data):
        data = bytes(data)
        if len(data) < 0x40 or data[:2] != b"MZ":
            raise PEFormatError("missing DOS MZ header")
        pe_offset = _u32(data, 0x3C)
        if pe_offset + 4 + 20 > len(data) or data[pe_offset:pe_offset + 4] != b"PE\0\0":
            raise PEFormatError("missing PE signature")

        coff = pe_offset + 4
        machine = _u16(data, coff)
        if machine != 0x014C:
            raise PEFormatError(
                f"unsupported machine 0x{machine:04X}; import guard requires x86 PE32"
            )
        section_count = _u16(data, coff + 2)
        optional_size = _u16(data, coff + 16)
        optional = coff + 20
        if optional + optional_size > len(data) or optional_size < 2:
            raise PEFormatError("truncated optional header")
        magic = _u16(data, optional)
        if magic != 0x10B:
            raise PEFormatError(
                f"unsupported optional-header magic 0x{magic:X}; "
                "import guard requires x86 PE32"
            )
        image_base = _u32(data, optional + 28)
        number_dirs_offset = optional + 92
        dirs_offset = optional + 96
        number_dirs = _u32(data, number_dirs_offset)
        if number_dirs < 2 or dirs_offset + 16 > optional + optional_size:
            raise PEFormatError("PE has no import data directory")
        import_rva, import_size = struct.unpack_from("<II", data, dirs_offset + 8)
        if not import_rva or not import_size:
            raise PEFormatError("PE import directory is empty")

        section_table = optional + optional_size
        sections = []
        for index in range(section_count):
            off = section_table + index * 40
            if off + 40 > len(data):
                raise PEFormatError("truncated section table")
            raw_name = data[off:off + 8].split(b"\0", 1)[0]
            name = raw_name.decode("ascii", "replace")
            virtual_size, rva, raw_size, raw_pointer = struct.unpack_from(
                "<IIII", data, off + 8)
            if raw_size and raw_pointer + raw_size > len(data):
                raise PEFormatError(f"section {name} extends past image")
            sections.append({
                "name": name,
                "virtual_size": virtual_size,
                "rva": rva,
                "raw_size": raw_size,
                "raw_pointer": raw_pointer,
            })

        image = cls(data, image_base, sections, {})
        image.imports = image._read_imports(import_rva, import_size)
        return image

    def rva_to_offset(self, rva, size=1):
        if size < 0:
            raise PEFormatError(f"negative RVA read size {size}")
        for section in self.sections:
            start = section["rva"]
            raw_size = section["raw_size"]
            if start <= rva and rva + size <= start + raw_size:
                delta = rva - start
                offset = section["raw_pointer"] + delta
                if offset < 0 or offset + size > len(self.data):
                    break
                return offset
        raise PEFormatError(
            f"RVA range 0x{rva:08X}+{size} is not backed by section raw data"
        )

    def read_rva(self, rva, size):
        offset = self.rva_to_offset(rva, size)
        end = offset + size
        return self.data[offset:end]

    def _read_c_string(self, rva):
        offset = self.rva_to_offset(rva)
        end = self.data.find(b"\0", offset)
        if end < 0:
            raise PEFormatError(f"unterminated import string at RVA 0x{rva:08X}")
        return self.data[offset:end].decode("ascii", "replace")

    def _read_imports(self, import_rva, import_size):
        imports = {}
        descriptor_count = max(1, import_size // 20)
        for index in range(descriptor_count):
            descriptor_rva = import_rva + index * 20
            try:
                original_first_thunk, _time, _forwarder, name_rva, first_thunk = struct.unpack(
                    "<IIIII", self.read_rva(descriptor_rva, 20))
            except (PEFormatError, struct.error) as exc:
                raise PEFormatError("truncated import descriptor") from exc
            if not any((original_first_thunk, name_rva, first_thunk)):
                return imports
            if not name_rva or not first_thunk:
                raise PEFormatError(f"malformed import descriptor {index}")
            dll = self._read_c_string(name_rva)
            lookup_rva = original_first_thunk or first_thunk
            terminated = False
            for thunk_index in range(0x10000):
                value = struct.unpack(
                    "<I", self.read_rva(lookup_rva + thunk_index * 4, 4))[0]
                if value == 0:
                    terminated = True
                    break
                slot_rva = first_thunk + thunk_index * 4
                if value & 0x80000000:
                    imported = ImportedSymbol(dll, None, value & 0xFFFF, slot_rva)
                else:
                    hint = struct.unpack("<H", self.read_rva(value, 2))[0]
                    del hint  # the guard compares identity, not hint numbers
                    imported = ImportedSymbol(
                        dll, self._read_c_string(value + 2), None, slot_rva)
                imports[slot_rva] = imported
            if not terminated:
                raise PEFormatError(f"unterminated import thunk table for {dll}")
        raise PEFormatError("import directory has no terminating descriptor")

    def _is_text(self, rva):
        return self.text_low <= rva < self.text_high

    def _read_text(self, rva, size):
        """Read one complete instruction from the backed .text section."""
        if size <= 0 or not self._is_text(rva) or not self._is_text(rva + size - 1):
            raise PinCheckError(
                "bad-thunk",
                f"RVA range 0x{rva:08X}+{size} leaves .text",
            )
        try:
            # read_rva's section check also rejects a range that crosses into a
            # neighbouring section whose raw bytes happen to be contiguous.
            return self.read_rva(rva, size)
        except PEFormatError as exc:
            raise PinCheckError("bad-thunk", str(exc)) from exc

    def follow_import_thunk(self, address, max_e9_hops=MAX_E9_HOPS):
        """Return ``(terminal_rva, iat_rva, chain)`` for an E9 -> FF25 thunk."""
        current = address
        chain = [current]
        for _ in range(max_e9_hops + 1):
            if not self._is_text(current):
                raise PinCheckError("bad-thunk", "thunk target leaves .text")
            opcode = self._read_text(current, 1)
            if opcode[:1] == b"\xE9":
                instruction = self._read_text(current, 5)
                displacement = struct.unpack("<i", instruction[1:])[0]
                target = current + 5 + displacement
                if not self._is_text(target):
                    raise PinCheckError("bad-thunk", "E9 target leaves .text")
                if target in chain:
                    raise PinCheckError("bad-thunk", "E9 thunk cycle")
                chain.append(target)
                current = target
                continue
            break
        else:
            raise PinCheckError("bad-thunk", f"more than {max_e9_hops} E9 hops")

        instruction = self._read_text(current, 6)
        if instruction[:2] != b"\xFF\x25":
            raise PinCheckError(
                "wrong-body",
                f"terminal RVA 0x{current:08X} is not an FF25 import jump",
            )
        operand = struct.unpack("<I", instruction[2:])[0]
        if operand < self.image_base:
            raise PinCheckError("bad-thunk", "FF25 operand precedes image base")
        iat_rva = operand - self.image_base
        if iat_rva not in self.imports:
            raise PinCheckError(
                "wrong-import",
                f"FF25 slot RVA 0x{iat_rva:08X} is absent from the import table",
            )
        return current, iat_rva, tuple(chain)


def _u16(data, offset):
    try:
        return struct.unpack_from("<H", data, offset)[0]
    except struct.error as exc:
        raise PEFormatError("truncated PE field") from exc


def _u32(data, offset):
    try:
        return struct.unpack_from("<I", data, offset)[0]
    except struct.error as exc:
        raise PEFormatError("truncated PE field") from exc


def _u64(data, offset):
    try:
        return struct.unpack_from("<Q", data, offset)[0]
    except struct.error as exc:
        raise PEFormatError("truncated PE field") from exc


def load_guarded_pins(path):
    """Read only the five guarded names from a symbols.csv-like file."""
    pins = {name: [] for name in EXPECTED_IMPORTS}
    with Path(path).open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            symbol = row.get("name", "")
            if symbol not in EXPECTED_IMPORTS:
                continue
            try:
                address = int(row["address"], 16)
            except (KeyError, TypeError, ValueError) as exc:
                raise ValueError(f"invalid address for {symbol!r}") from exc
            if address not in pins[symbol]:
                pins[symbol].append(address)
    return pins


def inspect_pin(image, symbol, address, expected_name=None, max_e9_hops=MAX_E9_HOPS):
    """Check one pin and return a structured result suitable for tests/tools."""
    expected_name = expected_name or EXPECTED_IMPORTS[symbol]
    expected_dll = EXPECTED_DLL
    try:
        terminal, iat_rva, chain = image.follow_import_thunk(address, max_e9_hops)
    except (PEFormatError, PinCheckError) as exc:
        status = exc.status if isinstance(exc, PinCheckError) else "bad-thunk"
        return PinResult(
            symbol, address, expected_dll, expected_name, status, tuple([address]),
            detail=str(exc),
        )

    imported = image.imports[iat_rva]
    actual_dll = imported.dll
    actual_name = imported.name
    if actual_dll.lower() != expected_dll or actual_name != expected_name:
        detail = (
            f"expected {expected_dll}!{expected_name} but found "
            f"{actual_dll}!{actual_name or '#' + str(imported.ordinal)}"
        )
        return PinResult(
            symbol, address, expected_dll, expected_name, "wrong-import", chain,
            terminal, iat_rva, actual_dll, actual_name, detail,
        )
    return PinResult(
        symbol, address, expected_dll, expected_name, "ok", chain,
        terminal, iat_rva, actual_dll, actual_name,
    )


def check_pins(image, pins, max_e9_hops=MAX_E9_HOPS):
    """Check all expected names, including a failure for a missing pin."""
    results = []
    for symbol, expected_name in EXPECTED_IMPORTS.items():
        addresses = pins.get(symbol, ())
        if not addresses:
            results.append(PinResult(
                symbol, 0, EXPECTED_DLL, expected_name, "missing-pin", tuple(),
                detail="symbols.csv has no pin for this guarded name",
            ))
            continue
        results.extend(
            inspect_pin(image, symbol, address, expected_name, max_e9_hops)
            for address in addresses
        )
    return results


def _format_result(result):
    address = f"0x{result.address:08X}" if result.address else "<missing>"
    chain = " -> ".join(f"0x{x:08X}" for x in result.chain) or "<none>"
    if result.ok:
        return (
            f"OK {result.symbol} @ {address}: "
            f"{result.actual_dll}!{result.actual_name} via {chain}"
        )
    return f"FAIL {result.symbol} @ {address}: {result.status}: {result.detail} (chain {chain})"


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, default=build.EXE,
                        help="retail PE baseline (default: build.py baseline)")
    parser.add_argument("--symbols", type=Path, default=build.SYMBOLS,
                        help="symbols.csv pin list")
    parser.add_argument("--max-e9-hops", type=int, default=MAX_E9_HOPS,
                        help="maximum bounded E9 hops before FF25 (default: %(default)s)")
    parser.add_argument("--json", action="store_true", help="emit result objects as JSON")
    args = parser.parse_args(argv)
    if args.max_e9_hops < 0:
        parser.error("--max-e9-hops must be non-negative")

    try:
        image = PEImage.from_path(args.exe)
        pins = load_guarded_pins(args.symbols)
        results = check_pins(image, pins, args.max_e9_hops)
    except (OSError, PEFormatError, ValueError) as exc:
        print(f"import_pin_guard: ERROR: {exc}", file=sys.stderr)
        return 2

    if args.json:
        import json
        print(json.dumps([result.__dict__ for result in results], indent=2))
    else:
        for result in results:
            print(_format_result(result))
    failures = [result for result in results if not result.ok]
    # Keep stdout machine-readable when --json is selected.  Human summaries
    # belong on stderr in both modes so a caller can pipe JSON safely.
    print(
        f"import_pin_guard: {'PASS' if not failures else 'FAIL'} "
        f"{len(results) - len(failures)}/{len(results)} guarded pins",
        file=sys.stderr,
    )
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
