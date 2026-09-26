#!/usr/bin/env python3
"""Preserve descriptive names across edits and bank-to-source conversions.

Usage: name_regression.py OLD NEW (NEW may be ':' for the index).
Unlike name_oracle, this compares history, not the witness's class-name key.
It checks explicit identifier substitutions, unambiguous computable layouts,
and single-row symbol changes at the same ledger address. It does not infer
semantic identity from a successful byte match.
"""
import argparse
import csv
import difflib
import hashlib
import io
import json
import re
import subprocess
from collections import defaultdict
from functools import lru_cache
from dataclasses import dataclass
from pathlib import Path

import name_oracle as oracle
import layout_history

ROOT = Path(__file__).resolve().parents[1]
CORRECTIONS = 'targets/game/reverse/name_corrections.json'
SOURCE = ('.cpp', '.cc', '.cxx', '.c', '.h', '.hh', '.hpp', '.hxx')
TOKEN = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|0[xX][0-9a-fA-F]+|\d+|[^\s]', re.S)
IDENT = re.compile(r'^[A-Za-z_]\w*$')
OPAQUE = re.compile(
    r'^(?:Rva[0-9a-f]{8}|(?:d|dup|j|sub|FUN)_[0-9a-f]{8}|'
    r'Gen_?[0-9a-f]{8}|Gen_t_[0-9a-f]{8}|'
    r'(?:rva|func|fn)_?[0-9a-f]{8})', re.I)
KEYWORDS = set('void bool char short int long float double signed unsigned const volatile static extern class struct public private protected return true false nullptr typedef typename auto Bool Byte Short UnsignedByte UnsignedShort WideChar Int UnsignedInt UnsignedInt32 Real Int64 UnsignedInt64'.split())
ADDRESS = re.compile(r'(?:rva|0x|(?:^|_)\s*)([0-9a-f]{8})(?![0-9a-f])', re.I)


# Unlike the witness oracle's broad work-queue heuristic, a historical gate
# must not classify m_fieldOfView or m_reservedCapacity as unnamed storage.
FIELD_OPAQUE = re.compile(
    r"^m_(?:(?:unk(?:nown)?|unmodelled|field|pad(?:ding)?|slack|slot|reserved|unused|opaque)"
    r"(?:_?(?:0x)?[0-9a-fA-F]+)?"
    r"|(?:bfme)?(?:dword|word|byte|bool|int|float|short|ptr|hash|string|str|val|value)"
    r"(?:_?(?:0x)?[0-9][0-9a-fA-F]*)?"
    r"|(?:at|f|bfme|p)(?:0x)?[0-9][0-9a-fA-F]*"
    r"|(?:0x)?[0-9][0-9a-fA-F]*)$"
)


def opaque(name):
    return bool(OPAQUE.match(name) or FIELD_OPAQUE.fullmatch(name))


def downgrade(old, new):
    return old != new and bool(IDENT.fullmatch(old)) and old not in KEYWORDS and not opaque(old) and opaque(new)


def tokens(text):
    return [t for t in TOKEN.findall(text) if not t.startswith(('//', '/*', '"', "'"))]


FUNCTION_DECL_TAIL = {
    ';', '{', '=', ':', 'const', 'volatile', 'noexcept', 'override',
    'final', 'try', '->',
}
FUNCTION_PREFIX_BLOCKERS = {
    '(', '[', '{', '}', ';', ',', '=', 'return', 'if', 'while', 'for',
    'switch', 'case', 'throw', 'new', 'delete', 'sizeof', 'decltype',
    '?', '.', '&', '*', '+', '-', '!', '~', '#',
}


def _paren_pairs(values):
    stack = []
    pairs = {}
    for index, value in enumerate(values):
        if value == '(':
            stack.append(index)
        elif value == ')' and stack:
            pairs[stack.pop()] = index
    return pairs


def _declaration_prefix(values, name_index):
    """Return the tokens before a possible qualified function name.

    A qualified call such as `Owner::run()` has no return-type prefix, while a
    definition such as `void Owner::run()` does.  Keeping that distinction
    prevents the declaration pass from pairing arbitrary calls.
    """
    start = name_index
    while (start >= 3 and values[start - 2:start] == [':', ':']
           and IDENT.fullmatch(values[start - 3])):
        start -= 3
    boundary = start - 1
    while boundary >= 0 and values[boundary] not in (';', '{', '}', '(', '[', ']', ','):
        boundary -= 1
    return values[boundary + 1:start]



