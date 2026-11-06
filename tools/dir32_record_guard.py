#!/usr/bin/env python3
"""dir32_addresses.csv is evidence the gate reads, so a commit may not write it freely.

verify_dir32_addresses trusts a recorded (name, va) pair: every reference must
give the name that address. A hand-added line was therefore a free pass for a
new decorated name at any address (the red team's "wrong global" exploit), and
a hand-edited address moved every reference's expectation at once.

  * An address already recorded for a name may not change. A wrong record is
    retired (below), never rewritten in a commit that also moves the references.
  * A deleted line must be retired by tools/dir32_record.py, which writes a
    `Dir32-Retire: OLD 0x<VA> for NEW` trailer. Only commit-msg sees the
    message, so .githooks/commit-msg runs `--commit-msg FILE` with this file AS
    OF HEAD (an edit cannot approve itself) and re-checks, against the staged
    tree, the owner's two conditions (ruling 2026-10-09): NEW is ledger-owned
    at OLD's address (a data_rows.csv row at that VA, a `?j_` row in
    functions.csv at that RVA, the one matched non-generated functions.csv
    row at that RVA linking under NEW, or a primary vtable ??_7C@@6B@ whose
    retail slots reach a matched non-generated ??_G/??_E row of C) and
    recorded nowhere else, and OLD (decorated and bare) occurs nowhere under
    game/ or inputs/reference/shims/ except in a game/gen_asm|gen_small dump
    no functions.csv row builds, or only inside gen_asm PROC bodies no row
    builds (and their EXTERN line). Every deletion needs a trailer and every
    trailer a matching deletion.
  * An added line must be one the tool would accept for an unrecorded name:
    build.unrecorded_dir32_problem against the record as of the base
    revision, so the added lines cannot vouch for each other.

  * An address may move only by an OPERATOR CORRECTION (approved by the
    project lead 2026-10-16; correction_problems): trailer
    `Dir32-Operator-Correction: <name> 0x<oldVA> -> 0x<newVA> evidence=<path>`,
    one per commit, named verbatim in the owner-approved list
    targets/game/reverse/dir32_operator_corrections.txt, the record's only
    change, no functions.csv/data_rows.csv change, every proof read from the
    PARENT tree. pre-commit takes the claim from BFME_DIR32_OPERATOR_CORRECTION=
    '<name> 0x<old> -> 0x<new> evidence=<path>'; commit-msg and pre-push
    (--range, every outgoing commit) re-check the trailer; pre-push adds the
    TUs whose code holds a moved VA to its scoped build (--sources). Undo needs
    a guard change (see the operator-correction section).

Usage: python3 tools/dir32_record_guard.py --staged [BASE]     (BASE defaults to HEAD)
       python3 tools/dir32_record_guard.py --commit-msg FILE     (deletions vs HEAD)
       python3 tools/dir32_record_guard.py --range BASE TIP      (address moves, pre-push)
       python3 tools/dir32_record_guard.py --sources BASE TIP    (TUs a move must rebuild)

The --commit-msg path imports nothing from the tree: the hook pipes it from HEAD.
"""
import csv
import re
import subprocess
import sys
from pathlib import Path

if "__file__" in globals() and not __file__.startswith("<"):
    sys.path.insert(0, str(Path(__file__).resolve().parent))

REL = "targets/game/reverse/dir32_addresses.csv"
DATA_ROWS = "targets/game/reverse/data_rows.csv"
FUNCTIONS = "targets/game/reverse/functions.csv"
IMAGE_BASE = 0x400000
SOURCE_ROOTS = ("game/", "inputs/reference/shims/")
# Vendored libraries (.lib archives) carry their own decorated names; a name
# spelled there is a real upstream identity some vendored object references.
VENDOR_ROOTS = ("inputs/vendor/",)
GEN_ROOTS = ("game/gen_asm/", "game/gen_small/")
RETIRE_RE = re.compile(r"^Dir32-Retire:[ \t]*(\S+)[ \t]+0x([0-9A-Fa-f]{1,8})[ \t]+for[ \t]+(\S+)[ \t]*$",
                       re.MULTILINE)
TOOL = "python3 tools/dir32_record.py retire OLD --for NEW --msg <message file>"


def root():
    top = subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True)
    return top.stdout.strip() or "."


def git_show_text(spec):
    shown = subprocess.run(["git", "show", spec], cwd=root(), capture_output=True)
    return shown.stdout.decode("utf-8", "replace") if shown.returncode == 0 else None


def read_at(spec):
    text = git_show_text(spec)
    if text is None:
        return None
    return {row["name"]: int(row["va"], 16) for row in csv.DictReader(text.splitlines())}


def trailer(old, va, new):
    return f"Dir32-Retire: {old} 0x{va:08X} for {new}"


def parse_trailers(message):
    return [(m.group(1), int(m.group(2), 16), m.group(3)) for m in RETIRE_RE.finditer(message)]


def bare_identifier(name):
    """The identifier a decorated name spells: ?Foo@Bar@@3HA -> Foo, _g_x -> g_x,
    and a vtable ??_7Foo@@6B@ its class, Foo."""
    if name.startswith("??_7"):
        head = name[4:].split("@", 1)[0]
    elif name.startswith("?"):
        head = name[1:].split("@", 1)[0]
    elif name.startswith("__"):
        # __imp__strcmpi (an import slot; source spells strcmpi) and
        # __real@41200000 have no identifier a word search could find. A C
        # name like __bfmeDynBufXZ is source identifier _bfmeDynBufXZ.
        if name.startswith("__imp_"):
            return None
        head = name[1:]
    elif name.startswith("_"):
        head = re.sub(r"@\d+$", "", name[1:])  # _Foo@8: __stdcall C name
    else:
        head = name
    return head if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", head) else None


