"""Writes tools/rewrite_words.txt, the completion word list of
tools/rewrite-rl (rlwrap -f):
 - the keywords of rewrite (from the keyword table in src/sym.c),
 - the functions, sorts and rule sets (FUNC, OTHER, BRA, SORT, ALG) of the
   libraries in use: the files loaded by inc/all (following INC) and the
   optional ones in OPTIONAL; of the integration only its entry points,
 - the LaTeX-like names (\\alpha, from tools/latex_symbols.tsv).
Internal names (beginning with _, the steps of the solvers and the
integration helpers) are left out. Run it after changing the libraries:
    python tools/gen_words.py"""
import os, re
here = os.path.dirname(os.path.abspath(__file__))
root = os.path.dirname(here)

OPTIONAL = ['inc/list', 'inc/linalg', 'inc/solve', 'inc/rvector', 'inc/rmatrix']
# libraries of internal helpers: only these names of them are offered
ENTRY_ONLY = {'inc/helpers': set(),
              'inc/integration': {'Int', 'Integrate', 'RubiIntegrate'}}
# internal steps of inc/solve and inc/linalg
INTERNAL = re.compile(r'^(sol|solker|solcheck|solfilter|iso|isom|isomap|isoeach|ker|kernel|kernelq|'
                      r'union|attract|attractq|unradical|radicalq|eqnorm|nroots|occurs|linsys|linsysq|'
                      r'sys\w*|yker|mfreeq|sortleq|threadq|Covec)$')

words = set()
kind = {}                    # for the colours of tools/latex.rlwrap
for m in re.finditer(r'\{\s*"([A-Z][A-Z0-9]*)",', open(os.path.join(root, 'src', 'sym.c'), encoding='utf-8').read()):
    words.add(m.group(1))
    kind[m.group(1)] = 'keyword'
sort_decl = re.compile(r'^\s*SORT\s+([^:#]*)')

# rule sets: only those the README uses (REWR ... : Name), the others are
# internal steps of the library (AddFront, Mulord, ...)
readme = open(os.path.join(root, 'README.md'), encoding='utf-8').read()
DOC_ALGS = set()
for m in re.finditer(r'REWR [^#\n]*:\s*\(?([A-Za-z][\w, ()]*)', readme):
    DOC_ALGS.update(w for w in re.split(r'[\s,()]+', m.group(1)) if w)
alg_decl = re.compile(r'^\s*ALG\s+([^:#]*)')

decl = re.compile(r'^\s*(?:FUNC|OTHER|BRA|SORT|ALG)\s+([^:#]*)')
inc = re.compile(r'^\s*INC\s+"([^"]+)"')
seen = set()

def scan(name):
    """the declarations of a library file and of the files it loads"""
    if name in seen or not os.path.isfile(os.path.join(root, name)):
        return
    seen.add(name)
    allowed = None
    for prefix, entry in ENTRY_ONLY.items():
        if name == prefix or name.startswith(prefix + '/'):
            allowed = entry
    for line in open(os.path.join(root, name), encoding='utf-8', errors='replace'):
        m = inc.match(line)
        if m:
            scan(m.group(1))
            continue
        m = decl.match(line)
        if not m:
            continue
        is_alg = alg_decl.match(line) is not None
        if sort_decl.match(line):
            for w in re.split(r'[\s,]+', m.group(1)):
                if re.fullmatch(r'[A-Za-z]\w*', w):
                    kind[w] = 'sort'
        for w in re.split(r'[\s,]+', m.group(1)):
            if not re.fullmatch(r'[A-Za-z][A-Za-z0-9]*', w) or len(w) < 2:   # no _: internal
                continue
            if is_alg and w not in DOC_ALGS:
                continue
            if allowed is not None and w not in allowed:
                continue
            if INTERNAL.match(w):
                continue
            words.add(w)

for name in ['inc/all'] + OPTIONAL:
    scan(name)

for line in open(os.path.join(here, 'latex_symbols.tsv'), encoding='utf-8'):
    words.add(line.split('\t', 1)[0])

out = os.path.join(here, 'rewrite_words.txt')
with open(out, 'w', encoding='utf-8', newline='\n') as f:
    for w in sorted(words):
        f.write(w + '\n')
n = sum(1 for w in words if not w.startswith('\\'))
print(len(words), 'words written to', out, '(%d without the \\ names)' % n)

# keywords and sort names, coloured in the output by tools/latex.rlwrap
kinds = os.path.join(here, 'rewrite_kinds.tsv')
with open(kinds, 'w', encoding='utf-8', newline='\n') as f:
    for w in sorted(kind):
        f.write(w + '\t' + kind[w] + '\n')
print(len(kind), 'keywords and sorts written to', kinds)