def _is_function_declaration(values, name_index, open_index, close_index):
    name = values[name_index]
    if not IDENT.fullmatch(name) or name in KEYWORDS or name == 'operator':
        return False
    if name_index + 1 != open_index:
        return False
    previous = values[name_index - 1] if name_index else ''
    if previous in FUNCTION_PREFIX_BLOCKERS:
        return False
    if previous == '>' and name_index >= 2 and values[name_index - 2] == '-':
        return False
    if previous == ':' and not (name_index >= 2 and values[name_index - 2] == ':'):
        return False
    if previous == ':':
        prefix = _declaration_prefix(values, name_index)
        if not prefix or any(value in FUNCTION_PREFIX_BLOCKERS for value in prefix):
            return False
    if close_index + 1 < len(values) and values[close_index + 1] not in FUNCTION_DECL_TAIL:
        return False
    return True


def _function_declarations(values):
    declarations = {}
    for open_index, close_index in _paren_pairs(values).items():
        name_index = open_index - 1
        if name_index >= 0 and _is_function_declaration(
                values, name_index, open_index, close_index):
            declarations[name_index] = (open_index, close_index)
    return declarations


def _equal_token_alignment(old, new):
    alignment = {}
    for tag, a, b, c, d in difflib.SequenceMatcher(
            None, old, new, autojunk=False).get_opcodes():
        if tag == 'equal':
            alignment.update({a + offset: c + offset for offset in range(b - a)})
    return alignment


def _templated_type_declaration(values, name_index):
    """Whether a class/struct name immediately follows a template prefix."""
    if name_index < 2 or values[name_index - 1] not in ('class', 'struct'):
        return False
    end = name_index - 2
    if values[end] != '>':
        return False
    depth = 0
    for index in range(end, -1, -1):
        if values[index] == '>':
            depth += 1
        elif values[index] == '<':
            depth -= 1
            if depth == 0:
                return index > 0 and values[index - 1] == 'template'
    return False


def _function_declaration_regressions(old, new):
    """Find only declaration names whose parameter boundaries remain aligned.

    The ordinary token pass intentionally handles equal-sized identifier
    substitutions.  This narrower pass covers a declaration when a return
    type, storage class, or calling convention also changes and makes the
    surrounding replacement unequal.  Exact parameter tokens plus aligned
    opening and closing parentheses are required; there is no name-only
    pairing across removed/added functions or overloads.
    """
    old_declarations = _function_declarations(old)
    new_declarations = _function_declarations(new)
    alignment = _equal_token_alignment(old, new)
    found = set()
    for old_name_index, (old_open, old_close) in old_declarations.items():
        new_open = alignment.get(old_open)
        new_close = alignment.get(old_close)
        if new_open is None or new_close is None:
            continue
        if old[old_open:old_close + 1] != new[new_open:new_close + 1]:
            continue
        candidates = [
            new_name_index for new_name_index, (candidate_open, candidate_close)
            in new_declarations.items()
            if candidate_open == new_open and candidate_close == new_close
            and downgrade(old[old_name_index], new[new_name_index])
        ]
        if len(candidates) == 1:
            found.add((old[old_name_index], new[candidates[0]]))
    return found


def layouts(text):
    # Strip prose/literals before looking for declarations; offset annotations
    # remain in the original input to the established layout walker.
    masked = TOKEN.sub(lambda m: ' ' * len(m[0]) if m[0].startswith(('//', '/*', '"', "'")) else m[0], text)
    result = {}
    for decl in oracle.DECL.finditer(masked):
        rows, refused = oracle.outer_members(text, decl.end() - 1, bool(decl.group('base')))
        if not refused and rows:
            result[decl[1]] = {off: (member, span, array) for member, off, _, _, span, array in rows}
    return result