def function_rows(tree=":"):
    """(name, rva, source, status, notes) for every functions.csv row in TREE."""
    text = git_show_text(f"{tree}{FUNCTIONS}") or ""
    for row in csv.DictReader(text.splitlines()):
        try:
            rva = int(row["target_rva"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        yield row["name"], rva, row.get("source") or "", row.get("status") or "", row.get("notes") or ""


def is_generated(source):
    return source.startswith(GEN_ROOTS)


def object_symbol(notes):
    match = re.search(r"(?:^|;)object-symbol=([^;\s]+)", notes)
    return match.group(1) if match else None


def authored_row(source, status, name, notes):
    """A matched, non-generated row that links under its own name."""
    return (status == "matched" and not is_generated(source)
            and object_symbol(notes) in (None, name))


EXE = "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
_IMAGE = {}


def read_retail(va, size):
    """SIZE bytes of the retail image at VA, or None outside its sections."""
    if "sections" not in _IMAGE:
        try:
            data = (Path(root()) / EXE).read_bytes()
        except OSError:
            data = b""
        sections = []
        if len(data) > 0x40:
            pe = int.from_bytes(data[0x3C:0x40], "little")
            count = int.from_bytes(data[pe + 6:pe + 8], "little")
            table = pe + 24 + int.from_bytes(data[pe + 20:pe + 22], "little")
            for i in range(count):
                at = table + 40 * i
                vsize, vaddr, rsize, raw = (int.from_bytes(data[at + 8 + 4 * k:at + 12 + 4 * k], "little")
                                            for k in range(4))
                characteristics = int.from_bytes(data[at + 36:at + 40], "little")
                sections.append((vaddr, min(vsize, rsize), raw, bool(characteristics & 0x20000000)))
        _IMAGE["data"], _IMAGE["sections"] = data, sections
    rva = va - IMAGE_BASE
    for vaddr, length, raw, _code in _IMAGE["sections"]:
        if vaddr <= rva and rva + size <= vaddr + length:
            return _IMAGE["data"][raw + rva - vaddr:raw + rva - vaddr + size]
    return None


def in_code(va):
    read_retail(IMAGE_BASE, 0)
    rva = va - IMAGE_BASE
    return any(code and vaddr <= rva < vaddr + length for vaddr, length, _raw, code in _IMAGE["sections"])


VTABLE_RE = re.compile(r"^\?\?_7(.+)@@6B@$")
VTABLE_SLOTS = 512


def code_references(va):
    """True when retail code holds VA as an imm32/disp32 anywhere: a ctor/dtor
    `mov [reg], imm32` marks a table start, so a slot walk must stop there."""
    if "code" not in _IMAGE:
        read_retail(IMAGE_BASE, 0)
        _IMAGE["code"] = b"".join(_IMAGE["data"][raw:raw + length]
                                  for _vaddr, length, raw, code in _IMAGE["sections"] if code)
    return _IMAGE["code"].find(va.to_bytes(4, "little")) >= 0


def vtable_slot_targets(va, starts=frozenset()):
    """RVAs the vtable at VA reaches, one ILT `jmp rel32` followed per slot. Retail
    has no RTTI locators between tables, so the slots run until the first dword
    that is not a code address or the first address in STARTS (another recorded
    name or data row, or an address retail code references: the next table's start)."""
    out = set()
    for slot in range(VTABLE_SLOTS):
        if slot and (va + 4 * slot in starts or code_references(va + 4 * slot)):
            break
        raw = read_retail(va + 4 * slot, 4)
        if raw is None:
            break
        target = int.from_bytes(raw, "little")
        if not in_code(target):
            break
        out.add(target - IMAGE_BASE)
        jump = read_retail(target, 5)
        if jump and jump[0] == 0xE9:
            out.add(((target + 5 + int.from_bytes(jump[1:], "little", signed=True)) & 0xFFFFFFFF)
                    - IMAGE_BASE)
    return out


def data_vas(tree=":"):
    out = set()
    for row in csv.DictReader((git_show_text(f"{tree}{DATA_ROWS}") or "").splitlines()):
        try:
            at = int(row["address"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        out.add(at + IMAGE_BASE if row.get("address_kind") == "rva" else at)
    return out


DTOR_RE = re.compile(r"^\?\?_[GE](.+?)@@")
def is_dtor_of(name, cls):
    """NAME is ??_G/??_E of exactly class CLS: the qualified name ends at `@@`
    and a plain virtual access code follows (U/M/E: public/protected/private
    virtual). A further `@` would mean CLS is only a prefix of a template's
    argument list; W/O/G codes are this-adjusting thunks, which sit in
    secondary tables, so they never prove a primary vtable."""
    for kind in ("??_G", "??_E"):
        head = f"{kind}{cls}@@"
        if name.startswith(head) and name[len(head):len(head) + 1] in ("U", "M", "E"):
            return True
    return False


SECONDARY_VTABLE_RE = re.compile(r"^\?\?_7.+@@6B(?!@$).+$")


def function_owner_problem(name, va, tree=":", old_name=None, recorded=None, rows=None, starts=None):
    """None when NAME is ledger-proven at VA as code, else why not.
      * a function: the one matched, non-generated functions.csv row at VA's RVA
        is NAME (it links under NAME, no other authored row claims the RVA);
      * a primary vtable ??_7C@@6B@: a slot of retail's table at VA reaches
        (directly or through one ILT jmp) a matched, non-generated ??_G/??_E
        deleting destructor of the same class C. A class's deleting destructor
        is its own (derived classes get their own), so it sits in C's vtable
        only; a ctor is no proof, since it also stores its bases' vtables."""
    rows = list(function_rows(tree)) if rows is None else rows
    rva = va - IMAGE_BASE
    match = VTABLE_RE.match(name)
    if match:
        cls = match.group(1)
        # Every retail table start is stored by a ctor/dtor (`mov [reg], imm32`);
        # the walk stops at the next such address. Same invariant, both ends.
        if not code_references(va):
            return f"no retail code references 0x{va:08X}, so it is not a vtable start"
        if old_name and SECONDARY_VTABLE_RE.match(old_name):
            return f"{old_name} names a secondary (multiple-inheritance) table, {name} a primary one"
        dtors = {r for n, r, src, st, notes in rows
                 if is_dtor_of(n, cls) and authored_row(src, st, n, notes)}
        if not dtors:
            return f"no matched, non-generated ??_G/??_E deleting destructor row of {cls} proves its vtable"
        if starts is None:
            starts = set((recorded or {}).values()) | data_vas(tree)
        reached = vtable_slot_targets(va, starts)
        if not dtors & reached:
            return f"retail's table at 0x{va:08X} does not reach a matched deleting destructor of {cls}"
        # Unrecorded neighbours leave the table's end unknown: a walk that also
        # reaches another class's deleting destructor ran into a second table.
        foreign = sorted({n for n, r, *_ in rows if r in reached and DTOR_RE.match(n)
                          and not is_dtor_of(n, cls)})
        if foreign:
            return (f"retail's slots from 0x{va:08X} also reach {foreign[0]}, another class's "
                    "deleting destructor; the table's end is unknown")
        return None
    here = [(n, src, st, notes) for n, r, src, st, notes in rows
            if r == rva and st == "matched" and not n.startswith("?j_")]
    mine = [row for row in here if row[0] == name]
    thunk = read_retail(va, 1)
    if mine and thunk == b"\xE9":
        return f"0x{va:08X} is a jmp thunk; retire for its ?j_ row, not the body's name"
    if not mine:
        return f"no matched functions.csv row {name} at RVA 0x{rva:08X}"
    _n, src, st, notes = mine[0]
    if is_generated(src):
        return f"{name} is a generated row ({src}), not an identity"
    if object_symbol(notes) not in (None, name):
        return f"{name} links as object-symbol {object_symbol(notes)}, not under its own name"
    others = sorted({n for n, src, _st, _notes in here if n != name and not is_generated(src)})
    if others:
        return f"RVA 0x{rva:08X} has other matched rows ({others[0]}); one identity per body"
    return None


def owners_at(va, tree=":"):
    """Ledger names that own retail VA in TREE (':' is the index): data rows at
    that VA and `?j_` function rows at that RVA."""
    out = set()
    for row in csv.DictReader((git_show_text(f"{tree}{DATA_ROWS}") or "").splitlines()):
        try:
            at = int(row["address"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        if row.get("address_kind") == "rva":
            at += IMAGE_BASE
        if at == va:
            out.add(row["name"])
    rva = va - IMAGE_BASE
    for line in (git_show_text(f"{tree}{FUNCTIONS}") or "").splitlines():
        if not line.startswith("?j_"):
            continue
        cols = line.split(",")
        try:
            if int(cols[2], 16) == rva:
                out.add(cols[0])
        except (IndexError, ValueError):
            continue
    return out


def row_sources(tree=":"):
    return {src for _n, _r, src, _st, _notes in function_rows(tree)}


def source_mentions(name):
    """Indexed paths that spell NAME: game/ and the shims (decorated or bare), the
    vendored libraries (decorated), and every other file a functions.csv row
    builds from (toolchain CRT libraries, reference sources; both spellings)."""
    hits = set()
    built = sorted(src for src in row_sources()
                   if src and not src.startswith(SOURCE_ROOTS + VENDOR_ROOTS))
    for needle, word in ((name, False), (bare_identifier(name), True)):
        if not needle:
            continue
        cmd = ["git", "grep", "--cached", "-l", "-F"] + (["-w"] if word else []) + ["-e", needle]
        roots = SOURCE_ROOTS + (() if word else VENDOR_ROOTS) + tuple(built)
        got = subprocess.run(cmd + ["--", *roots], cwd=root(), capture_output=True, text=True)
        hits.update(p for p in got.stdout.splitlines() if p)
    # A generated dump no functions.csv row builds is never compiled, linked or
    # DIR32-checked, and nobody may edit it: its spelling references nothing.
    # A dump some row still builds keeps blocking. A later conversion of such a
    # dump (list_naked_candidates.py) must spell NEW, not OLD: OLD is retired.
    dead = {p for p in hits if is_generated(p)}
    if dead:
        dead -= row_sources()
    # A gen_asm dump that rows still build stops blocking only when every
    # spelling of NAME in it sits inside PROC bodies that are dead (approved by
    # the project lead 2026-10-16): no row builds the proc, nothing anywhere
    # references it or a label it defines, and a matched hand-written row
    # covers its retail address. The assembler still emits such a proc into
    # the linked object (the .asm is assembled whole, its segments are not
    # COMDATs), but no code reaches it and no gate verifies it. Its EXTERN line
    # only serves those procs. Anything else, or a gen_small C++ dump, blocks.
    # The test is the file's FORMAT, not dumpness: only a generated MASM file
    # (.asm under GEN_ROOTS) has PROC bodies to read; whether a row is a dump is
    # build.is_scaffold_row's question and is not asked here.
    dead |= {p for p in hits - dead if is_generated(p) and p.endswith(".asm")
             and only_in_unbuilt_procs(p, name, bare_identifier(name))}
    return sorted(hits - dead)


PROC_RE = re.compile(r"^(\S+)[ \t]+PROC\b", re.IGNORECASE)
ADDRESS_PROC_RE = re.compile(r"^\?d_([0-9A-Fa-f]{8})@@YAXXZ$")
# The only lines tools/dump_apply.py writes inside a dump body: byte/word
# literals, dwords (numbers or a symbol), and call/jmp to a symbol. A dead
# body holding anything else (a label, EQU, TEXTEQU, MACRO, ...) could define
# something a built proc uses, so it is not provably dead.
DUMP_BODY_RE = re.compile(r"^[ \t]+(?:d[bw][ \t]+[0-9A-Fa-fhH, \t]+|dd[ \t]+[\w$?@+\- \t,]+"
                          r"|(?:call|jmp)[ \t]+[\w$?@]+)[ \t]*$")
# Conditional assembly, comments blocks, macros, text equates and includes
# make the text MASM assembles differ from the lines read here (bounds can be
# forged); a dump containing any of them is never exempted.
UNSAFE_DUMP_RE = re.compile(r"(?im)^[ \t]*(?:[\w$?@]+[ \t]+)?(?:IF\w*|ELSE\w*|ENDIF|COMMENT|MACRO|ENDM|"
                            r"INCLUDE\w*|TEXTEQU|EQU|CATSTR|SUBSTR|FOR|FORC|REPEAT|WHILE|PURGE)\b")
_TOKEN_EDGE = r"[\w$?@]"


def dump_lines(text):
    """The dump's lines as MASM reads them (split on \n only), or None when the
    text holds a control character other than tab/CR or an unsafe directive."""
    if re.search(r"[\x00-\x08\x0b\x0c\x0e-\x1f\x7f\x85  ]", text) or UNSAFE_DUMP_RE.search(text):
        return None
    return [line.rstrip("\r") for line in text.split("\n")]


def asm_procs(lines):
    """[(first line, last line, symbol)] of every `SYM PROC` .. `SYM ENDP` body,
    1-based and inclusive; None when a PROC opens inside another or never
    closes (the bounds are then unknown). LINES may be text (split on \n)."""
    if isinstance(lines, str):
        lines = [line.rstrip("\r") for line in lines.split("\n")]
    out, open_proc = [], None
    for number, line in enumerate(lines, 1):
        match = PROC_RE.match(line)
        if open_proc is None:
            if match:
                open_proc = (number, match.group(1))
        elif re.match(rf"^{re.escape(open_proc[1])}[ \t]+ENDP\b", line, re.IGNORECASE):
            out.append((open_proc[0], number, open_proc[1]))
            open_proc = None
        elif match:
            return None
    return None if open_proc else out


def built_symbols(path, tree=":"):
    """Symbols functions.csv rows in TREE build from PATH (any status): each
    row's name and its object-symbol=, if any."""
    out = set()
    for name, _rva, source, _status, notes in function_rows(tree):
        if source == path:
            out.add(name.lower())
            if object_symbol(notes):
                out.add(object_symbol(notes).lower())
    return out


_AUTHORED_STARTS = {}


def authored_row_starts(tree=":"):
    """RVAs where a matched, non-generated functions.csv row in TREE starts (cached)."""
    blob = subprocess.run(["git", "rev-parse", f"{tree}{FUNCTIONS}"], cwd=root(),
                          capture_output=True, text=True).stdout.strip()
    key = (root(), blob)                     # the ledger content, not just its name
    if key not in _AUTHORED_STARTS:
        starts = set()
        for _name, rva, source, status, _notes in function_rows(tree):
            if status == "matched" and not is_generated(source):
                starts.add(rva)
        _AUTHORED_STARTS.clear()
        _AUTHORED_STARTS[key] = starts
    return _AUTHORED_STARTS[key]


def referenced_elsewhere(symbols, path, lines, first, last):
    """True when any of SYMBOLS (decorated or bare, case-insensitive: ml -Cx
    resolves non-public names case-blind) is spelled in PATH outside lines
    FIRST..LAST (other than its own PUBLIC line), or in any other indexed file
    under game/, the shims, or a non-game source a functions.csv row builds."""
    tokens = [re.compile(rf"(?<!{_TOKEN_EDGE}){re.escape(s)}(?!{_TOKEN_EDGE})", re.IGNORECASE) for s in symbols]
    for number, line in enumerate(lines, 1):
        if first <= number <= last:
            continue
        for symbol, token in zip(symbols, tokens):
            if token.search(line) and not re.match(rf"^[ \t]*PUBLIC[ \t]+{re.escape(symbol)}[ \t]*$",
                                                   line, re.IGNORECASE):
                return True
    built = sorted(src for src in row_sources() if src and not src.startswith(SOURCE_ROOTS + VENDOR_ROOTS))
    cmd = ["git", "grep", "--cached", "-l", "-i", "-w", "-F"]
    for symbol in symbols:
        cmd += ["-e", symbol]
    got = subprocess.run(cmd + ["--", *SOURCE_ROOTS, *built], cwd=root(), capture_output=True, text=True)
    return any(p != path for p in got.stdout.splitlines() if p)


def dead_proc(path, symbol, lines, first, last, built, tree=":"):
    """A proc no row builds, whose body is only generator-written byte/call
    lines, that nothing references by its decorated or bare name, and whose
    retail address (?d_XXXXXXXX) is where a matched hand-written row starts."""
    if symbol.lower() in built:
        return False
    match = ADDRESS_PROC_RE.match(symbol)
    if not match or int(match.group(1), 16) not in authored_row_starts(tree):
        return False
    if not all(DUMP_BODY_RE.match(line) or not line.strip() for line in lines[first:last - 1]):
        return False
    return not referenced_elsewhere([symbol, symbol[1:symbol.index("@")]], path, lines, first, last)


def only_in_unbuilt_procs(path, name, bare=None, tree=":"):
    """True when every line of the dump at PATH (as TREE holds it) spelling
    NAME (decorated) or BARE (as a word), case-insensitively, lies in a dead
    PROC body (dead_proc), or is that name's own `EXTERN NAME:` declaration;
    and at least one such proc exists."""
    text = git_show_text(f"{tree}{path}")
    if text is None:
        return False
    lines = dump_lines(text)
    if lines is None:
        return False
    procs = asm_procs(lines)
    if procs is None:
        return False
    decorated = re.compile(re.escape(name), re.IGNORECASE)
    word = re.compile(rf"(?<![A-Za-z0-9_]){re.escape(bare)}(?![A-Za-z0-9_])", re.IGNORECASE) if bare else None
    built, verdict, seen = built_symbols(path, tree), {}, False
    for number, line in enumerate(lines, 1):
        if not decorated.search(line) and not (word and word.search(line)):
            continue
        inside = [(first, last, sym) for first, last, sym in procs if first <= number <= last]
        if inside:
            first, last, sym = inside[0]
            if sym not in verdict:
                verdict[sym] = dead_proc(path, sym, lines, first, last, built, tree)
            if not verdict[sym]:
                return False
            seen = True
        elif not re.match(rf"^[ \t]*EXTERN[ \t]+{re.escape(name)}:", line, re.IGNORECASE):
            return False
    return seen


PLACEHOLDER_RE = re.compile(
    r"(?i)(?:rva|va|gen|glo|dup_|d_|j_|obj|data?|addr|sub_|fun_|t\d\w*_)_?[0-9a-f]{5,8}"
    r"|(?:^|[?@_$])(?:bfme|gen_|genx|dup_|d_)"
    r"|^b_[0-9a-f]{8}$")


def is_placeholder(name):
    """An address-derived or generated stand-in name (Rva00819920, Gen_0014B790,
    bfmeCb974D, ?d_00819920, b_00548d90, T1A2_0110F9CC, g_Va0109FB78)."""
    return bool(PLACEHOLDER_RE.search(bare_identifier(name) or name))


def retire_problem(old_name, va, new_name, old, new):
    """None when OLD_NAME, recorded at VA in OLD, may be retired for NEW_NAME given
    the record NEW after the change, else why not. Ledgers and sources: the index."""
    if old.get(old_name) != va:
        where = f"0x{old[old_name]:08X}" if old_name in old else "nowhere"
        return f"{old_name} is recorded at {where}, not 0x{va:08X}"
    if new_name == old_name:
        return "NEW must differ from OLD"
    code_owner = new_name not in owners_at(va)
    if code_owner:
        code = function_owner_problem(new_name, va, old_name=old_name, recorded=old)
        if code:
            return (f"{new_name} is not ledger-owned at 0x{va:08X}: it needs a data_rows.csv row "
                    "at that VA (tools/add_data_match.py), a ?j_ functions.csv row at that RVA, "
                    "the matched non-generated function row there, or a vtable a matched deleting "
                    f"destructor of its class proves ({code})")
    if new_name in new and new[new_name] != va:
        return f"{new_name} is recorded at 0x{new[new_name]:08X}, not 0x{va:08X}"
    # A code owner (a function row or a vtable) is admitted only when OLD's
    # absence can be shown and nothing descriptive is lost.
    if code_owner and bare_identifier(old_name) is None:
        return (f"{old_name} spells no plain identifier (ctor/dtor/operator/template), so a source "
                "search cannot show nothing still references it")
    if code_owner and is_placeholder(new_name) and not is_placeholder(old_name):
        return f"{new_name} is an address-derived/placeholder name; it may not replace descriptive {old_name}"
    mentions = source_mentions(old_name)
    if mentions:
        return (f"{old_name} (or {bare_identifier(old_name)}) still appears in "
                + ", ".join(mentions[:3]) + (f" (+{len(mentions) - 3} more)" if len(mentions) > 3 else ""))
    return None


def retire_problems(old, new, message):
    """Every deleted line needs a matching Dir32-Retire trailer whose conditions hold,
    and every trailer a deleted line."""
    deleted = {name: old[name] for name in old.keys() - new.keys()}
    claims = parse_trailers(message)
    out, named = [], set()
    for name, va, for_name in claims:
        named.add(name)
        if name not in deleted:
            out.append(f"trailer retires {name} but this commit does not delete its line")
        elif va != deleted[name]:
            out.append(f"trailer gives {name} 0x{va:08X}; the deleted line recorded 0x{deleted[name]:08X}")
        else:
            problem = retire_problem(name, va, for_name, old, new)
            if problem:
                out.append(f"{name} for {for_name}: {problem}")
    for name in sorted(deleted.keys() - named):
        out.append(f"{name},0x{deleted[name]:08X} deleted without a Dir32-Retire trailer; use {TOOL}")
    return out


# ---------------------------------------------------------------------------
# Operator correction (approved by the project lead 2026-10-16): the one route
# by which a recorded address may change. A misrecorded primary vtable line is
# moved to the address retail proves, in a commit that does nothing else to
# the record or the ledgers, that an owner-approved list names exactly, and
# that carries its proof. Every proof reads the PARENT tree, so a commit can
# never manufacture its own.
#
# UNDO needs a guard change: the new address must pass the primary-vtable rule
# and the old one fail it, so reverting a correction to the misrecorded address
# is refused by construction.
# ---------------------------------------------------------------------------
CORRECTION_RE = re.compile(
    r"^Dir32-Operator-Correction:[ \t]*(\S+)[ \t]+0x([0-9A-Fa-f]{1,8})[ \t]+->[ \t]+"
    r"0x([0-9A-Fa-f]{1,8})[ \t]+evidence=(\S+)[ \t]*$", re.MULTILINE)
CORRECTION_ENV = "BFME_DIR32_OPERATOR_CORRECTION"
CITE_RE = re.compile(r"\b(ctor|dtor)=0x([0-9A-Fa-f]{1,8})\b")
APPROVED = "targets/game/reverse/dir32_operator_corrections.txt"
APPROVED_RE = re.compile(r"^(\S+)[ \t]+0x([0-9A-Fa-f]{1,8})[ \t]+->[ \t]+0x([0-9A-Fa-f]{1,8})(?:[ \t]+#.*)?$")
EVIDENCE_DIR = "targets/game/reverse/identity_evidence/"
LEDGERS = (FUNCTIONS, DATA_ROWS)


def parse_corrections(message):
    return [(m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4))
            for m in CORRECTION_RE.finditer(message)]


def approved_corrections(tree):
    """{(name, old VA, new VA)} the owner-approved list holds in TREE."""
    out = set()
    for line in (git_show_text(f"{tree}{APPROVED}") or "").splitlines():
        found = APPROVED_RE.match(line.strip())
        if found and not line.lstrip().startswith("#"):
            out.add((found.group(1), int(found.group(2), 16), int(found.group(3), 16)))
    return out


def as_rva(value):
    return value - IMAGE_BASE if value >= IMAGE_BASE else value


def decoded_operands(code, va):
    """[(instruction VA, mnemonic, [(kind, value)])] by linear decode (capstone):
    kind 'imm' or 'disp' (a memory operand's displacement), 'mem' marks the
    destination of a store."""
    import capstone
    from capstone import x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    out = []
    for insn in md.disasm(code, va):
        ops = []
        for op in insn.operands:
            if op.type == x86.X86_OP_IMM:
                ops.append(("imm", op.imm & 0xFFFFFFFF))
            elif op.type == x86.X86_OP_MEM:
                ops.append(("mem", op.mem.disp & 0xFFFFFFFF))
        out.append((insn.address, insn.mnemonic, ops))
    return out


def stores_table(code, va, table):
    """A decoded `mov dword ptr [mem], imm32` in CODE (at VA) whose immediate is TABLE."""
    return any(mnemonic == "mov" and len(ops) == 2 and ops[0][0] == "mem" and ops[1] == ("imm", table)
               for _at, mnemonic, ops in decoded_operands(code, va))


def references(code, va, target):
    """A decoded operand of CODE (at VA) holding TARGET as an imm32 or disp32."""
    return any(value == target for _at, _m, ops in decoded_operands(code, va) for _k, value in ops)


def row_sizes(tree):
    sizes = {}
    for row in csv.DictReader((git_show_text(f"{tree}{FUNCTIONS}") or "").splitlines()):
        try:
            sizes.setdefault((row["name"], int(row["target_rva"], 16)), int(row["target_size"]))
        except (KeyError, TypeError, ValueError):
            continue
    return sizes


def rows_referencing(va, rows, tree):
    """[(name, rva, source)] of matched, non-generated rows whose retail bytes
    hold VA as a decoded imm32/disp32 operand (one code scan, then decode)."""
    read_retail(IMAGE_BASE, 0)
    needle = va.to_bytes(4, "little")
    hits = []
    for vaddr, length, raw, code in _IMAGE["sections"]:
        if not code:
            continue
        blob = _IMAGE["data"][raw:raw + length]
        at = blob.find(needle)
        while at >= 0:
            hits.append(vaddr + at)
            at = blob.find(needle, at + 1)
    if not hits:
        return []
    sizes = row_sizes(tree)
    out = []
    for name, rva, source, status, _notes in rows:
        if status != "matched" or is_generated(source):
            continue
        size = sizes.get((name, rva))
        if not size or not any(rva <= h < rva + size for h in hits):
            continue
        code = read_retail(rva + IMAGE_BASE, size)
        if code and references(code, rva + IMAGE_BASE, va):
            out.append((name, rva, source))
    return out


def correction_problems(old, new, claims, parent, tree, changed_paths, added_paths):
    """[] when CLAIMS (one Dir32-Operator-Correction) is exactly the commit's
    change and the PARENT tree plus the retail image prove it, else why not.

    * exactly one claim, listed verbatim in the owner-approved APPROVED file of
      the parent tree; the record's only change is that name moving from the
      claimed old VA to the claimed new VA; functions.csv and data_rows.csv
      are untouched (identity fixes land in an earlier commit);
    * the name is a primary vtable ??_7C@@6B@; in the parent tree the new VA
      passes the primary-vtable rule and the old VA FAILS it; slot 0 of the
      new table (through one ILT jmp) is a matched, non-generated ??_G/??_E of
      exactly C; no other name is recorded at the new VA;
    * no matched, non-generated row of the parent tree whose source spells C
      still holds the old VA (decoded imm32/disp32): its TU would stop
      verifying; fix that row's identity first;
    * the evidence is a file this commit ADDS under identity_evidence/, citing
      both VAs, ctor=0x<rva> and dtor=0x<rva>. The ctor is a matched,
      non-generated row of the parent whose decoded code does `mov [mem],
      imm32` of the new VA, and is either named ??0C@@... or retail's ILT
      CONFIRMS that name there while CONTRADICTING the row's own name; the
      dtor is a matched, non-generated ??_G/??_E of C the new table reaches.
    The old VA simply loses the name; other names recorded there are untouched.
    """
    out = []
    if len(claims) != 1:
        return [f"{len(claims)} Dir32-Operator-Correction trailers; one correction per commit"]
    name, old_va, new_va, evidence = claims[0]
    if (name, old_va, new_va) not in approved_corrections(parent):
        out.append(f"`{name} 0x{old_va:08X} -> 0x{new_va:08X}` is not in the owner-approved {APPROVED} "
                   "of the parent commit")
    moved = {n: (old[n], new[n]) for n in old.keys() & new.keys() if old[n] != new[n]}
    if old.keys() != new.keys():
        out.append("a correction commit may not add or delete record lines")
    if set(moved) != {name}:
        out.append(f"the record's moved names are {sorted(moved) or 'none'}; a correction moves "
                   f"exactly {name}")
    elif moved[name] != (old_va, new_va):
        out.append(f"{name} moves 0x{moved[name][0]:08X} -> 0x{moved[name][1]:08X}, the trailer says "
                   f"0x{old_va:08X} -> 0x{new_va:08X}")
    touched = sorted(set(LEDGERS) & set(changed_paths))
    if touched:
        out.append(f"a correction commit may not change {', '.join(touched)}; land identity fixes first")
    match = VTABLE_RE.match(name)
    if not match or SECONDARY_VTABLE_RE.match(name):
        out.append(f"{name} is not a primary vtable ??_7C@@6B@; only those have a correction route")
        return out
    cls = match.group(1)
    others = sorted(n for n, va in new.items() if va == new_va and n != name)
    if others:
        out.append(f"0x{new_va:08X} is also recorded for {others[0]}")
    rows = list(function_rows(parent))
    recorded = {n: va for n, va in old.items() if n != name}
    problem = function_owner_problem(name, new_va, tree=parent, recorded=recorded, rows=rows)
    if problem:
        out.append(f"0x{new_va:08X} is not proven {name}: {problem}")
    if function_owner_problem(name, old_va, tree=parent, recorded=recorded, rows=rows) is None:
        out.append(f"0x{old_va:08X} still passes the primary-vtable rule for {cls}; nothing to correct")
    proving = {r for n, r, src, st, notes in rows if is_dtor_of(n, cls) and authored_row(src, st, n, notes)}
    slot0 = read_retail(new_va, 4)
    first = int.from_bytes(slot0, "little") if slot0 else 0
    jump = read_retail(first, 5) if first else None
    reach = {first - IMAGE_BASE}
    if jump and jump[0] == 0xE9:
        reach.add(((first + 5 + int.from_bytes(jump[1:], "little", signed=True)) & 0xFFFFFFFF) - IMAGE_BASE)
    if not reach & proving:
        out.append(f"slot 0 of 0x{new_va:08X} (0x{first:08X}) is not a matched ??_G/??_E of {cls}")
    blockers = [(n, r, s) for n, r, s in rows_referencing(old_va, rows, parent)
                if re.search(rf"\b{re.escape(cls)}\b", git_show_text(f"{parent}{s}") or "")]
    for n, r, s in blockers[:5]:
        out.append(f"{n} at 0x{r:08X} ({s}) spells {cls} and holds 0x{old_va:08X}; its TU would stop "
                   "verifying -- fix its identity in an earlier commit")
    if not evidence.startswith(EVIDENCE_DIR) or evidence not in added_paths:
        out.append(f"evidence {evidence} must be a file this commit ADDS under {EVIDENCE_DIR}")
        return out
    text = git_show_text(f"{tree}{evidence}")
    if text is None:
        out.append(f"evidence {evidence} is not in the committed tree")
        return out
    upper = text.upper()
    for label, va in (("old", old_va), ("new", new_va)):
        if f"{va:08X}" not in upper:
            out.append(f"evidence does not cite the {label} VA 0x{va:08X}")
    cites = {}
    for kind, value in CITE_RE.findall(text):
        cites.setdefault(kind, []).append(as_rva(int(value, 16)))
    if not cites.get("ctor"):
        out.append("evidence cites no ctor=0x<rva> storing the table")
    sizes = row_sizes(parent)
    for rva in cites.get("ctor", []):
        owners = [(n, src, notes) for n, r, src, st, notes in rows
                  if r == rva and authored_row(src, st, n, notes)]
        if len(owners) != 1:
            out.append(f"ctor=0x{rva:08X} is not exactly one matched, non-generated row in the parent")
            continue
        owner = owners[0][0]
        code = read_retail(rva + IMAGE_BASE, sizes.get((owner, rva), 0))
        if not code or not stores_table(code, rva + IMAGE_BASE, new_va):
            out.append(f"ctor=0x{rva:08X} ({owner}) has no decoded `mov [mem], 0x{new_va:08X}`")
        if not owner.startswith(f"??0{cls}@@"):
            tools = str(Path(root()) / "tools")   # piped from a revision: no __file__
            if tools not in sys.path:
                sys.path.insert(0, tools)
            import ilt_oracle
            wanted = f"??0{cls}@@QAE@XZ"
            if (ilt_oracle.check(wanted, rva)[0] != ilt_oracle.CONFIRMED
                    or ilt_oracle.check(owner, rva)[0] != ilt_oracle.CONTRADICTED):
                out.append(f"ctor=0x{rva:08X} is the row {owner}, not ??0{cls}@@, and retail's ILT does "
                           f"not confirm {wanted} there over it")
    if not cites.get("dtor"):
        out.append("evidence cites no dtor=0x<rva> (the ??_G proof)")
    reached = vtable_slot_targets(new_va, set(recorded.values()) | data_vas(parent))
    for rva in cites.get("dtor", []):
        if rva not in proving:
            out.append(f"dtor=0x{rva:08X} is not a matched, non-generated ??_G/??_E row of {cls}")
        elif rva not in reached:
            out.append(f"dtor=0x{rva:08X} is not reached by the table at 0x{new_va:08X}")
    return out


def env_corrections():
    import os
    value = os.environ.get(CORRECTION_ENV, "").strip()
    return parse_corrections(f"Dir32-Operator-Correction: {value}") if value else []


def changed_paths_of(*diff_args, added=False):
    got = subprocess.run(["git", "diff", "--name-only", "--no-renames"]
                         + (["--diff-filter=A"] if added else []) + list(diff_args),
                         cwd=root(), capture_output=True, text=True)
    if got.returncode:
        raise SystemExit(f"dir32_record_guard: git diff {' '.join(diff_args)} failed: {got.stderr.strip()}")
    return set(got.stdout.split())


def staged_correction_problems(old, new, claims):
    return correction_problems(old, new, claims, "HEAD:", ":",
                               changed_paths_of("--cached", "HEAD"),
                               changed_paths_of("--cached", "HEAD", added=True))


def _range_commits(base, tip):
    listed = subprocess.run(["git", "rev-list", "--reverse", "--first-parent", f"{base}..{tip}",
                             "--", REL], cwd=root(), capture_output=True, text=True)
    if listed.returncode:
        raise SystemExit(f"dir32_record_guard: cannot list {base}..{tip}: {listed.stderr.strip()}")
    commits = listed.stdout.split()
    messages = subprocess.run(["git", "log", "--format=%H", "--grep", "^Dir32-Operator-Correction:",
                               f"{base}..{tip}"], cwd=root(), capture_output=True, text=True)
    return commits + [c for c in messages.stdout.split() if c not in commits]


def check_range(base, tip):
    """pre-push: every commit in BASE..TIP that moves a recorded address must
    carry a valid operator correction for exactly that move, judged against
    its own parent, and every correction trailer must match a move."""
    bad = 0
    for sha in _range_commits(base, tip):
        old = read_at(f"{sha}^:{REL}") or {}
        new = read_at(f"{sha}:{REL}") or {}
        message = subprocess.run(["git", "log", "-1", "--format=%B", sha], cwd=root(),
                                 capture_output=True, text=True).stdout
        claims = parse_corrections(message)
        moved = [n for n in old.keys() & new.keys() if old[n] != new[n]]
        if not claims and not moved:
            continue
        if not claims:
            found = [f"{n}: recorded 0x{old[n]:08X} moved to 0x{new[n]:08X} without a "
                     "Dir32-Operator-Correction" for n in sorted(moved)]
        else:
            found = correction_problems(old, new, claims, f"{sha}^:", f"{sha}:",
                                        changed_paths_of(f"{sha}^", sha),
                                        changed_paths_of(f"{sha}^", sha, added=True))
        if found:
            bad += 1
            print(f"dir32_record_guard: FAIL {sha[:10]}:", file=sys.stderr)
            for line in found[:20]:
                print("    " + line, file=sys.stderr)
    if bad:
        return 1
    print(f"dir32_record_guard: OK (record moves in {base[:10]}..{tip[:10]} all corrected)")
    return 0


def moved_sources(base, tip):
    """pre-push scoped build: `source:<path>` for every matched, non-generated
    row (at TIP) whose retail code holds a moved name's old or new VA, so a
    record-only commit still rebuilds every TU whose DIR32 check it changes."""
    rows = list(function_rows(f"{tip}:"))
    out = set()
    for sha in _range_commits(base, tip):
        old = read_at(f"{sha}^:{REL}") or {}
        new = read_at(f"{sha}:{REL}") or {}
        for name in old.keys() & new.keys():
            if old[name] != new[name]:
                for va in (old[name], new[name]):
                    out.update(src for _n, _r, src in rows_referencing(va, rows, f"{tip}:"))
    for source in sorted(out):
        print(f"source:{source}")
    return 0


def check_commit_msg(message_file):
    if subprocess.run(["git", "rev-parse", "-q", "--verify", "MERGE_HEAD"], cwd=root(),
                      capture_output=True).returncode == 0:
        return 0
    old, new = read_at(f"HEAD:{REL}"), read_at(f":{REL}")
    with open(message_file, encoding="utf-8", errors="replace") as handle:
        message = handle.read()
    old, new = old or {}, new or {}
    claims = parse_corrections(message)
    moved = [n for n in old.keys() & new.keys() if old[n] != new[n]]
    if claims or moved:
        found = (staged_correction_problems(old, new, claims)
                 if claims else [f"{n}: recorded address moved without a Dir32-Operator-Correction"
                                 for n in sorted(moved)])
        if found:
            print(f"dir32_record_guard: FAIL operator correction of {REL}", file=sys.stderr)
            for line in found[:20]:
                print("    " + line, file=sys.stderr)
            return 1
        print(f"dir32_record_guard: OK (operator correction {claims[0][0]} "
              f"0x{claims[0][1]:08X} -> 0x{claims[0][2]:08X})")
        return 0
    if not (old.keys() - new.keys()) and not parse_trailers(message):
        return 0
    found = retire_problems(old, new, message)
    if found:
        print(f"dir32_record_guard: FAIL {len(found)} retirement problem(s) in {REL}", file=sys.stderr)
        for line in found[:20]:
            print("    " + line, file=sys.stderr)
        return 1
    print(f"dir32_record_guard: OK ({len(old.keys() - new.keys())} line(s) retired)")
    return 0


def problems(old, new, symbol_map=None, corrections=()):
    import build
    out = []
    moved = [n for n in old.keys() & new.keys() if old[n] != new[n]]
    if corrections and moved:
        # pre-commit cannot see the message: the env claim is checked here and
        # the trailer again by commit-msg and pre-push. A claim left in the
        # environment of a commit that moves nothing is ignored, never a refusal.
        return staged_correction_problems(old, new, list(corrections))
    for name in sorted(moved):
        out.append(f"{name}: recorded 0x{old[name]:08X} rewritten to 0x{new[name]:08X}; "
                       f"retire the line instead ({TOOL}), or, for a misrecorded primary "
                       "vtable, an operator correction (Dir32-Operator-Correction)")
    added = sorted(new.keys() - old.keys())
    if added:
        identities = build.dir32_identities(old)
        if symbol_map is None:
            symbol_map = build.load_symbol_map()
        for name in added:
            problem = build.unrecorded_dir32_problem(name, new[name], identities, symbol_map)
            if problem:
                out.append(f"{name},0x{new[name]:08X} added: {problem}")
    return out


def main(argv):
    if len(argv) == 2 and argv[0] == "--commit-msg":
        return check_commit_msg(argv[1])
    if len(argv) == 3 and argv[0] == "--range":
        return check_range(argv[1], argv[2])
    if len(argv) == 3 and argv[0] == "--sources":
        return moved_sources(argv[1], argv[2])
    if not argv or argv[0] != "--staged":
        sys.exit(__doc__)
    base = argv[1] if len(argv) > 1 else "HEAD"
    old, new = read_at(f"{base}:{REL}"), read_at(f":{REL}")
    if new is None:
        sys.exit(f"dir32_record_guard: {REL} is not in the index")
    found = problems(old or {}, new, corrections=env_corrections())
    if found:
        print(f"dir32_record_guard: FAIL {len(found)} change(s) to {REL} the gate did not make")
        for line in found[:20]:
            print("    " + line)
        return 1
    print(f"dir32_record_guard: OK ({len(old or {})} -> {len(new)} recorded names)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
