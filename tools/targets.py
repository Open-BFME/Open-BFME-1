"""Immutable, hash-bound context for explicit binary targets."""
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import struct
from types import MappingProxyType
from typing import Mapping

import pefile


ROOT = Path(__file__).resolve().parents[1]


class TargetError(ValueError):
    """A target's configuration, image or requested address is invalid."""


@dataclass(frozen=True, slots=True)
class CompilerProfile:
    flags: tuple[str, ...]
    toolchain_includes: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class Section:
    name: str
    rva: int
    virtual_size: int
    raw_size: int
    raw_offset: int
    characteristics: int


@dataclass(frozen=True, slots=True)
class Export:
    name: str | None
    ordinal: int
    rva: int
    forwarder: str | None


@dataclass(frozen=True, slots=True)
class Import:
    dll: str
    name: str | None
    ordinal: int | None
    iat_rva: int


@dataclass(frozen=True, slots=True)
class Relocation:
    rva: int
    type: int


def initial_ilt_map(image_bytes, text):
    """Recognize only the padded, contiguous initial MSVC incremental-link table.

    An E9 outside this table can be a real tail-call function. Routing through
    it would erase that function's identity and attribute its caller to a callee.
    """
    size = min(text.virtual_size, text.raw_size)
    raw = image_bytes[text.raw_offset:text.raw_offset + size]
    if len(raw) < 10 or raw[:6] != b"\xCC" * 5 + b"\xE9":
        return MappingProxyType({})
    offset, thunks = 5, {}
    while offset < len(raw) and raw[offset] == 0xE9:
        if offset + 5 > len(raw):
            raise TargetError("initial ILT ends inside a jump instruction")
        rva = text.rva + offset
        target = rva + 5 + struct.unpack_from("<i", raw, offset + 1)[0]
        if not text.rva <= target < text.rva + size:
            raise TargetError(f"initial ILT entry 0x{rva:X} jumps outside file-backed .text")
        thunks[rva] = target
        offset += 5
    if len(thunks) < 2:
        return MappingProxyType({})
    padding_end = max(offset + 3, (offset + 15) & ~15)
    if padding_end > len(raw) or raw[offset:padding_end] != b"\xCC" * (padding_end - offset):
        raise TargetError("initial ILT has no int3 padding through the next 16-byte boundary")
    if any(text.rva + 5 <= target < text.rva + offset for target in thunks.values()):
        raise TargetError("initial ILT points back inside its own table")
    return MappingProxyType(thunks)


@dataclass(frozen=True, slots=True)
class Target:
    target_id: str
    root: Path
    config_path: Path
    image_path: Path
    expected_sha256: str
    ledger_root: Path
    build_root: Path
    profiles: Mapping[str, CompilerProfile]
    image_base: int
    sections: tuple[Section, ...]
    image_bytes: bytes = field(repr=False)
    exports: tuple[Export, ...] = field(repr=False)
    imports: tuple[Import, ...] = field(repr=False)
    relocations: tuple[Relocation, ...] = field(repr=False)
    ilt_thunks: Mapping[int, int] = field(repr=False)

    @property
    def ledger_path(self):
        return self.ledger_root / "functions.csv"

    @property
    def text_section(self):
        matches = [section for section in self.sections if section.name == ".text"]
        if len(matches) != 1:
            raise TargetError(f"{self.target_id}: expected exactly one .text section")
        return matches[0]

    def verify_hash(self):
        return _verified_image(self.image_path, self.expected_sha256)

    def follow_ilt(self, rva):
        return self.ilt_thunks.get(rva, rva)

    @property
    def ilt_provenance(self):
        if not self.ilt_thunks:
            return None
        start, end = min(self.ilt_thunks), max(self.ilt_thunks) + 5
        return {"start_rva": start, "end_rva": end, "entry_count": len(self.ilt_thunks),
                "sha256": hashlib.sha256(self.read_rva(start, end - start)).hexdigest()}

    def section_for_rva(self, rva):
        if not isinstance(rva, int) or rva < 0:
            raise TargetError(f"{self.target_id}: expected a nonnegative RVA")
        for section in self.sections:
            if section.rva <= rva < section.rva + section.virtual_size:
                return section
        raise TargetError(f"{self.target_id}: RVA 0x{rva:X} is outside virtual PE sections")

    def read_rva(self, rva, size):
        if not isinstance(rva, int) or not isinstance(size, int) or rva < 0 or size <= 0:
            raise TargetError(f"{self.target_id}: expected nonnegative RVA and positive size")
        section = self.section_for_rva(rva)
        offset = rva - section.rva
        if offset + size > min(section.virtual_size, section.raw_size):
            raise TargetError(
                f"{self.target_id}: RVA 0x{rva:X}+{size} is not fully backed by "
                f"{section.name}'s virtual and raw extent")
        start = section.raw_offset + offset
        return self.image_bytes[start:start + size]


def _keys(value, expected, label):
    if not isinstance(value, dict) or set(value) != set(expected):
        raise TargetError(f"{label}: expected fields {', '.join(sorted(expected))}")


def _relative(value, label):
    if (not isinstance(value, str) or not value or "\\" in value or ":" in value
            or PurePosixPath(value).is_absolute() or ".." in PurePosixPath(value).parts):
        raise TargetError(f"{label}: expected a relative path without '..'")
    return value


def _under(root, value, label):
    path = (root / _relative(value, label)).resolve()
    if not path.is_relative_to(root):
        raise TargetError(f"{label}: path escapes repository root: {value}")
    return path