def regressions(before, after):
    found = set()
    old, new = tokens(before), tokens(after)
    if old == new:
        return []
    # Moving a retained type before a new namespace can align its old
    # declaration with the namespace declaration. That is not a type rename.
    type_definition = re.compile(r'\b(?:class|struct)\s+([A-Za-z_]\w*)[^;{}]*\{')
    namespace_definition = re.compile(r'\bnamespace\s+([A-Za-z_]\w*)\s*\{')
    old_text, new_text = ' '.join(old), ' '.join(new)
    retained_types = (set(type_definition.findall(old_text)) &
                      set(type_definition.findall(new_text)))
    added_namespaces = (set(namespace_definition.findall(new_text)) -
                        set(namespace_definition.findall(old_text)))
    # Exact token alignment handles functions, locals and declarations even
    # when the surrounding class is not sizeable. Comments cannot preserve a name.
    for tag, a, b, c, d in difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes():
        if tag == 'replace' and b - a == d - c:
            for offset, (x, y) in enumerate(zip(old[a:b], new[c:d])):
                old_pos, new_pos = a + offset, c + offset
                moved_type = (x in retained_types and y in added_namespaces and
                              old_pos > 0 and new_pos > 0 and
                              old[old_pos - 1] in ('class', 'struct') and
                              new[new_pos - 1] == 'namespace')
                # A bare MSVC attribute can align with a new sizeof operand.
                # Exempt this occurrence, not real identifiers named "naked".
                compiler_attribute = (
                    old_pos >= 2 and old_pos + 1 < len(old) and
                    old[old_pos - 2] in ('__declspec', '_declspec') and
                    old[old_pos - 1] == '(' and old[old_pos + 1] == ')')
                # A removed template helper can align with a newly added plain
                # class at the same location.  Its template prefix makes that
                # declaration pairing ambiguous; other uses and matching
                # layouts are still checked independently.
                template_mismatch = (
                    _templated_type_declaration(old, old_pos) !=
                    _templated_type_declaration(new, new_pos))
                if (downgrade(x, y) and not moved_type and
                        not compiler_attribute and not template_mismatch):
                    found.add((x, y))
    found.update(_function_declaration_regressions(old, new))
    left, right = layouts(before), layouts(after)
    for owner, members in left.items():
        if owner in right:
            candidates = [owner]
        else:
            shape = {off: value[1:] for off, value in members.items()}
            candidates = [name for name, fields in right.items()
                          if name not in left
                          if {off: value[1:] for off, value in fields.items()} == shape]
            # Removing a local type during header adoption does not rename it
            # to an unrelated, already-present type with the same layout.
            # Never pick arbitrarily between two identical carrier layouts.
            if len(candidates) != 1:
                continue
        target = candidates[0]
        if downgrade(owner, target):
            found.add((owner, target))
        for off, (name, span, array) in members.items():
            other = right[target].get(off)
            if other and other[1:] == (span, array) and downgrade(name, other[0]):
                found.add((name, other[0]))
    return sorted(found)


def git(root, *args):
    return subprocess.run(['git', *args], cwd=root, check=True, capture_output=True).stdout.decode('utf-8', 'replace')


def read(root, ref, path):
    spec = ':' + path if ref == ':' else ref + ':' + path
    exists = subprocess.run(['git', 'cat-file', '-e', spec], cwd=root, capture_output=True)
    if exists.returncode:
        return None
    return git(root, 'show', spec)


def read_many(root, ref, paths):
    """Read changed Git blobs in one framed request; missing paths stay explicit."""
    paths = sorted(set(paths))
    if not paths:
        return {}
    specs = [':' + path if ref == ':' else ref + ':' + path for path in paths]
    if any('\n' in spec or '\r' in spec for spec in specs):
        raise ValueError('newline in Git blob request')
    out = subprocess.run(['git', 'cat-file', '--batch'], cwd=root,
                         input=('\n'.join(specs) + '\n').encode(),
                         capture_output=True, check=True).stdout
    stream = io.BytesIO(out)
    values = {}
    for path in paths:
        header = stream.readline().rstrip(b'\n')
        if header.endswith(b' missing'):
            values[path] = None
            continue
        fields = header.split(b' ')
        if len(fields) != 3 or fields[1] != b'blob':
            raise ValueError(f'{ref}:{path}: unexpected Git object header {header!r}')
        size = int(fields[2])
        data = stream.read(size)
        if len(data) != size or stream.read(1) != b'\n':
            raise ValueError(f'{ref}:{path}: truncated Git blob batch')
        values[path] = data.decode('utf-8', 'replace')
    if stream.read(1):
        raise ValueError('extra Git blob batch data')
    return values


def diff_args(old, new):
    return ['--cached', old] if new == ':' else [old, new]


