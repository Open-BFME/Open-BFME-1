#!/usr/bin/env python3
"""Preserve descriptive names across edits and bank-to-source conversions.

Usage: name_regression.py OLD NEW (NEW may be ':' for the index).
Unlike name_oracle, this compares history, not the witness's class-name key.
It checks explicit identifier substitutions and unambiguous, computable layouts;
it does not infer semantic identity from a successful byte match.
"""
import argparse
import csv
import difflib
import hashlib
import json
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

import name_oracle as oracle

ROOT = Path(__file__).resolve().parents[1]
CORRECTIONS = 'reverse/name_corrections.json'
SOURCE = ('.cpp', '.cc', '.cxx', '.c', '.h', '.hh', '.hpp', '.hxx')
TOKEN = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|0[xX][0-9a-fA-F]+|\d+|[^\s]', re.S)
IDENT = re.compile(r'^[A-Za-z_]\w*$')
OPAQUE = re.compile(r'^(?:Rva[0-9a-f]{8}|(?:d|dup|j|sub|FUN|Gen_t)_[0-9a-f]{8}|(?:rva|func|fn)_?[0-9a-f]{8})', re.I)
KEYWORDS = set('void bool char short int long float double signed unsigned const volatile static extern class struct public private protected return true false nullptr typedef typename auto Bool Byte Short UnsignedByte UnsignedShort WideChar Int UnsignedInt UnsignedInt32 Real Int64 UnsignedInt64'.split())
ADDRESS = re.compile(r'(?:rva|0x|(?:^|_)\s*)([0-9a-f]{8})(?![0-9a-f])', re.I)


# Unlike the witness oracle's broad work-queue heuristic, a historical gate
# must not classify m_fieldOfView or m_reservedCapacity as unnamed storage.
FIELD_OPAQUE = re.compile(
    r"^m_(?:(?:unk(?:nown)?|unmodelled|field|pad(?:ding)?|slack|slot|reserved|unused|opaque)"
    r"(?:_?(?:0x)?[0-9a-fA-F]+)?"
    r"|(?:bfme)?(?:dword|word|byte|bool|int|float|short|ptr|hash|string|str|val|value)"
    r"(?:_?(?:0x)?[0-9][0-9a-fA-F]*)?"
    r"|(?:at|f|bfme)(?:0x)?[0-9][0-9a-fA-F]*"
    r"|(?:0x)?[0-9][0-9a-fA-F]*)$"
)


def opaque(name):
    return bool(OPAQUE.match(name) or FIELD_OPAQUE.fullmatch(name))


def downgrade(old, new):
    return old != new and bool(IDENT.fullmatch(old)) and old not in KEYWORDS and not opaque(old) and opaque(new)


def tokens(text):
    return [t for t in TOKEN.findall(text) if not t.startswith(('//', '/*', '"', "'"))]


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
                if downgrade(x, y) and not moved_type and not compiler_attribute:
                    found.add((x, y))
    left, right = layouts(before), layouts(after)
    for owner, members in left.items():
        if owner in right:
            candidates = [owner]
        else:
            shape = {off: value[1:] for off, value in members.items()}
            candidates = [name for name, fields in right.items()
                          if {off: value[1:] for off, value in fields.items()} == shape]
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


def diff_args(old, new):
    return ['--cached', old] if new == ':' else [old, new]


def source(path):
    return path.startswith(('Code/', 'reference/shims/', 'reverse/attempts/')) and path.endswith(SOURCE)


def pairs(root, old, new):
    args = diff_args(old, new)
    paths = git(root, 'diff', '--name-only', '-z', '--no-renames', *args).split('\0')
    left, right = {}, {}
    ids = {}
    for path in paths:
        if not source(path):
            continue
        for ref, dest in ((old, left), (new, right)):
            text = read(root, ref, path)
            if text is not None:
                dest[path] = text
        ids[path] = {int(m[1], 16) for m in ADDRESS.finditer(Path(path).stem)}
    # Read only changed ledger rows, never the complete ledger. These link
    # semantic filenames and functions whose source carries no address token.
    delta = git(root, 'diff', '--unified=0', '--no-renames', *args, '--', 'reverse/functions.csv')
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
        text = read(root, ref, path)
        if text is not None:
            dest[path] = text
    # A bank may remain in place while a conversion is prepared. Compare it
    # too; deletion and git's rename similarity heuristic are not prerequisites.
    for path in list(right):
        for rva in ids.get(path, ()):
            bank = f'reverse/attempts/0x{rva:08x}.cpp'
            text = read(root, old, bank)
            if text is not None:
                left[bank] = text
                ids.setdefault(bank, set()).add(rva)
    linked = {(p, p) for p in left.keys() & right.keys()}
    # Git-detected moves cover address-free files without a ledger edit.
    moved = git(root, 'diff', '--name-status', '-z', '-M', *args).split('\0')
    i = 0
    while i < len(moved) and moved[i]:
        status = moved[i]; i += 1
        count = 2 if status.startswith(('R', 'C')) else 1
        names = moved[i:i + count]; i += count
        if count == 2 and names[0] in left and names[1] in right:
            linked.add(tuple(names))
    linked.update((a, b) for a in left for b in right
                  if a != b and ids.get(a, set()) & ids.get(b, set()))
    return [(a, b, left[a], right[b]) for a, b in sorted(linked)]


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
    for a, b, before, after in pairs(root, old, new):
        for x, y in regressions(before, after):
            finding = Finding(a, b, x, y, digest(before), digest(after))
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
                            or not evidence.startswith(('docs/', 'reverse/'))
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
