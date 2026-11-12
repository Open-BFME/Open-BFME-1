"""Read-only evidence checks; normal build.sh remains the source admission gate."""
import argparse
import importlib.util
import json
from pathlib import Path
import random
import re
import unittest

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def load(name):
    spec = importlib.util.spec_from_file_location(name, HERE / (name + '.py'))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


recover = load('recover')
emit = load('emit')


class PartitionTests(unittest.TestCase):
    def test_signed_unsigned_wrap_and_equality_partitions(self):
        rng = random.Random(20261112)
        offsets = [0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF]
        jumps = ['je', 'jne', 'jg', 'jge', 'jl', 'jle', 'ja', 'jae', 'jb', 'jbe', 'jns', 'js']
        for _ in range(500):
            a = (rng.randrange(2), rng.choice(offsets) if rng.randrange(2) else rng.getrandbits(32))
            b = (rng.randrange(2), rng.choice(offsets) if rng.randrange(2) else rng.getrandbits(32))
            for jump in jumps:
                yes, no = recover.partition([(0, recover.MOD)], a, b, jump)
                spans = sorted(yes + no)
                end = 0
                for lo, hi in spans:
                    self.assertEqual(lo, end)
                    self.assertLess(lo, hi)
                    end = hi
                self.assertEqual(end, recover.MOD)
                points = {0, recover.MASK, *(rng.getrandbits(32) for _ in range(4))}
                for expr in (a, b):
                    for crossing in (0, 0x80000000):
                        for delta in (-1, 0, 1):
                            points.add((crossing - expr[1] + delta) & recover.MASK)
                for x in points:
                    l, r = recover.ev(a, x), recover.ev(b, x)
                    sl, sr = recover.signed(l), recover.signed(r)
                    expected = {'je': l == r, 'jne': l != r, 'jg': sl > sr,
                                'jge': sl >= sr, 'jl': sl < sr, 'jle': sl <= sr,
                                'ja': l > r, 'jae': l >= r, 'jb': l < r, 'jbe': l <= r,
                                'jns': sl >= 0, 'js': sl < 0}[jump]
                    self.assertEqual(any(lo <= x < hi for lo, hi in yes), expected,
                                     (a, b, jump, hex(x)))


class SourceEvidenceTests(unittest.TestCase):
    def test_independent_case_and_literal_mapping(self):
        for suffix in ('stringa', 'stringw', 'descriptiona', 'descriptionw'):
            with self.subTest(suffix=suffix):
                data = json.loads((EVIDENCE / ('dxerr-' + suffix + '.json')).read_text())
                self.assertEqual(data['covered_inputs'], 1 << 32)
                expected = {case['hr']: case['value'] for case in data['cases']}
                text = (ROOT / 'game/Libraries/Source/DirectX' / ('dxerr' + suffix + '.cpp')).read_text()
                actual, pending, default = {}, [], None
                for line in text.splitlines():
                    match = re.search(r'case (0x[0-9A-F]+):', line)
                    if match:
                        pending.append(int(match[1], 16))
                    match = re.search(r'return L?(".*");', line)
                    if not match:
                        continue
                    literal = json.loads(match[1])
                    if 'default:' in line:
                        self.assertFalse(pending)
                        default = literal
                    else:
                        self.assertTrue(pending)
                        for value in pending:
                            self.assertNotIn(value, actual)
                            actual[value] = literal
                        pending = []
                self.assertFalse(pending)
                self.assertEqual(actual, expected)
                self.assertEqual(default, data['default'])

    def test_candidate_reproduction(self):
        for suffix in ('stringa', 'stringw', 'descriptiona', 'descriptionw'):
            with self.subTest(suffix=suffix):
                order = 'origin' if suffix.startswith('string') else 'donor'
                expected = emit.source(suffix, '/O1 /G6 /MT /DNDEBUG', order, EVIDENCE)
                actual = (ROOT / 'game/Libraries/Source/DirectX' / ('dxerr' + suffix + '.cpp')).read_text()
                actual = '// cl:' + actual.split('// cl:', 1)[1]
                self.assertEqual(actual, expected)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-dir', type=Path, required=True)
    args = parser.parse_args()
    EVIDENCE = args.evidence_dir
    unittest.main(argv=['test_recovery.py'], verbosity=2)
