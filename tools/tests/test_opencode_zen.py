"""Zen catalog registration must not introduce paid fallback."""
import json
import io
from contextlib import redirect_stdout, redirect_stderr
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import opencode_router as r


class ZenTests(unittest.TestCase):
    def setUp(self):
        self.c=r.config(r.DEFAULT_CONFIG)
        self.zen=next(m for m in self.c['models'] if m['id']=='opencode/space-bunny-free')
        self.job=dict(tier='bulk',category='bulk',model=self.zen['id'],budget_justification='')

    def test_catalog_registration_and_paid_disabled(self):
        zen=[m for m in self.c['models'] if m['id'].startswith('opencode/')]
        self.assertEqual(len(zen),82)
        self.assertEqual([m['id'] for m in zen if m['enabled']],[self.zen['id']])
        self.assertEqual(self.zen['variants'],['low','medium','high','xhigh','max'])
        self.assertFalse(self.zen['metered'])

    def test_zero_prices_require_all_explicit_cost_bands(self):
        self.assertTrue(r.zero_catalog_cost([dict(input=0,output=0,cache=dict(read=0,write=0))]))
        for data in (None,[],[{}],[dict(input=0,output=0)],[dict(input=0)],[dict(input=False,output=0)],
                     [dict(input=0,output=1)],[dict(input=0,output=0,cache=dict(read=1))],
                     [dict(input=0,output=0),dict(input=1,output=1)]):
            self.assertFalse(r.zero_catalog_cost(data))

    def test_live_catalog_required_even_with_variant_discovery_disabled(self):
        self.c['variant_discovery']=False
        def catalog(argv,**kwargs):
            kwargs['stdout'].write(json.dumps({'data':[dict(id='space-bunny-free',providerID='opencode',enabled=True,
                cost=[dict(input=0,output=0,cache=dict(read=0,write=0))],variants=[dict(id=v) for v in self.zen['variants']])]}))
        with patch.object(r.subprocess,'run',side_effect=catalog):
            caps=r.discover_variants(self.c,r.ROOT)
        self.assertEqual(caps[self.zen['id']],self.zen['variants'])
        exhausted=dict(pacing_mode='exhausted',max_metered_workers=1)
        self.assertEqual(r.choose(self.c,self.job,{}, {},[],0,exhausted),self.zen)
        with patch.object(r.subprocess,'run',side_effect=OSError('offline')):
            r.discover_variants(self.c,r.ROOT)
        self.assertIsNone(r.choose(self.c,self.job,{}, {},[],0,exhausted))

    def test_paid_zen_cannot_be_enabled(self):
        paid=next(m for m in self.c['models'] if m['id'].startswith('opencode/') and m['metered'])
        paid['enabled']=True
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'config.json';p.write_text(json.dumps(self.c))
            with self.assertRaisesRegex(ValueError,'paid or unverified'):r.config(p)

    def test_all_explicit_variants_share_one_model_capacity(self):
        self.c['_verified_free_zen']=[self.zen['id']]
        for variant in self.zen['variants']:
            self.job['model']=self.zen['id']+'#'+variant
            self.assertEqual(r.choose(self.c,self.job,{}, {},[],0),self.zen)
            self.assertIsNone(r.choose(self.c,self.job,{self.zen['id']:1}, {},[],0))
        with tempfile.TemporaryDirectory() as tmp:
            with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
                for variant in self.zen['variants']:
                    self.assertEqual(r.main(['--state',tmp,'submit','bulk','check '+variant,
                        '--model',self.zen['id']+'#'+variant]),0)
                with self.assertRaises(SystemExit):
                    r.main(['--state',tmp,'submit','bulk','invalid','--model',self.zen['id']+'#invented'])

    def test_worker_allows_only_selected_provider(self):
        for mid,provider in ((self.zen['id'],'opencode'),('opencode-go/gpt-6-luna','opencode-go')):
            e=r.worker_env(mid,Path.cwd())
            rules=json.loads(e['OPENCODE_CONFIG_CONTENT'])['experimental']['policies']
            allowed=[p['resource'] for p in rules if p['action']=='provider.use' and p['effect']=='allow']
            self.assertEqual(allowed,[provider])

    def test_zen_quota_does_not_latch_go_account(self):
        with tempfile.TemporaryDirectory() as tmp:
            state=Path(tmp)
            job=r.enqueue(state,'bulk','fixture')
            with r.database(state) as db:
                db.execute("INSERT INTO attempts(id,job,model,status,started) VALUES('z',?,?,'running',1000)",(job,self.zen['id']))
            r.finish(state,self.c,'z',{'kind':'quota'},1001)
            self.assertFalse(r.budget_snapshot(state,self.c)['exhausted'])

if __name__=='__main__':unittest.main()