def ledger_diff(root, old, new):
    old_path = layout_history.path_at(old, 'targets/game/reverse/functions.csv',
                                       layout_history.OLD_LEDGER, root=root,
                                       allow_missing=True)
    new_path = layout_history.path_at('' if new == ':' else new,
                                       'targets/game/reverse/functions.csv',
                                       layout_history.OLD_LEDGER, root=root,
                                       allow_missing=True)
    if not old_path or not new_path or old_path == new_path:
        return git(root, 'diff', '--unified=0', '--no-renames',
                   *diff_args(old, new), '--', new_path or old_path or
                   'targets/game/reverse/functions.csv')
    before = csv.DictReader((read(root, old, old_path) or '').splitlines())
    after = csv.DictReader((read(root, new, new_path) or '').splitlines())
    def claims(rows):
        return [(r['name'], r['export_rva'], r['target_rva'], r['target_size'],
                 layout_history.canonical_source(r['source']), r['status'])
                for r in rows]
    if claims(before) != claims(after):
        raise ValueError('ledger relocation changed a function claim')
    return ''


def source(path):
    # Generated files hold many unrelated placeholder bodies.  A ledger row
    # moving from one of them to authored C++ links the entire old file to the
    # new one, so comparing its declarations invents name regressions.
    return (not path.startswith('game/gen_small/') and
            path.startswith(('game/', 'inputs/reference/shims/', 'targets/game/reverse/attempts/')) and
            path.endswith(SOURCE))


def pairs(root, old, new):
    args = diff_args(old, new)
    changes = []
    fields = git(root, 'diff', '--name-status', '-z', '-M1%', *args).split('\0')
    i = 0
    while i < len(fields) and fields[i]:
        status = fields[i]; i += 1
        count = 2 if status.startswith(('R', 'C')) else 1
        changes.append((status, fields[i:i + count]))
        i += count
    paths = {path for status, names in changes if status not in ('R100', 'C100')
             for path in names}
    source_paths = {path for path in paths if source(path)}
    old_paths = source_paths | {names[0] for status, names in changes
                                if status.startswith(('R', 'C')) and status not in ('R100', 'C100')
                                and source(names[1])}
    snapshots = {(old, path): value for path, value in read_many(root, old, old_paths).items()}
    snapshots.update({(new, path): value for path, value in read_many(root, new, source_paths).items()})
    @lru_cache(maxsize=None)
    def snapshot(ref, path):
        return snapshots.get((ref, path)) if (ref, path) in snapshots else read(root, ref, path)
    left, right = {}, {}
    ids = {}
    for path in paths:
        if not source(path):
            continue
        for ref, dest in ((old, left), (new, right)):
            text = snapshot(ref, path)
            if text is not None:
                dest[path] = text
        ids[path] = {int(m[1], 16) for m in ADDRESS.finditer(Path(path).stem)}
    # Read only changed ledger rows, never the complete ledger. These link
    # semantic filenames and functions whose source carries no address token.
    delta = ledger_diff(root, old, new)
    for line in delta.splitlines():
        if not line.startswith(('+', '-')) or line.startswith(('+++', '---')):
            continue
        row = next(csv.reader([line[1:]]), [])
        if len(row) < 6 or not source(row[4]):
            continue
        try:
            rva = int(row[2], 16)
        except ValueError:
            continue
        path = row[4]
        ids.setdefault(path, set()).add(rva)
        ref, dest = (new, right) if line[0] == '+' else (old, left)
        text = snapshot(ref, path)
        if text is not None:
            dest[path] = text
    # A bank may remain in place while a conversion is prepared. Compare it
    # too; deletion and git's rename similarity heuristic are not prerequisites.
    old_banks = set(git(root, 'ls-tree', '-r', '--name-only', old, '--',
                        'reverse/attempts/', 'targets/game/reverse/attempts/').splitlines())
    for path in list(right):
        for rva in ids.get(path, ()):
            bank = f'targets/game/reverse/attempts/0x{rva:08x}.cpp'
            old_bank = bank if bank in old_banks else 'reverse/' + bank[len('targets/game/reverse/') :]
            if old_bank not in old_banks:
                continue
            text = snapshot(old, old_bank)
            if text is not None:
                left[old_bank] = text
                ids.setdefault(old_bank, set()).add(rva)
    linked = {(p, p) for p in left.keys() & right.keys()}
    # Git-detected moves cover address-free files without a ledger edit.
    for status, names in changes:
        if status.startswith(('R', 'C')) and status not in ('R100', 'C100') and source(names[1]):
            before = snapshot(old, names[0])
            after = snapshot(new, names[1])
            if before is not None and after is not None:
                left[names[0]] = before
                right[names[1]] = after
                linked.add(tuple(names))
    by_rva = defaultdict(set)
    for path in right:
        for rva in ids.get(path, ()):
            by_rva[rva].add(path)
    for a in left:
        targets = {b for rva in ids.get(a, ()) for b in by_rva[rva] if a != b}
        if not targets:
            continue
        # Rehoming one row out of a retained game/ TU does not move its other
        # declarations. Comparing that unchanged whole source to the new file
        # invents unrelated renames; the same-RVA ledger check still runs.
        if a.startswith('game/') and snapshot(new, a) == left[a]:
            continue
        linked.update((a, b) for b in targets)
    return [(a, b, left[a], right[b]) for a, b in sorted(linked)]


