#!/usr/bin/env python3
import concurrent.futures
import csv
import functools
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import threading
from pathlib import Path

from coffar import RELOC_WIDTH, read_archive
from gen_case_shims import ensure_case_shims
from portable_lock import lock, unlock


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "manifest.json"
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
BUILD_DIR = ROOT / "build" / "match"
PATCH_DIR = ROOT / "build" / "patch"


LIB_SUFFIX = ".lib"
# A row whose bytes are compared with every relocation site masked out is only
# as good as the bytes that remain. Below this many concrete bytes the
# comparison proves nothing, so the row is not evidence and the gate says so.
MIN_LIB_CONCRETE = 8


def resolved(path):
    # Path.resolve() can hand back a Windows extended-length \\?\ path once the
    # tree gets deep enough (Code/gen_small/*.cpp under a long checkout dir on
    # Python 3.14). ROOT never carries that prefix, so relative_to() rejects the
    # result and the gate dies in its last phase. Strip it back off.
    out = Path(path).resolve()
    text = str(out)
    return Path(text[4:]) if text.startswith("\\\\?\\") else out


def obj_path(source, member=None):
    # Namespace objs by the source's repo-relative path, not its bare stem:
    # same-basename sources in different tree dirs must not collide.
    # Encode uppercase as ^x because wine resolves paths case-insensitively:
    # INI.cpp and ini.cpp would otherwise overwrite each other's obj.
    rel = resolved(source).relative_to(ROOT)
    stem = "_".join(rel.with_suffix("").parts)
    if member is not None:
        # One .lib holds hundreds of members and a row names exactly one, so the
        # obj is per (source, member) — keying on the source alone would give
        # 2,000 rows spanning 136 members a single shared output path.
        stem += "_" + member_stem(member)
    encoded = "".join(("^" + c.lower()) if c.isupper() else c for c in stem)
    return BUILD_DIR / (encoded + ".obj")


def member_stem(member):
    """Filename part of an archive member name (`obj\\i386\\d3dx9tex.obj`)."""
    return re.split(r"[\\/]", member)[-1].removesuffix(".obj")


def ledger_member(row):
    """The archive member a .lib-sourced row's bytes come from."""
    match = re.search(r"(?:^|;)member=([^;]+)", row.get("notes", ""))
    if match is None:
        raise SystemExit(
            f"{row['name']}: source {row['source']} is a static library but the row "
            "has no `member=` note naming the object its bytes come from")
    return match.group(1)


def row_object(row):
    """The object file holding this row's code: a compiled TU, or a lib member."""
    source = ROOT / row["source"]
    if source.suffix.lower() == LIB_SUFFIX:
        return obj_path(source, ledger_member(row))
    return obj_path(source)


def require_row_object(row):
    """row_object, but a missing object is fatal rather than skipped.

    The string-ref and DIR32 verifiers used to `continue` past an absent obj
    while still reporting "0 unverified/skipped", so a whole source's rows could
    drop out of both checks and leave the summary line saying everything passed.
    """
    obj = row_object(row)
    if not obj.exists():
        raise SystemExit(
            f"{row['name']} ({row['source']}): object {obj.relative_to(ROOT)} is missing, "
            "so this row cannot be verified. Run the full ./build.sh, which builds it.")
    return obj


def extract_lib_members(rows):
    """Unpack every archive member the given rows name into the build dir.

    A member is a verbatim COFF object, so extracting it verbatim is all a
    .lib-sourced row needs: from here it goes through the same symbol lookup,
    relocation read and byte comparison as a compiled translation unit.
    """
    wanted = {}
    for row in rows:
        source = ROOT / row["source"]
        if source.suffix.lower() == LIB_SUFFIX:
            wanted.setdefault(source, set()).add(ledger_member(row))
    for source, names in sorted(wanted.items()):
        if not source.exists():
            raise SystemExit(f"functions.csv references missing static library: "
                             f"{source.relative_to(ROOT)}")
        members = dict(read_archive(source))
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        for name in sorted(names):
            if name not in members:
                raise SystemExit(
                    f"{source.relative_to(ROOT)}: no member named {name!r} — a row's "
                    "`member=` note does not match any object in the archive")
            output = obj_path(source, name)
            body = members[name]
            if not output.exists() or output.read_bytes() != body:
                output.write_bytes(body)
    if wanted:
        print(f"Lib members: {sum(len(n) for n in wanted.values())} extracted from "
              f"{len(wanted)} archive(s)")
NOOP_EXE = PATCH_DIR / "lotrbfme.noop.exe"
DEFAULT_VC71_ROOT = (
    ROOT
    / "build"
    / "toolchains"
    / "vs2003"
    / "Program Files"
    / "Microsoft Visual Studio .NET 2003"
)
_WINE_PATH_CACHE = {}
_WINE_PATH_LOCK = threading.Lock()