def _verified_image(path, expected):
    try:
        data = path.read_bytes()
    except OSError as error:
        raise TargetError(f"cannot read target image {path}: {error}") from error
    actual = hashlib.sha256(data).hexdigest()
    if actual != expected:
        raise TargetError(f"{path}: SHA-256 mismatch; expected {expected}, got {actual}")
    return data


def _profiles(values):
    if not isinstance(values, dict) or not values:
        raise TargetError("profiles: expected at least one compiler profile")
    result = {}
    for name, value in values.items():
        if not re.fullmatch(r"[a-z0-9][a-z0-9-]*", name):
            raise TargetError(f"invalid compiler profile name: {name!r}")
        _keys(value, ("flags", "toolchain_includes"), f"profile {name}")
        flags, includes = value["flags"], value["toolchain_includes"]
        if not isinstance(flags, list) or not flags or any(
                not isinstance(flag, str) or not flag.startswith(("-", "/")) for flag in flags):
            raise TargetError(f"profile {name}: flags must be a nonempty list of compiler options")
        if not isinstance(includes, list):
            raise TargetError(f"profile {name}: toolchain_includes must be a list")
        result[name] = CompilerProfile(tuple(flags), tuple(
            _relative(path, f"profile {name} include") for path in includes))
    return MappingProxyType(result)


def _name(value):
    return value.decode("ascii") if value is not None else None


def load_target(target_id, *, root=ROOT):
    if not isinstance(target_id, str) or not re.fullmatch(r"[a-z0-9][a-z0-9-]*", target_id):
        raise TargetError(f"invalid target ID: {target_id!r}")
    root = Path(root).resolve()
    config_path = _under(root, f"{target_id}/target.json", "target config")
    try:
        config = json.loads(config_path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as error:
        raise TargetError(f"cannot load target {target_id} at {config_path}: {error}") from error
    _keys(config, ("schema_version", "target_id", "image", "ledger_root", "build_root", "profiles"),
          str(config_path))
    if type(config["schema_version"]) is not int or config["schema_version"] != 1 or config["target_id"] != target_id:
        raise TargetError(f"{config_path}: expected schema_version 1 and target_id {target_id}")
    _keys(config["image"], ("path", "sha256"), "image")
    expected = config["image"]["sha256"]
    if not isinstance(expected, str) or not re.fullmatch(r"[0-9a-f]{64}", expected):
        raise TargetError(f"{config_path}: image.sha256 must be 64 lowercase hex digits")
    for key, expected_path in (("ledger_root", f"reverse/{target_id}"),
                               ("build_root", f"build/{target_id}")):
        if config[key] != expected_path:
            raise TargetError(f"{target_id}: {key} must be {expected_path} to isolate target state")
    image_path = _under(root, config["image"]["path"], "image.path")
    ledger_root = _under(root, config["ledger_root"], "ledger_root")
    build_root = _under(root, config["build_root"], "build_root")
    for path, key in ((ledger_root, "ledger_root"), (build_root, "build_root")):
        if path != root / config[key]:
            raise TargetError(f"{target_id}: {key} must not redirect through a symlink")
    profiles = _profiles(config["profiles"])
    data = _verified_image(image_path, expected)
    try:
        pe = pefile.PE(data=data, fast_load=True)
        if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.Magic != 0x10B:
            raise TargetError(f"{target_id}: only x86 PE32 targets are supported")
        pe.parse_data_directories(directories=[0, 1, 5])
        for index, attribute in ((0, "DIRECTORY_ENTRY_EXPORT"), (1, "DIRECTORY_ENTRY_IMPORT"),
                                 (5, "DIRECTORY_ENTRY_BASERELOC")):
            directory = pe.OPTIONAL_HEADER.DATA_DIRECTORY[index]
            if directory.Size and directory.VirtualAddress and not hasattr(pe, attribute):
                raise TargetError(f"{target_id}: cannot parse PE directory {index}")
        sections = tuple(Section(_name(section.Name.rstrip(b"\0")), section.VirtualAddress,
                                 section.Misc_VirtualSize, section.SizeOfRawData,
                                 section.PointerToRawData, section.Characteristics)
                         for section in pe.sections)
        for section in sections:
            if section.raw_size and section.raw_offset + section.raw_size > len(data):
                raise TargetError(f"{target_id}: {section.name} raw extent exceeds image size")
        ranges = sorted((section.rva, section.rva + section.virtual_size) for section in sections)
        if any(end > next_start for (_, end), (next_start, _) in zip(ranges, ranges[1:])):
            raise TargetError(f"{target_id}: overlapping virtual PE sections")
        exports = tuple(Export(_name(symbol.name), symbol.ordinal, symbol.address, _name(symbol.forwarder))
                        for symbol in pe.DIRECTORY_ENTRY_EXPORT.symbols) if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") else ()
        imports = tuple(Import(_name(dll.dll), _name(symbol.name), symbol.ordinal,
                               symbol.address - pe.OPTIONAL_HEADER.ImageBase)
                        for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", ()) for symbol in dll.imports)
        relocations = tuple(Relocation(entry.rva, entry.type)
                            for block in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", ()) for entry in block.entries)
        image_base = pe.OPTIONAL_HEADER.ImageBase
        pe.close()
    except (pefile.PEFormatError, UnicodeError, IndexError) as error:
        raise TargetError(f"{target_id}: invalid PE image: {error}") from error
    texts = [section for section in sections if section.name == ".text"]
    if len(texts) != 1:
        raise TargetError(f"{target_id}: expected exactly one .text section")
    target = Target(target_id, root, config_path, image_path, expected, ledger_root, build_root,
                    profiles, image_base, sections, data, exports, imports, relocations,
                    initial_ilt_map(data, texts[0]))
    return target