def _symbol_names(symbol):
    """Extract plain method and immediate-owner names from an MSVC symbol."""
    if symbol.startswith(('??0', '??1')):
        owner = symbol[3:].split('@', 1)[0]
        return ('', owner if IDENT.fullmatch(owner) else '')
    if not symbol.startswith('?') or symbol.startswith('??') or '@@' not in symbol:
        return ()
    head = symbol[1:].split('@@', 1)[0].split('@')
    return tuple(part if IDENT.fullmatch(part) else '' for part in head[:2])


def ledger_symbol_regressions(root, old, new):
    """Catch a ledger-only rename of the same physical body."""
    delta = ledger_diff(root, old, new)
    removed, added = {}, {}
    for line in delta.splitlines():
        if not line.startswith(('+', '-')) or line.startswith(('+++', '---')):
            continue
        row = next(csv.reader([line[1:]]), [])
        if len(row) < 6:
            continue
        try:
            key = (int(row[2], 16), int(row[3]))
        except ValueError:
            continue
        (added if line[0] == '+' else removed).setdefault(key, []).append(
            (row[0], line[1:]))

    found = []
    for key in removed.keys() & added.keys():
        if len(removed[key]) != 1 or len(added[key]) != 1:
            continue  # A many-to-many ledger edit has no safe name pairing.
        old_symbol, before = removed[key][0]
        new_symbol, after = added[key][0]
        for old_name, new_name in zip(_symbol_names(old_symbol),
                                      _symbol_names(new_symbol)):
            if downgrade(old_name, new_name):
                found.append(Finding('targets/game/reverse/functions.csv',
                                     'targets/game/reverse/functions.csv', old_name, new_name,
                                     digest(before), digest(after)))
    return sorted(found, key=lambda f: (f.before_sha256, f.old_name, f.new_name))


@dataclass(frozen=True)
class Finding:
    old_path: str
    new_path: str
    old_name: str
    new_name: str
    before_sha256: str
    after_sha256: str


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


def check(root, old, new):
    raw = read(root, new, CORRECTIONS)
    corrections = json.loads(raw) if raw else []
    if not isinstance(corrections, list):
        raise ValueError(f'{CORRECTIONS} must contain a list')
    findings = []
    accepted = 0
    candidates = [
        Finding(a, b, x, y, digest(before), digest(after))
        for a, b, before, after in pairs(root, old, new)
        for x, y in regressions(before, after)
    ]
    candidates.extend(ledger_symbol_regressions(root, old, new))
    for finding in candidates:
        allowed = False
        for entry in corrections:
            if not isinstance(entry, dict):
                raise ValueError(f'{CORRECTIONS}: correction must be an object')
            if all(entry.get(k) == v for k, v in vars(finding).items()):
                evidence = entry.get('evidence', '')
                reason = entry.get('reason', '')
                # An exact, reviewable correction, not a count baseline or
                # reusable allowlist. Its evidence must exist in this snapshot.
                if (not isinstance(evidence, str) or not isinstance(reason, str)
                        or not evidence.startswith(('docs/', 'targets/game/reverse/'))
                        or '..' in Path(evidence).parts or not reason.strip()
                        or not (read(root, new, evidence) or '').strip()):
                    raise ValueError(f'{CORRECTIONS}: correction needs tracked evidence and a reason')
                allowed = True
                accepted += 1
                break
        if not allowed:
            findings.append(finding)
    return findings, accepted


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('old')
    parser.add_argument('new')
    args = parser.parse_args(argv)
    try:
        findings, accepted = check(ROOT, args.old, args.new)
    except (ValueError, subprocess.CalledProcessError) as exc:
        print(f'name_regression: {exc}')
        return 1
    for f in findings:
        print(f'  {f.old_path} -> {f.new_path}: {f.old_name} -> {f.new_name}')
    print(f'name_regression: {len(findings)} descriptive-to-placeholder regression(s), {accepted} documented correction(s)')
    if findings:
        print('Preserve the established name, or document an evidence-backed identity correction; see docs/naming_evidence.md.')
    return bool(findings)


if __name__ == '__main__':
    raise SystemExit(main())