def u16(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def hash_file(path, algorithm):
    digest = hashlib.new(algorithm)
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def verify_baseline():
    with MANIFEST.open("r", encoding="utf-8") as handle:
        manifest = json.load(handle)

    baseline_dir = MANIFEST.parent
    verified = 0

    for entry in manifest["files"]:
        path = baseline_dir / entry["path"]
        if not path.exists():
            raise SystemExit(f"missing baseline file: {path}")

        size = path.stat().st_size
        if size != entry["size"]:
            raise SystemExit(f"{entry['path']}: size {size} != {entry['size']}")

        sha256 = hash_file(path, "sha256")
        if sha256 != entry["sha256"]:
            raise SystemExit(f"{entry['path']}: sha256 mismatch")

        md5 = hash_file(path, "md5")
        if md5 != entry["md5"]:
            raise SystemExit(f"{entry['path']}: md5 mismatch")

        verified += 1

    print(f"Baseline: OK {verified} file(s) ({manifest['id']})")


def pe_sections(data):
    pe_offset = u32(data, 0x3C)
    coff = pe_offset + 4
    section_count = u16(data, coff + 2)
    optional_size = u16(data, coff + 16)
    section_table = coff + 20 + optional_size

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace").strip()
        virtual_size = u32(data, offset + 8)
        virtual_address = u32(data, offset + 12)
        raw_size = u32(data, offset + 16)
        raw_pointer = u32(data, offset + 20)
        sections.append(
            {
                "name": name,
                "rva": virtual_address,
                "size": max(virtual_size, raw_size),
                "raw_pointer": raw_pointer,
            }
        )
    return sections


def rva_to_file_offset(sections, rva):
    for section in sections:
        start = section["rva"]
        end = start + section["size"]
        if start <= rva < end:
            return section["raw_pointer"] + (rva - start)
    raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")


@functools.lru_cache(maxsize=1)
def exe_image():
    """The retail image and its section table, read once per process.

    The baseline is md5-verified and never rewritten during a run, so this is the
    same bytes every call. It used to be re-read per call: next_work.py asks for
    4,008 candidate bodies and spent 13 of its 14 seconds re-reading the same
    13 MB file and re-parsing the same section table.
    """
    data = EXE.read_bytes()
    return data, pe_sections(data)


def read_target_bytes(rva, size):
    data, sections = exe_image()
    offset = rva_to_file_offset(sections, rva)
    return data[offset : offset + size]


def coff_name(data, symbol_offset, string_table):
    short_name = data[symbol_offset : symbol_offset + 8]
    if short_name[:4] == b"\0\0\0\0":
        string_offset = u32(short_name, 4)
        end = string_table.index(b"\0", string_offset)
        return string_table[string_offset:end].decode("ascii", errors="replace")
    return short_name.rstrip(b"\0").decode("ascii", errors="replace")


# A COFF symbol's SectionNumber is int16, so a symbol living in section 0x8000
# or beyond reads back negative and every `section > 0` test below rejects it as
# undefined. A 250-instantiation generated TU needed 44,768 COMDATs and lost 56
# rows to exactly that, diagnosed only as "symbol not found in object".
COFF_SECTION_CEILING = 0x7FFF


def read_object_symbols(data):
    symbol_table = u32(data, 8)
    symbol_count = u32(data, 12)
    string_table = data[symbol_table + symbol_count * 18 :]
    symbols = []
    index = 0
    while index < symbol_count:
        offset = symbol_table + index * 18
        name = coff_name(data, offset, string_table)
        value = u32(data, offset + 8)
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        aux_count = data[offset + 17]
        symbols.append({"name": name, "value": value, "section": section_number, "aux": aux_count})
        for _ in range(aux_count):
            index += 1
            offset = symbol_table + index * 18
            symbols.append({"name": "", "value": 0, "section": 0, "aux": 0})
        index += 1
    return symbols


@functools.lru_cache(maxsize=256)
def _object_layout(path_str, mtime_ns, size):
    """Parsed COFF layout, keyed by (path, mtime, size) so a recompile misses.

    The gate reads the SAME multi-MB object once per ledger row; with generated
    claims putting hundreds of rows on one TU, re-reading and re-parsing per row
    came to dominate full-gate wall time (91k rows over ~4k objects). One parse
    per object version is behavior-identical."""
    data = Path(path_str).read_bytes()
    section_count = u16(data, 2)
    section_table = 20

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        sections.append(
            {
                "name": data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace"),
                "raw_size": u32(data, offset + 16),
                "raw_pointer": u32(data, offset + 20),
                "reloc_count": u16(data, offset + 32),
                "reloc_pointer": u32(data, offset + 24),
            }
        )

    return data, sections, read_object_symbols(data)


def read_object_symbol_bytes(path, symbol_name, expected_size=None):
    stat = path.stat()
    data, sections, symbols = _object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    resolved_name = symbol_name
    if not any(s["name"] == symbol_name and s["section"] > 0 for s in symbols):
        # MSVC hashes the absolute source path into anonymous-namespace names,
        # so the same function gets a different ?A0x........ token in each
        # clone/worktree. Accept only one otherwise-identical defined symbol.
        normalized = re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", symbol_name)
        candidates = [s["name"] for s in symbols if s["section"] > 0 and
                      re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", s["name"]) == normalized]
        if len(candidates) == 1:
            resolved_name = candidates[0]
        # Compiler-generated dynamic-initializer ordinals change when globals
        # differ between the BFME and ZH translation units.  Resolve a stale
        # retail ordinal only when size identifies one initializer uniquely.
        elif expected_size is not None and re.fullmatch(r"_\$E\d+", symbol_name):
            candidates = []
            for candidate in symbols:
                if candidate["section"] <= 0 or not re.fullmatch(r"_\$E\d+", candidate["name"]):
                    continue
                section = sections[candidate["section"] - 1]
                start = section["raw_pointer"] + candidate["value"]
                end = section["raw_pointer"] + section["raw_size"]
                if len(data[start:end].rstrip(b"\xcc")) == expected_size:
                    candidates.append(candidate["name"])
            if len(candidates) == 1:
                resolved_name = candidates[0]
    index = 0
    while index < len(symbols):
        symbol = symbols[index]
        # the same name can appear as a sectionless entry (e.g. weak external)
        # before its real definition; keep scanning for the defined one
        if symbol["name"] == resolved_name and symbol["section"] > 0:
            section = sections[symbol["section"] - 1]
            value = symbol["value"]
            start = section["raw_pointer"] + value
            end = section["raw_pointer"] + section["raw_size"]
            bytes_data = data[start:end]

            relocs = []
            for r in range(section["reloc_count"]):
                ro = section["reloc_pointer"] + r * 10
                rva = u32(data, ro)
                sym_idx = u32(data, ro + 4)
                rtype = u16(data, ro + 8)
                if value <= rva < value + len(bytes_data):
                    relocs.append((rva - value, rtype, symbols[sym_idx]["name"]))

            return bytes_data, relocs

        index += 1

    if len(sections) > COFF_SECTION_CEILING:
        raise ValueError(
            f"symbol not found in object: {symbol_name} — {path.name} carries "
            f"{len(sections)} sections and a COFF section number is int16, so every symbol "
            f"past section {COFF_SECTION_CEILING} reads negative and is invisible to any "
            "reader. Split the batch that produced this TU: its limit is a section budget, "
            "not a row count.")
    raise ValueError(f"symbol not found in object: {symbol_name}")


def ledger_object_symbol(row):
    """Return an explicit TU-local object symbol alias from the notes column."""
    match = re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes", ""))
    return match.group(1) if match else row["name"]


def vc71_root():
    root = Path(os.environ.get("VC71_ROOT", DEFAULT_VC71_ROOT))
    compiler = root / "Vc7" / "bin" / "cl.exe"
    if not compiler.exists():
        raise SystemExit(
            "MSVC 7.1 cl.exe not found. Set VC71_ROOT to a Visual Studio .NET 2003 "
            f"install root, or place it at {DEFAULT_VC71_ROOT.relative_to(ROOT)}."
        )
    return root


def wine_path(path):
    key = str(path)
    if os.name == "nt":
        return key
    with _WINE_PATH_LOCK:
        cached = _WINE_PATH_CACHE.get(key)
        if cached is not None:
            return cached
        winepath = shutil.which("winepath")
        if winepath is None:
            raise SystemExit("winepath not found. Install Wine to run MSVC 7.1 on this host.")
        converted = subprocess.check_output([winepath, "-w", key], text=True).strip()
        _WINE_PATH_CACHE[key] = converted
        return converted


def stlport_include_dir():
    """Directory of STLport 4.5.3 headers, or None. The game linked STLport, so
    files using std:: containers must compile against it to byte-match (MSVC's own
    STL emits different code). Prefer a vendored copy; fall back to an env var."""
    candidates = [ROOT / "vendor" / "stlport"]
    env_root = os.environ.get("STLPORT_ROOT")
    if env_root:
        candidates.append(Path(env_root))
    for path in candidates:
        if (path / "list").exists():
            return path
    return None


# The vendored Zero Hour tree. Its whole value is being unmodified upstream, so
# its files carry neither the `// stlport` marker nor a `// cl:` line that a
# Code/ source uses to declare its build settings; a row sourced from here gets
# its flags from the path instead. Both settings below are what the 420-TU sweep
# compiled and matched with.
ZH_REFERENCE_ROOT = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
# The base game beside it. BFME forked the SAGE engine before Zero Hour did, so
# where the expansion's copy of a translation unit drifted, the base game's copy
# is the one whose bodies still compile byte-true.
GENERALS_REFERENCE_ROOT = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "Generals" / "Code"
_ZH_INCLUDE_PARTS = (
    "GameEngine/Include", "GameEngine/Source", "Libraries/Include",
    "Libraries/Source", "Libraries/Source/Compression",
    "Libraries/Source/WWVegas", "Libraries/Source/WWVegas/WWLib",
    "GameEngineDevice/Include", "Libraries/Source/WWVegas/WW3D2",
    "Libraries/Source/WWVegas/WWMath", "Libraries/Source/WWVegas/WWDebug",
    "Libraries/Source/WWVegas/WWSaveLoad", "Main",
)


def _reference_include_dirs(*roots):
    return ["-I" + directory for directory in ["reference/shims/sweep"] + [
        f"{root.relative_to(ROOT).as_posix()}/{part}"
        for root in roots for part in _ZH_INCLUDE_PARTS
    ]]


_ZH_BASE_FLAGS = ["-DNDEBUG", "-DWIN32", "-D_WINDOWS", "-MD", "-EHsc"]
_ZH_FLAGS = _ZH_BASE_FLAGS + _reference_include_dirs(ZH_REFERENCE_ROOT)
# Base-game headers win; the Zero Hour tail is on the path only because
# reference/shims/sweep was written against the expansion and includes headers
# (Common/ObjectStatusTypes.h) the base game never shipped.
_GENERALS_FLAGS = _ZH_BASE_FLAGS + _reference_include_dirs(
    GENERALS_REFERENCE_ROOT, ZH_REFERENCE_ROOT)


def zh_reference_source(source):
    """`source` relative to whichever vendored SAGE tree holds it, or None."""
    if source is None:
        return None
    for root in (ZH_REFERENCE_ROOT, GENERALS_REFERENCE_ROOT):
        try:
            return resolved(source).relative_to(root).as_posix()
        except ValueError:
            continue
    return None


def source_needs_stlport(source):
    """A source declares it needs STLport with a `// stlport` line near the top.
    STLport shadows standard headers (<cmath>, <cstring>, ...), so it must be
    opt-in per file — never on the global include path for STL-free matched files."""
    if source is None:
        return False
    relative = zh_reference_source(source)
    if relative is not None:
        # The sweep's split over 420 vendored TUs, with no exceptions either way:
        # the WWVegas libraries match against MSVC's own STL, and every GameEngine
        # TU needs STLport (which took their compile rate from 29% to 94.6%).
        return not relative.startswith("Libraries/Source/WWVegas/")
    try:
        with Path(source).open("r", encoding="utf-8", errors="replace") as handle:
            head = handle.read(2048)
    except OSError:
        return False
    return "// stlport" in head


def compiler_environment(root, source=None):
    env = os.environ.copy()
    bin_dir = root / "Vc7" / "bin"
    ide_dir = root / "Common7" / "IDE"
    base_dir = root.parents[1]

    stlport = stlport_include_dir() if source_needs_stlport(source) else None

    if os.name == "nt":
        include = str(root / "Vc7" / "include")
        if stlport:
            include = str(stlport) + os.pathsep + include
        env["INCLUDE"] = include
        env["LIB"] = str(root / "Vc7" / "lib")
        # MSVC 7.1 runtime DLLs (msvcp71.dll) live in the toolchain root, not
        # bin/ or Common7/IDE/. Add base_dir so the compiler back-ends load.
        env["PATH"] = os.pathsep.join([str(bin_dir), str(ide_dir), str(base_dir), env.get("PATH", "")])
        return env

    include = wine_path(root / "Vc7" / "include")
    if stlport:
        include = wine_path(stlport) + ";" + include
    env["INCLUDE"] = include
    env["LIB"] = wine_path(root / "Vc7" / "lib")
    env["WINEPATH"] = ";".join(
        path
        for path in [wine_path(bin_dir), wine_path(ide_dir), wine_path(base_dir), env.get("WINEPATH", "")]
        if path
    )
    return env


def source_extra_flags(source):
    # A source that needs different compiler flags (e.g. /EHsc for functions the
    # original built with exception handling) declares them in its first lines:
    #   // cl: /EHsc
    # A UTF-8 BOM lands in front of the very first line, so `// cl:` on line 1
    # stops matching and the file silently compiles with the base flags instead.
    # That is invisible in the output -- the build just quietly ignores the
    # directive -- and it costs whole sessions to spot, so strip it here rather
    # than relying on every editor to write BOM-free files. Windows PowerShell's
    # `Set-Content -Encoding UTF8` writes one by default.
    if zh_reference_source(source) is not None:
        try:
            resolved(source).relative_to(GENERALS_REFERENCE_ROOT)
        except ValueError:
            return _ZH_FLAGS
        return _GENERALS_FLAGS
    with source.open("r", encoding="utf-8-sig", errors="replace") as handle:
        for line in handle.read(2048).splitlines():
            if line.startswith("// cl:"):
                # Use '-' style options so MSYS/Cygwin shells don't rewrite
                # leading '/' arguments as Windows paths.
                return [f.replace("/", "-", 1) if f.startswith("/") else f for f in line[len("// cl:") :].split()]
    return []


def compiler_command(source, output):
    root = vc71_root()
    source_arg = source.relative_to(ROOT).as_posix()
    output_arg = output.relative_to(ROOT).as_posix()

    command = []
    if os.name != "nt":
        wine = shutil.which("wine")
        if wine is None:
            raise SystemExit("wine not found. Install Wine to run MSVC 7.1 on this host.")
        command.append(wine)

    if source.suffix.lower() == LIB_SUFFIX:
        raise SystemExit(f"{source.relative_to(ROOT)}: a static library is not compiled — "
                         "its rows read an archive member (see extract_lib_members)")

    if source.suffix.lower() == ".asm":
        # Pure MASM for bodies C++ cannot emit (e.g. SEH array-ctor prologues).
        assembler = root / "Vc7" / "bin" / "ml.exe"
        command += [
            str(assembler),
            "-nologo",
            "-c",
            "-Cx",
            f"-Fo{output_arg}",
            source_arg,
        ]
        return command, compiler_environment(root, source)

    compiler = root / "Vc7" / "bin" / "cl.exe"
    command += [
        str(compiler),
        "-nologo",
        "-c",
        "-O2",
        "-GR-",
        "-EHsc-",
    ]
    command += source_extra_flags(source)
    command += [
        f"-Fo{output_arg}",
        source_arg,
    ]
    return command, compiler_environment(root, source)


def _host_path(text):
    # cl.exe under wine prints /showIncludes paths as Z:\home\... — map to host.
    path = text.strip().replace("\\", "/")
    if len(path) >= 2 and path[0] in "zZ" and path[1] == ":":
        path = path[2:] or "/"
    if not path.startswith("/"):
        path = str(ROOT / path)
    return os.path.normpath(path)


_CASEDIR_MEMO = {}


def _case_resolve(path):
    """Map a wine-reported path to the real on-disk path. Wine resolves
    case-insensitively and cl prints the REQUESTED casing (lowercased prefixes,
    'Basetype.h' for BaseType.h), so exact lookup fails on Linux. The repo bans
    case-colliding names, so per-component lowercase matching is unambiguous.
    Returns None when nothing matches."""
    if os.path.exists(path):
        return path
    current = "/"
    for part in path.split("/"):
        if not part:
            continue
        candidate = os.path.join(current, part)
        if os.path.exists(candidate):
            current = candidate
            continue
        listing = _CASEDIR_MEMO.get(current)
        if listing is None:
            try:
                listing = {name.lower(): name for name in os.listdir(current)}
            except OSError:
                return None
            _CASEDIR_MEMO[current] = listing
        real = listing.get(part.lower())
        if real is None:
            return None
        current = os.path.join(current, real)
    return current


_HASH_MEMO = {}


def _hash_file(path):
    try:
        stat = os.stat(path)
    except OSError:
        return None
    cached = _HASH_MEMO.get(path)
    if cached and cached[0] == (stat.st_mtime_ns, stat.st_size):
        return cached[1]
    digest = hashlib.md5(Path(path).read_bytes()).hexdigest()
    _HASH_MEMO[path] = ((stat.st_mtime_ns, stat.st_size), digest)
    return digest


def _deps_sidecar(output):
    return output.with_suffix(".deps.json")


def _portable(text):
    # Normalize ROOT-dependent path spellings (host and wine forms) so
    # fingerprints and sidecars stay valid across checkouts of the same tree —
    # a worktree seeded with the main clone's warm cache starts warm.
    if os.name != "nt":
        text = text.replace(wine_path(ROOT), "@ROOT@")
    return text.replace(str(ROOT), "@ROOT@")


def _cmd_fingerprint(command, env):
    payload = [[_portable(part) for part in command], _portable(env.get("INCLUDE", ""))]
    return hashlib.md5(json.dumps(payload).encode()).hexdigest()


def _write_deps_sidecar(source, output, fingerprint, stdout_text, is_cl):
    """Record the compile's exact inputs so compile_is_current can prove reuse.
    Uncacheable situations (unparseable include note, .asm with an include
    directive) fail LOUD and write no sidecar — that TU then always recompiles,
    visibly, instead of silently reusing a possibly-stale obj."""
    deps = {}
    problems = []
    if is_cl:
        for line in stdout_text.splitlines():
            if not line.startswith("Note: including file:"):
                continue
            host = _case_resolve(_host_path(line[len("Note: including file:"):]))
            if host is None:
                problems.append(line.strip()[:120])
                continue
            rel = os.path.relpath(host, ROOT)
            key = host if rel.startswith("..") else rel
            if key in deps:
                continue
            digest = _hash_file(host)
            if digest is None:
                problems.append(host)
            else:
                deps[key] = digest
        if not deps:
            # A TU with no #include genuinely has no notes — empty deps is
            # correct there. Notes missing DESPITE includes is the broken case.
            text = source.read_text(encoding="utf-8", errors="replace")
            if re.search(r"^\s*#\s*include\b", text, re.MULTILINE):
                problems.append("(cl produced no include notes despite #include lines)")
    else:
        head = source.read_text(encoding="utf-8", errors="replace")
        if re.search(r"^\s*include\s", head, re.IGNORECASE | re.MULTILINE):
            problems.append("(.asm uses an include directive; deps unknown)")
    if problems:
        print(f"deps-cache: not caching {source.relative_to(ROOT)} — {problems[:3]}",
              file=sys.stderr)
        _deps_sidecar(output).unlink(missing_ok=True)
        return
    payload = {"cmd": fingerprint, "source": _hash_file(str(source)), "deps": deps}
    tmp = _deps_sidecar(output).with_suffix(".tmp")
    tmp.write_text(json.dumps(payload))
    tmp.replace(_deps_sidecar(output))


def compile_is_current(source, output):
    """Sound obj reuse: True iff the obj exists and the source, compile command,
    and EVERY header recorded by /showIncludes at compile time are byte-identical.
    This is what makes skipping a TU in the full gate safe — the old behavior
    (recompile everything / trust BUILD_RECOMPILE_ONLY blindly) either burned
    ~17 min per gate or could re-verify a stale obj after a header edit."""
    sidecar = _deps_sidecar(output)
    if not output.exists() or not sidecar.exists():
        return False
    try:
        meta = json.loads(sidecar.read_text())
    except (OSError, ValueError):
        return False
    command, env = compiler_command(source, output)
    if meta.get("cmd") != _cmd_fingerprint(command, env):
        return False
    if meta.get("source") != _hash_file(str(source)):
        return False
    for dep, digest in meta.get("deps", {}).items():
        path = dep if os.path.isabs(dep) else str(ROOT / dep)
        if _hash_file(path) != digest:
            return False
    return True


def format_bytes(data):
    return " ".join(f"{byte:02x}" for byte in data)


def load_all_function_rows():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def load_function_rows():
    return [row for row in load_all_function_rows() if row["status"] == "matched"]


def is_scaffold_row(row):
    """True for a machine byte-dump row: it pins bytes and a boundary only.

    A gen-dump row claims no identity and no source, so every "is this address
    still open work?" question must answer yes over it. Tools that treat the
    ledger's address set as "done" go blind across the whole dump pass
    otherwise -- reverse/reloc_names.csv is REGENERATED by the full gate, so a
    dump row swallowing an address silently deletes a recovered name.
    """
    return row.get("notes", "").lstrip().startswith("gen-dump")


def load_claim_rows(*, counting_dumps, matched_only):
    """Ledger rows for a claim question; `counting_dumps` says WHICH question.

    Two questions get conflated, and the conflation is a bug that has landed
    four separate times. "Is this ground spoken for?" is an over-claim guard and
    a dump does count: counting_dumps=True. "Do we have source for this?" is a
    work finder and a dump does not: counting_dumps=False, which is
    is_scaffold_row's rule and the only correct one. Answering by source path
    instead hides the 349 gen-dump rows that live outside Code/gen_asm/.

    matched_only mirrors check_csv's overlap rule: an unmatched row is a
    hypothesis about an address, not proof the ground is spoken for.

    Neither argument is defaulted, and both are keyword-only, because a default
    is exactly how the wrong answer reached tool number four in silence.
    """
    rows = load_all_function_rows()
    if matched_only:
        rows = [row for row in rows if row["status"] == "matched"]
    if not counting_dumps:
        rows = [row for row in rows if not is_scaffold_row(row)]
    return rows


def follow_thunk(data, sections, rva, low, high):
    """The body an incremental-link thunk stands for, or rva when it is not one.

    The .text bound is what tells a thunk from a coincidence. Any byte can be
    0xE9 -- 0xA5E88E is the tail of a `mov` immediate inside a d3dx9 body -- and
    reading the four bytes after one as a displacement then yields an arbitrary
    address. Unbounded, that address is not merely wrong but unmappable: it
    reached new_starts.py's boundary scan as RVA -0x2AD9506D and crashed it.
    """
    offset = rva_to_file_offset(sections, rva)
    if data[offset] != 0xE9:
        return rva
    body = rva + 5 + struct.unpack_from("<i", data, offset + 1)[0]
    return body if low <= body < high else rva


def build_call_thunks():
    # Intra-module calls don't target a function's body directly -- they go through
    # the incremental-link thunk table, a block of 5-byte `jmp body` entries near the
    # start of .text. Map each body to its (lowest-addressed = ILT) thunk so that a
    # call to a matched function resolves to the address the original code called.
    data = EXE.read_bytes()
    text = next(section for section in pe_sections(data) if section["name"] == ".text")
    lo, size, raw = text["rva"], text["size"], text["raw_pointer"]
    body_to_thunks = {}
    pos, end = raw, raw + size - 5
    while True:
        pos = data.find(b"\xe9", pos, end)
        if pos == -1:
            break
        thunk_rva = (pos - raw) + lo
        target = thunk_rva + 5 + struct.unpack_from("<i", data, pos + 1)[0]
        if lo <= target < lo + size:
            # incremental linking creates one thunk block per re-link; a body can
            # have several thunks and different call sites use different ones
            body_to_thunks.setdefault(target, []).append(thunk_rva)
        pos += 1
    return body_to_thunks


def load_symbol_map():
    # Candidate addresses for resolving relative calls (REL32), most-likely first.
    # Incremental linking makes the callee encoding site-specific: objs linked
    # earlier call a matched function through its incremental-link thunk, objs
    # re-linked in place call the body directly. Both are legitimate, so a matched
    # function maps to [thunk, body] and the comparison picks whichever the target
    # actually used; anything else still fails the byte comparison loudly.
    # reverse/symbols.csv holds callees we do not own source for yet (CRT helpers
    # like __ftol2) at their exact call-target address, plus specific incremental-
    # link thunks build_call_thunks does not auto-discover. It is ADDITIVE: each
    # pinned address becomes one more candidate, so a matched name and a hand-pinned
    # thunk for the same name coexist and each call site picks whichever it encodes.
    thunks = build_call_thunks()
    symbol_map = {}
    for row in load_all_function_rows():
        body = int(row["target_rva"], 16)
        symbol_map[row["name"]] = thunks.get(body, []) + [body]
    if SYMBOLS.exists():
        # Membership sets mirroring the candidate lists, built only for the names
        # symbols.csv actually pins: `candidate not in candidates` is a linear
        # scan of a list that reaches 9,155 entries, and cost 2.72s of this
        # function's 3.09s. Building all 160k up front would just move the cost.
        # The lists stay lists, in append order — the resolver seeds from
        # candidates[0], stops at the first displacement that reproduces retail,
        # and reports the last one on failure.
        members = {}
        with SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                address = int(row["address"], 16)
                name = row["name"]
                candidates = symbol_map.setdefault(name, [])
                seen = members.get(name)
                if seen is None:
                    seen = members[name] = set(candidates)
                # a pinned body gets its incremental-link thunks too, same as a
                # ledger row: call sites encode the thunk, not the body
                for candidate in thunks.get(address, []) + [address]:
                    if candidate not in seen:
                        seen.add(candidate)
                        candidates.append(candidate)
    return symbol_map


# Sweep environment include dirs (header-only). Added on a *retry* when a source
# fails to open an include that only exists under the GeneralsMD/reference tree
# (e.g. the sweep-shim windows.h, or NetworkDefs.h pulled in by it). Off the
# default path so they never change codegen for the 10k+ already-matched sources.
_SWEEP_INCLUDE_DIRS = [
    ROOT / "reference" / "shims" / "sweep",
    ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code",
    ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code" / "Include",
]


def compile_source(source, output):
    output.parent.mkdir(parents=True, exist_ok=True)
    command, env = compiler_command(source, output)
    is_cl = source.suffix.lower() != ".asm"
    # Fingerprint the BASE command: the sweep-include retry below is a
    # deterministic function of these same inputs, so cache validity holds.
    fingerprint = _cmd_fingerprint(command, env)
    for attempt in range(3):
        result = subprocess.run(
            command + (["-showIncludes"] if is_cl else []),
            cwd=ROOT,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
        )
        if result.returncode == 0:
            _write_deps_sidecar(source, output, fingerprint, result.stdout, is_cl)
            return
        # Retry once with the sweep include dirs on the path (header resolution
        # only — never affects codegen of already-matched sources).
        if attempt == 0 and any(d.exists() for d in _SWEEP_INCLUDE_DIRS):
            missing = any("Cannot open include file" in l for l in result.stdout.splitlines())
            if missing:
                env = dict(env)
                extra = ";".join(wine_path(d) for d in _SWEEP_INCLUDE_DIRS if d.exists())
                env["INCLUDE"] = env["INCLUDE"] + ";" + extra
                command = list(command) + [f"-I{wine_path(d)}" for d in _SWEEP_INCLUDE_DIRS if d.exists()]
                continue
        transient = (not result.stdout.strip()
                     or "Application could not be started" in result.stdout
                     or "ShellExecuteEx failed" in result.stdout)
        if not transient or attempt == 2:
            print(f"compile failed: {source.relative_to(ROOT)}", file=sys.stderr)
            print("\n".join(l for l in result.stdout.splitlines()
                            if not l.startswith("Note: including file:")))
            raise SystemExit(result.returncode)
        print(f"retrying transient Wine launch failure for "
              f"{source.relative_to(ROOT)} ({attempt + 2}/3)", file=sys.stderr)


def is_funclet_row(row, object_symbol):
    """True for a gen-funclet row pinned to a compiler-local $L label."""
    return bool("gen-funclet" in (row.get("notes") or "")
                and re.fullmatch(r"\$L\d+", object_symbol))


def holds_funclet(body, relocs, target):
    """True if `body` starts with this row's funclet.

    Pre-link, every relocation site holds an addend rather than the address the
    linker wrote, so those bytes are masked out of both sides -- the same
    comparison compile_function makes, one step earlier and without the pins.
    """
    size = len(target)
    if len(body) < size:
        return False
    left, right = bytearray(body[:size]), bytearray(target)
    masked = set()
    for offset, _rtype, _sym in relocs:
        if offset + 4 <= size:
            left[offset:offset + 4] = right[offset:offset + 4] = b"\0\0\0\0"
            masked.update(range(offset, offset + 4))
    # A body whose every byte is a relocation site compares equal to ANY target
    # of its length, because nothing of it is left to compare. That is not a
    # match, it is an absence of evidence, and counting it is how a DATA table
    # ends up tying with a real funclet: AIPlayer.cpp's $L86009 is four label
    # pointers ($L78697..$L78700) covering all eight bytes, and it tied with
    # $L85915, which decodes to retail's own `lea ecx,[ebp-0x1c]; jmp <dtor>`.
    # Requiring one surviving byte separates them without choosing between them.
    if len(masked) >= size:
        return False
    return left == right


def funclet_scan(path, row, target):
    """Every $L in the parent's group, with what the comparison actually saw.

    Returns [(label, bodylen, surviving, held)], where `surviving` counts the
    bytes NOT covered by a relocation -- the evidence the comparison had to work
    with -- and `held` is holds_funclet's verdict. funclet_candidates is this
    filtered to the ones that held; the rest exists so a refusal can SHOW its
    reasoning instead of dying with a bare label. `surviving=0` beside
    `held=True` is the whole diagnosis of a body that matches on nothing.
    """
    parent = re.search(r"(?:^|;)parent=([^;]+)", row.get("notes", ""))
    if not parent:
        return []
    stat = path.stat()
    _data, _sections, symbols = _object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    handler = f"__ehhandler${parent.group(1)}"
    group = {s["section"] for s in symbols
             if s["name"] in (handler, parent.group(1)) and s["section"] > 0}
    if not group:
        return []
    size = len(target)
    seen = []
    for symbol in symbols:
        if symbol["section"] not in group or not re.fullmatch(r"\$L\d+", symbol["name"]):
            continue
        try:
            body, relocs = read_object_symbol_bytes(path, symbol["name"], size)
        except ValueError:
            continue
        masked = {i for offset, _rtype, _sym in relocs if offset + 4 <= size
                  for i in range(offset, offset + 4)}
        seen.append((symbol["name"], len(body), size - len(masked),
                     holds_funclet(body, relocs, target)))
    return seen


def funclet_refusal(row, object_symbol, scan, size, reason):
    """A refusal that shows its work: every candidate and what was compared."""
    lines = [f"{row['name']} ({row['source']}): {object_symbol} {reason}."]
    if scan:
        for name, bodylen, surviving, held in scan:
            lines.append(f"    {name:<12} bodylen={bodylen:>4}  "
                         f"surviving={surviving:>3}/{size}  masked-equal={held}")
    else:
        lines.append("    no $L bodies in the parent's group at all")
    return "\n".join(lines)


def funclet_candidates(path, row, target):
    """Every $L body in the claimed parent's group that IS this row's funclet.

    An SEH funclet has no name of its own, so those rows pin it to the
    compiler-local label its parent's COMDAT happened to receive. Those numbers
    are per-compilation ordinals: they shift whenever ANY unrelated edit to the
    TU changes how many labels precede them, and the pin then names a DIFFERENT
    body -- which is why nothing may trust one it has not just checked. When
    this was written 184 of the ledger's 20,045 funclet pins had already been
    renumbered off their body.

    Identity comes from evidence instead: inside the section that also holds
    __ehhandler$<parent> -- the parent's own funclet group -- the $L symbols
    whose bytes equal retail at this row's address. The caller decides, and only
    a unique answer may be used; a group of look-alikes has to fail loudly.
    """
    return [name for name, _bodylen, _surviving, held
            in funclet_scan(path, row, target) if held]


def read_funclet(row, object_symbol, output, target):
    """The bytes of a gen-funclet row's body, and a note when the pin was stale.

    Returns (bytes, relocs, note). The $L pin is a hint that has to earn its
    keep: the moment it does not hold this funclet, the body is re-identified
    from the parent's group (see funclet_candidates) or the row goes red with
    what it actually compiled. Nothing is ever picked from a field of two.
    """
    try:
        compiled, relocs = read_object_symbol_bytes(output, object_symbol, len(target))
    except ValueError as missing:
        compiled, relocs, gone = None, None, missing
    else:
        if holds_funclet(compiled, relocs, target):
            return compiled, relocs, None
        gone = None

    scan = funclet_scan(output, row, target)
    hits = [name for name, _bodylen, _surviving, held in scan if held]
    if len(hits) > 1:
        raise SystemExit(funclet_refusal(
            row, object_symbol, scan, len(target),
            f"does not hold this funclet and {len(hits)} bodies in the parent's group "
            f"match it equally ({', '.join(hits)}). Byte evidence cannot tell them apart, "
            "so the gate will not pick one — the row needs a body it can name on its own"))
    if hits:
        compiled, relocs = read_object_symbol_bytes(output, hits[0], len(target))
        return compiled, relocs, (
            f"{object_symbol} was renumbered by an edit to this TU; the body is {hits[0]} "
            "in the object built now (stale ledger pin, not a byte mismatch)")
    if gone is not None:
        # Was a bare "symbol not found in object: $L<n>", which killed the gate
        # before it printed a single result line and named nothing but a
        # compiler-local label. The pin renumbered and nothing replaced it, so
        # the row has no anchor at all -- and uw_0045bea0 is the reason the
        # message asks the question it does: that row could not find a body
        # because it was two 4-byte accessors and twelve int3 of padding, not a
        # funclet. A row that cannot find its body may not deserve one.
        raise SystemExit(funclet_refusal(
            row, object_symbol, scan, len(target),
            "is not in the object, and nothing in the parent's group holds this funclet "
            "either. The pin renumbered and no body replaces it, so the row has no anchor "
            "-- check whether it deserves one before giving it a new pin"))
    return compiled, relocs, (
        f"{object_symbol} no longer holds this funclet and nothing in the parent's group "
        "does either, so this is the body that label names now")


def compile_function(row, symbol_map, output):
    target_rva = int(row["target_rva"], 16)
    target_size = int(row["target_size"])
    target = read_target_bytes(target_rva, target_size)
    object_symbol = ledger_object_symbol(row)
    note = None
    if is_funclet_row(row, object_symbol):
        compiled, relocs, note = read_funclet(row, object_symbol, output, target)
    else:
        compiled, relocs = read_object_symbol_bytes(output, object_symbol, target_size)

    # A lib member is pre-link code: every relocation site still holds an addend
    # rather than the address the linker wrote, and its callees are
    # library-internal symbols no ledger row gives an address for, so none of
    # them can be resolved the way a compiled TU's are. Mask them all instead
    # and compare only the bytes in between; `concrete` reports how many that
    # leaves, because a comparison over too few bytes is not evidence.
    #
    # A gen-alias row (the ICF-twin dup_ convention: same body claimed at a
    # second address under an alias name) needs the same masking, but only as a
    # FALLBACK, never as a mode. Its object code is the original claim's
    # compiled TU, so every relocation site's symbol is known -- but the
    # candidate list load_symbol_map builds for that symbol covers only the
    # original claim's address and ITS thunks, not a sibling ICF fold of the
    # callee that this second address's own thunk chain routes through. Which
    # fold the twin encodes is exactly the position-dependent fact a twin's
    # rel32 legitimately differs on, so strict resolution cannot see it.
    #
    # Masking gen-alias rows UNCONDITIONALLY is wrong, and measurably so: it
    # drags them under the MIN_LIB_CONCRETE floor, and the 4-to-7-byte alias
    # rows that make up most of the 9600 already in the ledger have fewer than
    # eight non-relocation bytes by construction. Doing that failed 528 of
    # GameAudio.cpp's 3279 rows, a file that gates 3278/3278 without it. So try
    # strict first and keep it when it proves the row; fall back to masking only
    # for a row strict cannot prove. An ordinary conversion never takes the
    # fallback, and keeps full strictness.
    lib_member = (ROOT / row["source"]).suffix.lower() == LIB_SUFFIX
    gen_alias = "gen-alias" in (row.get("notes") or "")

    def resolve(masked):
        resolved = bytearray(compiled[:target_size])
        unresolved = []
        covered = bytearray(target_size)
        for offset, rtype, sym_name in relocs:
            if offset >= target_size:
                continue  # reloc belongs to a later function sharing the COMDAT section
            if masked:
                width = min(RELOC_WIDTH.get(rtype, 4), target_size - offset)
                resolved[offset : offset + width] = target[offset : offset + width]
                covered[offset : offset + width] = b"\1" * width
            elif rtype == 0x0006:  # IMAGE_REL_I386_DIR32
                resolved[offset : offset + 4] = target[offset : offset + 4]
            elif rtype == 0x0014:  # IMAGE_REL_I386_REL32
                # `resolved` is a bytearray, so assigning four bytes at
                # target_size-1..-3 EXTENDS it instead of failing: the row compiles
                # longer than it claims, clobbers its own last bytes on the way, and
                # surfaces as two hex dumps of different lengths naming neither the
                # extent nor this site. A call displacement cannot end after the
                # function does, so what is wrong here is the boundary, not the
                # write -- clipping would only make a wrong boundary compare equal.
                if offset + 4 > target_size:
                    raise SystemExit(
                        f"{row['name']} ({row['source']}): REL32 site at offset {offset} "
                        f"(0x{offset:x}) for {sym_name} needs {offset + 4} bytes but the row "
                        f"claims target_size {target_size}. The row's extent is wrong: raise "
                        "it to the real end of the function. This displacement is part of "
                        "this body, not of whatever follows it.")
                if sym_name in symbol_map:
                    next_address = target_rva + offset + 4
                    candidates = symbol_map[sym_name]
                    displacement = struct.pack("<i", candidates[0] - next_address)
                    for target_address in candidates[1:]:
                        if target[offset : offset + 4] == displacement:
                            break
                        displacement = struct.pack("<i", target_address - next_address)
                    resolved[offset : offset + 4] = displacement
                else:
                    unresolved.append(sym_name)

        return resolved, unresolved, covered

    resolved, unresolved, covered = resolve(lib_member)
    masked = lib_member
    if gen_alias and not lib_member and bytes(resolved) != target:
        alt_resolved, alt_unresolved, alt_covered = resolve(True)
        if bytes(alt_resolved) == target:
            resolved, unresolved, covered = alt_resolved, alt_unresolved, alt_covered
            masked = True

    return {
        "name": row["name"],
        "target_rva": target_rva,
        "target": target,
        "bytes": bytes(resolved),
        "source": row["source"],
        "unresolved": unresolved,
        "relocs": relocs,
        "masked": masked,
        "concrete": target_size - sum(covered),
        "note": note,
    }


REL32 = 0x0014
GHIDRA_FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
# MSVC hashes the absolute source path into anonymous-namespace symbols, so the
# same function carries a different token in every clone. Naming a retail
# address after one would churn this file on each contributor's gate.
CLONE_LOCAL_RE = re.compile(r"\?A0x[0-9A-Fa-f]{8}")
# tools/gen_dump.py mints Gen_t_/Gen_dtor_ classes for the machine-generated
# funclet TUs, and tools/gen_uw.py mints the whole Gen_uw* family (Gen_uw_,
# Gen_uwm_, Gen_uwh<pad>_, Gen_uws<size>_, Gen_uwt_, Gen_uwp_, Gen_uw_new).
# Those names are this project's own bookkeeping, not identity recovered from
# retail, and they outnumber the recovered names roughly two to one. Published
# marked so the queue can tell a real class and signature from a placeholder
# that only looks like one. Every generator that mints a name has to be listed
# here: the Gen_uw* family was invisible to this pattern for one phase and 15 of
# its pins were published as recovered identity.
GEN_PLACEHOLDER_RE = re.compile(
    r"Gen_(?:t|dtorv?)_[0-9a-f]{8}|Gen_uw[a-z]*\d*_"
    # The conversion lanes also mint ADDRESS-DERIVED names whose whole point
    # is to DISCLAIM identity: Gen<RVA>, gen<RVA>, Gen_<rva>, Rva<RVA>Thing.
    # Without this arm 2061 such names were being written into
    # reverse/reloc_names.csv as identity=real -- the precise opposite of
    # what the naming convention asserts. Eight hex digits with no ninth
    # keeps it from matching an ordinary identifier that merely starts "Gen".
    r"|(?:Gen|gen|Rva|rva)_?[0-9A-Fa-f]{8}(?![0-9A-Fa-f])")
# tools/zh_sweep.py names a row ?dup_<rva>@@YAXXZ when the bytes are proven by a
# Zero Hour twin but the identity is not: the twin is one member of an ICF fold
# and the reference TU's COMDAT it compiled is recorded in object-symbol= only
# as the build directive it is. Such a row claims an address without naming it.
DUP_ALIAS_RE = re.compile(r"^\?dup_[0-9a-f]{8}@@YAXXZ$")


def harvest_reloc_names(patches):
    """Name retail functions from the call sites of rows proven byte-true.

    A byte-true row's compiled bytes ARE the retail bytes, so each REL32
    relocation sits exactly where retail encodes that call's displacement and
    the relocation carries the callee's mangled name. The callee is therefore
    decoded from the RETAIL bytes, gated on the byte in front of the
    displacement being the call opcode: asking compile_function's resolver
    instead would only ever return callees already listed in symbols.csv, which
    is no new identity at all.

    The decoded address is usually not the body. Intra-module calls go through
    an incremental-link thunk, so a lone `jmp` at the target is followed to the
    body it stands for.

    A ?dup_<rva> row does not contribute. Its bytes are retail's, but the
    relocation SYMBOLS are the Zero Hour TU's names for the Zero Hour functions
    an arbitrary fold member calls -- and where BFME folded a different set,
    that name is simply wrong here. Two landed twins of ZH's
    GadgetSliderSetDisabled*ThumbColor named 0x00479040 winSetDisabledColor,
    colliding with the ?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z that six
    BFME call sites had recovered, and select_reloc_names dropped the address
    rather than guess. A row that admits it is not an identity cannot lend its
    callee names to an identity harvest.

    Returns {body rva: {"names": set, "sources": set, "sites": int}}.
    """
    data, sections = exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    thunks = {}

    def follow(rva):
        if rva not in thunks:
            thunks[rva] = follow_thunk(data, sections, rva, low, high)
        return thunks[rva]

    named = {}
    for patch in patches:
        if DUP_ALIAS_RE.match(patch["name"]):
            continue
        target = patch["target"]
        for offset, rtype, symbol in patch["relocs"]:
            if rtype != REL32 or offset < 1 or offset + 4 > len(target):
                continue
            if target[offset - 1] != 0xE8:
                continue
            callee = (patch["target_rva"] + offset + 4
                      + struct.unpack_from("<i", target, offset)[0])
            if not low <= callee < high:
                continue
            entry = named.setdefault(follow(callee),
                                     {"names": set(), "sources": set(), "sites": 0})
            entry["names"].add(symbol)
            entry["sources"].add(patch["source"])
            entry["sites"] += 1
    return named


def select_reloc_names(named):
    """Keep only harvested names that identify one unclaimed anonymous function.

    Both filters are load-bearing. Identical-code folding gives one address
    several legitimate names, and a shared address that acquires two of them is
    a contradiction the arity gate cannot see, so an address named more than one
    way is dropped rather than guessed at. Addresses the ledger already claims,
    or that Ghidra already names, are not new identity.

    "Claims" means NAMES, not covers. A gen-dump row pins bytes under a
    synthetic name and a ?dup_<rva> row pins them under a Zero Hour twin whose
    identity it explicitly disclaims; both leave the address anonymous, and
    both would otherwise swallow the one piece of evidence that could name it
    -- the recovered ?findCommandSet@ControlBar@@... at 0x4A0340 survived only
    because a human went looking after the line vanished.
    """
    inventory = {}
    with GHIDRA_FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            inventory[int(row["rva"], 16)] = (int(row["size"]), row["name"])
    claimed = {int(row["target_rva"], 16) for row in load_all_function_rows()
               if not is_scaffold_row(row) and not DUP_ALIAS_RE.match(row["name"])}

    selected = []
    for rva, entry in sorted(named.items()):
        if len(entry["names"]) != 1:
            continue
        name = next(iter(entry["names"]))
        if CLONE_LOCAL_RE.search(name):
            continue
        known = inventory.get(rva)
        if known is None or not known[1].startswith("FUN_") or rva in claimed:
            continue
        selected.append({
            "name": name,
            "target_rva": f"0x{rva:08X}",
            "target_size": str(known[0]),
            "source": min(entry["sources"]),
            "notes": (f"reloc-derived;call-sites={entry['sites']};identity="
                      + ("generated" if GEN_PLACEHOLDER_RE.search(name)
                         else "real")),
        })
    return selected


def write_reloc_names(patches):
    """Regenerate reverse/reloc_names.csv from this gate's byte-true rows.

    Regenerated, never appended: it is derived output, and a row that stops
    being re-derivable must stop being published. There is deliberately no
    status column — what is byte-verified here is the naming evidence, not the
    named function's body, and no derived file gets to imply otherwise.
    """
    selected = select_reloc_names(harvest_reloc_names(patches))
    with RELOC_NAMES.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(
            handle, ["name", "target_rva", "target_size", "source", "notes"],
            lineterminator="\n")
        writer.writeheader()
        writer.writerows(selected)
    real = sum(1 for row in selected if row["notes"].endswith("identity=real"))
    print(f"Reloc names: {len(selected)} anonymous function(s) named from "
          f"byte-true call sites ({real} recovered identity, "
          f"{len(selected) - real} generated placeholder) -> "
          f"{RELOC_NAMES.relative_to(ROOT)}")
    return selected


def verify_functions(only=None):
    rows = load_function_rows()
    if only:
        rows = [row for row in rows if any(sel in row["source"] or sel in row["name"] for sel in only)]
        if not rows:
            raise SystemExit("no functions match: " + ", ".join(only))
    total = len(rows)
    symbol_map = load_symbol_map()

    sources = []
    seen = set()
    for row in rows:
        source = ROOT / row["source"]
        if source not in seen:
            seen.add(source)
            sources.append(source)
    missing = [s for s in sources if not s.exists()]
    if missing:
        raise SystemExit("functions.csv references missing source file(s): "
                         + ", ".join(str(m) for m in missing)
                         + " - a commit added rows without adding the file")
    # Split by kind BEFORE anything reaches the compiler: a .lib is a build
    # input to read, not a translation unit, and cl.exe would choke on it.
    extract_lib_members(rows)
    sources = [s for s in sources if s.suffix.lower() != LIB_SUFFIX]
    source_outputs = {s: obj_path(s) for s in sources}
    if len(set(source_outputs.values())) != len(source_outputs):
        raise SystemExit("obj stem collision between sources; refusing parallel compile")
    # wine cl.exe instances are independent processes; compile is the wall-clock
    # hog (byte comparison below is pure reads), so parallelize only this phase
    # Incremental mode (BUILD_RECOMPILE_ONLY="a.cpp;b.cpp"): reuse existing .obj
    # files for every source NOT listed - valid only when the caller proves the
    # unlisted sources and all headers are identical to the previous verified
    # build in this same tree (the fleet verifier does, via git diff). A missing
    # .obj is compiled regardless; never silently reused when absent.
    recompile_only = os.environ.get("BUILD_RECOMPILE_ONLY")
    if recompile_only is not None:
        wanted = {w for w in recompile_only.split(";") if w}
        to_compile = [s for s in sources
                      if str(s.relative_to(ROOT)) in wanted or not source_outputs[s].exists()]
        print(f"Incremental compile: {len(to_compile)} of {len(sources)} source(s)")
    else:
        # Sound dep-cache: skip every TU whose obj provably matches its current
        # source + flags + recorded headers (see compile_is_current). A TU with
        # no sidecar (first gate after this change, or flagged uncacheable)
        # recompiles. This is what turns a header-edit gate from ~17 min of
        # recompile-the-world into seconds-per-actual-includer.
        to_compile = [s for s in sources if not compile_is_current(s, source_outputs[s])]
        cached = len(sources) - len(to_compile)
        if cached:
            print(f"Compile: {len(to_compile)} of {len(sources)} TU(s) "
                  f"(deps-cache: {cached} current)")
    # BUILD_POOL controls compile parallelism. Default 1: a single build.py call
    # (a worker verifying its own 1-2 files, or the fleet's per-task fast verify)
    # must NOT fork an 8-way wine pool - dozens of concurrent callers would then
    # oversubscribe the cores into a stall. Only the full-suite periodic audit,
    # which runs alone, sets BUILD_POOL=8 to compile all 260+ TUs in parallel.
    pool_size = max(1, min(int(os.environ.get("BUILD_POOL", "1")), os.cpu_count() or 1))
    # Host-wide wine/cl mutex: concurrent FULL builds thrash each other (and wine
    # cl fails at high concurrency), so a full build (>8 TUs) takes the lock
    # EXCLUSIVELY and they serialize against each other. Small per-file verifies
    # take NO lock: they must never wait behind a sibling clone's full gate — that
    # stall serialized every worker to a crawl. A full build compiles one cl.exe
    # at a time here (BUILD_POOL=1), so unlocked per-file verifies running
    # alongside it stay within the core count.
    lock_dir = Path.home() / ".cache"
    lock_dir.mkdir(parents=True, exist_ok=True)
    exclusive = len(to_compile) > 8
    lock_file = None
    if exclusive:
        lock_file = (lock_dir / "open-bfme-build.lock").open("a")
        lock(lock_file, exclusive=True,
             wait_notice="waiting for build lock (another clone is running a full build)...")
    try:
        if pool_size == 1 or len(to_compile) <= 1:
            for s in to_compile:
                compile_source(s, source_outputs[s])
        else:
            with concurrent.futures.ThreadPoolExecutor(pool_size) as pool:
                futures = {pool.submit(compile_source, s, source_outputs[s]): s for s in to_compile}
                for future in concurrent.futures.as_completed(futures):
                    future.result()
    finally:
        if lock_file is not None:
            unlock(lock_file)
            lock_file.close()

    failures = 0
    patches = []
    renumbered = []
    for row in rows:
        patch = compile_function(row, symbol_map, row_object(row))
        target = patch["target"]
        compiled = patch["bytes"]

        thin = patch["masked"] and patch["concrete"] < MIN_LIB_CONCRETE
        if compiled == target and not thin:
            patches.append(patch)
            if patch["note"]:
                renumbered.append(f"{row['name']} ({row['source']}): {patch['note']}")
            continue

        failures += 1
        print(f"  FAIL {row['name']} ({row['source']})")
        if patch["note"]:
            print(f"    {patch['note']}")
        if thin and compiled == target:
            print(f"    only {patch['concrete']} of {len(target)} byte(s) lie outside a "
                  "relocation site; a masked comparison this thin proves nothing")
            continue
        if patch["unresolved"]:
            calls = ", ".join(sorted(set(patch["unresolved"])))
            print(f"    unresolved call(s): {calls} (add to reverse/symbols.csv)")
        print(f"    target:   {format_bytes(target)}")
        print(f"    compiled: {format_bytes(compiled)}")

    if renumbered:
        # Green, but on a pin the ledger got wrong: say so every time, or the
        # only record of a rotting pin is the day it lands on a look-alike.
        print(f"Funclet pins: {len(renumbered)} row(s) verified past a renumbered $L label")
        for line in renumbered[:5]:
            print(f"    {line}")

    if failures:
        print(f"Functions: FAIL {failures}/{total}")
        print(f"{failures} function(s) failed byte comparison")
        raise SystemExit(1)

    source_count = len({row["source"] for row in rows})
    if total == 1:
        row = rows[0]
        print(f"Functions: OK 1/1 matched")
        print(f"  {row['name']} ({row['source']})")
    else:
        print(f"Functions: OK {total}/{total} matched across {source_count} source file(s)")

    # Only a full gate may rewrite the derived file: a scoped run proves a
    # handful of rows and would silently publish that handful as the whole set.
    if not only:
        write_reloc_names(patches)

    return patches


def patch_exe(patches, output):
    output.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(EXE, output)

    data = bytearray(output.read_bytes())
    sections = pe_sections(data)
    ranges = []
    for patch in sorted(patches, key=lambda entry: entry["target_rva"]):
        offset = rva_to_file_offset(sections, patch["target_rva"])
        end = offset + len(patch["bytes"])
        if data[offset:end] != patch["target"]:
            raise SystemExit(f"{patch['name']}: target bytes changed before patching")
        if ranges and offset < ranges[-1][1]:
            # ICF alias group: a previous patch wrote byte-identical code to this
            # exact range (folded COMDATs share one address). Re-applying is a no-op.
            if offset == ranges[-1][0] and end == ranges[-1][1] and patch["bytes"] == data[offset:end]:
                continue
            raise SystemExit(f"{patch['name']}: patch overlaps previous patch")
        ranges.append((offset, end))
        data[offset:end] = patch["bytes"]

    output.write_bytes(data)
    return output


def verify_noop_patch(patches):
    patch_exe(patches, NOOP_EXE)

    original_sha256 = hash_file(EXE, "sha256")
    patched_sha256 = hash_file(NOOP_EXE, "sha256")

    if patched_sha256 != original_sha256:
        raise SystemExit(
            f"No-op patch: FAIL {NOOP_EXE.relative_to(ROOT)} sha256 {patched_sha256} != {original_sha256}"
        )
    print(f"No-op patch: OK {NOOP_EXE.relative_to(ROOT)}")


def verify_string_refs(rows):
    """Independently VERIFY (not mask) every DIR32 relocation that points at a string literal:
    read the address the compiled code references, and confirm the string AT that address in the
    binary byte-equals the compiled literal. Self-verifying (no pins) — catches source/binary string
    discrepancies that compile_function's DIR32 masking otherwise hides (e.g. "%S" vs "%ls",
    "ParticleSystemInfo" vs "FXParticleSystemInfo"). Reuses the objs already built by verify_functions."""
    exe = EXE.read_bytes()
    pe = pe_sections(exe)
    mismatches = []
    checked = 0
    empty_ok = 0
    for row in rows:
        obj = require_row_object(row)
        target_rva = int(row["target_rva"], 16)
        target_size = int(row["target_size"])
        target = read_target_bytes(target_rva, target_size)
        try:
            fn_bytes, relocs = read_object_symbol_bytes(
                obj, ledger_object_symbol(row), target_size)
        except ValueError:
            continue
        for offset, rtype, sym in relocs:
            if rtype != 0x0006 or offset + 4 > target_size or not sym.startswith("??_C@"):
                continue
            # No silent skip: a string reference we cannot verify is a hole in the guarantee, so a
            # genuine extraction/RVA failure is surfaced as a mismatch (fail loudly), not swallowed.
            try:
                cs, _ = read_object_symbol_bytes(obj, sym)
                str_rva = struct.unpack_from("<I", target, offset)[0] - 0x400000
                file_off = rva_to_file_offset(pe, str_rva)
            except (ValueError, struct.error) as exc:
                mismatches.append((row["name"], f"<unverifiable {sym[:24]}: {exc}>".encode(), b""))
                continue
            # DIR32 relocs carry an addend (pre-link value at the site): pooled string reuse
            # references symbol+addend (e.g. "DBGHELP.DLL"+4 == "ELP.DLL"), so the referenced
            # literal is content[addend:], and the binary holds it at str_rva == sym_rva+addend.
            addend = struct.unpack_from("<i", fn_bytes, offset)[0] if offset + 4 <= len(fn_bytes) else 0
            content = cs.rstrip(b"\x00")
            if 0 < addend <= len(content):
                content = content[addend:]
            if not content:
                # empty string literal "": no content to match, but confirm the referenced location
                # really is an empty string (a null byte) and not a stale/wrong pointer.
                if exe[file_off] != 0:
                    mismatches.append((row["name"], b'"" (empty)', exe[file_off : file_off + 4]))
                else:
                    empty_ok += 1
                continue
            if exe[file_off : file_off + len(content)] != content:
                mismatches.append((row["name"], content, exe[file_off : file_off + len(content)]))
            else:
                checked += 1
    if mismatches:
        print(f"String-ref verify: FAIL {len(mismatches)} mismatch(es) (source string != binary string)")
        for name, src_s, bin_s in mismatches[:12]:
            print(f"    {name}: source={src_s!r} binary={bin_s!r}")
        raise SystemExit(1)
    print(f"String-ref verify: OK ({checked} literals + {empty_ok} empty-string refs verified, 0 unverified/skipped)")


def verify_dir32_consistency(rows):
    """Regression gate for the non-string DIR32s (globals/vtables/func-addrs) build.py masks. A symbol
    has one address, so every reference must resolve to the same base once the addend is subtracted
    (base = binary_addr - compiled_addend). A symbol with >1 base is a candidate hidden discrepancy.
    Whitelist (reverse/dir32_consistency_whitelist.txt) holds the CURRENT known-legitimate cases
    (double-linked TUs CRC32_Table/_COLLISION_EPSILON; the investigated FX ctor/dtor vtable artifacts).
    Hand-written only: an absent whitelist is a hard failure listing the candidates, never an
    auto-written free pass, and any NEW inconsistency FAILS."""
    from collections import defaultdict
    whitelist_path = ROOT / "reverse" / "dir32_consistency_whitelist.txt"
    sym2base = defaultdict(set)
    for row in rows:
        obj = require_row_object(row)
        trva, tsz = int(row["target_rva"], 16), int(row["target_size"])
        target = read_target_bytes(trva, tsz)
        try:
            body, relocs = read_object_symbol_bytes(
                obj, ledger_object_symbol(row), tsz)
        except ValueError:
            continue
        for off, rtype, sym in relocs:
            if rtype != 0x0006 or off + 4 > tsz or off + 4 > len(body) or sym.startswith("??_C@"):
                continue
            # Compiler-local labels ($L1234 funclets, $T294 funcinfo, $SG strings)
            # are TU-scoped: object-symbol= rows alias ONE anchor TU's label onto
            # thousands of retail instances by design, so "one symbol, one
            # address" only holds for external symbols. Locals add no detection
            # power for double-linked TUs (those always expose externals too).
            if re.fullmatch(r"\$[A-Za-z]+\d+", sym):
                continue
            # __ehhandler$<mangled> is the same case one step out: the compiler
            # emits one per TU alongside the COMDAT it guards, and retail does
            # not fold COMDATs, so a template instantiation claimed at N retail
            # addresses legitimately resolves its handler to N stub addresses.
            if sym.startswith("__ehhandler$"):
                continue
            final = struct.unpack_from("<I", target, off)[0]
            addend = struct.unpack_from("<I", body, off)[0]
            sym2base[sym].add((final - addend) & 0xFFFFFFFF)
    inconsistent = sorted(s for s, b in sym2base.items() if len(b) > 1)
    if not whitelist_path.exists():
        # NOT self-seeding. Auto-writing this file is how 18 entries got in
        # without a human ever reading them, 8 of them hiding placements this
        # very check had proved wrong (dropped in 25801f359). A missing
        # whitelist is a missing review, and a missing review is a failure.
        raise SystemExit(
            f"DIR32 consistency: {whitelist_path.relative_to(ROOT)} is missing. This check does NOT "
            f"seed itself — an auto-written whitelist is an unreviewed free pass. The {len(inconsistent)} "
            "currently inconsistent symbol(s) are listed below; READ them, confirm each is a legitimate "
            "doubly-linked TU or investigated vtable artifact, and commit the file by hand:\n"
            + "".join("    " + s + "\n" for s in inconsistent))
    whitelist = {l.strip() for l in whitelist_path.read_text().splitlines() if l.strip() and not l.startswith("#")}
    new = [s for s in inconsistent if s not in whitelist]
    if new:
        print(f"DIR32 consistency: FAIL {len(new)} NEW inconsistent symbol(s) (candidate hidden bug — same symbol, multiple addresses)")
        for s in new[:12]:
            print(f"    {s}: bases {[hex(b) for b in sorted(sym2base[s])]}")
        raise SystemExit(1)
    print(f"DIR32 consistency: OK ({len(sym2base)} symbols; {len(inconsistent)} whitelisted, 0 new)")


UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(?:present-unmatched|absent-from-retail)\b", re.MULTILINE
)



def verify_source_claims(only=None):
    """Progress is matched rows, nothing else: every .cpp under Code/ must own at
    least one byte-verified matched row, and no marker may contradict the ledger
    (a symbol both matched and marked unmatched is a stale annotation lying about
    state). There is deliberately NO exception list: a source file nothing has
    ever byte-verified is a reconstruction, not a port, and must not live here.
    Removing that hatch is why game_engine_init.cpp and five others were deleted.

    With `only`, checks just the sources those selectors name. The delta path runs
    it that way so a zero-row source or a stale marker fails for whoever adds it.
    Left to the full gate alone, it lands on delta verification and then blocks
    every header or shim commit tree-wide until someone else cleans it up."""
    matched_by_source = {}
    matched_sources = {}
    for row in load_function_rows():
        matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
        matched_sources.setdefault(row["name"], set()).add(row["source"])

    problems = []
    sources = sorted((ROOT / "Code").rglob("*.cpp"))
    if only:
        sources = [p for p in sources
                   if any(sel in p.relative_to(ROOT).as_posix() for sel in only)]
    for path in sources:
        rel = path.relative_to(ROOT).as_posix()
        text = path.read_text(encoding="utf-8", errors="replace")
        for label in UNMATCHED_MARKER_RE.findall(text):
            # a marker on a symbol matched from ANOTHER file is correct bookkeeping
            # (e.g. the ZH copy of a function landed via an asm-whale scaffold);
            # matched from THIS file, the marker is a stale lie about its state
            if rel in matched_sources.get(label, ()):
                # Say what this actually knows. `matched_sources` is the LEDGER's
                # status column, not a byte comparison -- and merge_cluster
                # --apply sets that status without building. Wording this as
                # "byte-verified" once had an agent believe a repointed row was
                # proven and nearly write an overturned verdict into a source
                # comment; the build is what verifies, and it disagreed.
                problems.append(
                    f"{rel}: the LEDGER records {label} as matched from this file "
                    f"(status only -- not a byte comparison) while the file still "
                    f"carries an unmatched marker. Either the marker is a stale "
                    f"annotation, or the row was repointed here and has not been "
                    f"byte-verified yet; ./build.sh on this file settles which."
                )
        if matched_by_source.get(rel, 0) == 0:
            problems.append(
                f"{rel}: ZERO matched rows — source presence is not progress. There is "
                f"no exception list; byte-match at least one function or delete the file."
            )

    if problems:
        print(f"Source claims: FAIL ({len(problems)} problem(s))")
        for problem in problems[:20]:
            print(f"    {problem}")
        raise SystemExit(1)
    scope = "scoped" if only else "all"
    print(f"Source claims: OK ({len(sources)} sources, {scope} byte-verified)")


def main(only=None):
    # Sources include some sweep headers under two case spellings; only the
    # canonical one is committed (case-only-colliding paths break Windows/macOS
    # checkout). Regenerate the alternate spelling here before any compile.
    ensure_case_shims()
    if only:
        # Fast path: compile and byte-compare only the matching sources/functions
        # (a few seconds), skipping the baseline hash and no-op patch. Use this to
        # iterate; run with no arguments for the full check before committing.
        #
        # Claims first: verify_functions exits with "no functions match" when the
        # selector names a source that owns no rows, which is exactly the case the
        # zero-row check exists to catch, so it has to run before that exit.
        verify_source_claims(only)
        verify_functions(only)
        # String-ref verify scoped to the same rows: function bytes alone cannot
        # tell identical-twin stubs apart (their string pointer is a masked
        # DIR32) — three wrong-twin claims survived per-file verification and
        # reached master before the full gate caught them.
        rows = [row for row in load_function_rows()
                if any(sel in row["source"] or sel in row["name"] for sel in only)]
        verify_string_refs(rows)
        return
    print("Full verification")
    # Identity, not bytes: verify_functions proves each row's bytes, and a
    # symbols.csv pin that names the WRONG body still reproduces them (that is
    # how the ControlBar and GameWindow misidentifications passed a green gate).
    # 3.4s on a >10min gate, reading only the retail image and the ledgers, so
    # it needs no cached artifact and no compile output -- imported here rather
    # than at module scope because pin_consistency imports this module.
    import pin_consistency

    # EVERY check reports, then the gate exits ONCE. Exiting at the first
    # failure makes each late check hostage to every earlier one: a live DIR32
    # red sat four statements ahead of the pin guard, so the guard built to
    # catch what a green gate cannot had itself never run on master -- and a
    # report of "only the pre-existing DIR32 red" reads identically whether the
    # later checks passed or never executed. Ordering is not a safety property;
    # running is.
    failed = []

    def run(label, check):
        """Run one check, recording rather than propagating its SystemExit.

        Only SystemExit is caught, and only a failing code: a check that dies
        any other way is a bug in the gate itself and must still crash loudly.
        """
        try:
            return check()
        except SystemExit as exc:
            if not exc.code:
                raise
            # A check that raises SystemExit("<explanation>") carries its whole
            # diagnosis in exc.code. Dropping it reduced a named, actionable
            # error -- an ambiguous funclet heal naming its TU and both
            # candidate bodies -- to "verify_functions did not produce a patch
            # set", which reads as a crash. That cost three full-gate runs and
            # two wrong diagnoses before anyone called the check directly to
            # recover the text. An int is a bare exit status and says nothing.
            if not isinstance(exc.code, int):
                print(f"{label}: {exc.code}")
            failed.append(label)
            return None

    run("baseline", verify_baseline)
    patches = run("functions", verify_functions)
    rows = load_function_rows()
    run("string-refs", lambda: verify_string_refs(rows))
    run("dir32 consistency", lambda: verify_dir32_consistency(rows))
    run("pin consistency", pin_consistency.verify)
    run("source claims", verify_source_claims)
    if patches is None:
        # The no-op patch needs the compiled patch set, so a failed
        # verify_functions leaves it unrunnable. Say that out loud and stay red
        # rather than skipping it into a green summary.
        print("No-op patch: FAIL not run — verify_functions did not produce a patch set")
        failed.append("no-op patch (unrunnable)")
    else:
        run("no-op patch", lambda: verify_noop_patch(patches))

    if failed:
        print(f"\nFULL GATE: FAIL — {len(failed)} red: " + ", ".join(failed))
        raise SystemExit(1)
    print("\nFULL GATE: OK — every check green")


if __name__ == "__main__":
    main(sys.argv[1:])
