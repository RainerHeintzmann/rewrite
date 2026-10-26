"""Writes tex/rewrite/syntax.txt, the grammar of rewrite for the appendix of
the manual (tex/rewrite/readme.tex): the token and precedence declarations
and the rules of src/syn.y, without the C actions and comments.
Run it after changing the grammar:
    python tools/gen_syntax.py"""
import os
import re

here = os.path.dirname(os.path.abspath(__file__))
root = os.path.dirname(here)


def strip_actions(text):
    """text without { ... } actions, C comments and string/char literals in them"""
    out, depth, i = [], 0, 0
    while i < len(text):
        c = text[i]
        if text.startswith('/*', i):
            j = text.find('*/', i + 2)
            i = len(text) if j < 0 else j + 2
            continue
        if depth == 0 and c == "'" and i + 2 < len(text):	# a token like '{' or '\n'
            j = text.find("'", i + 1 + (text[i + 1] == '\\'))
            out.append(text[i:j + 1])
            i = j + 1
            continue
        if depth > 0 and c in '"\'':				# a literal inside an action
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            i = j + 1
            continue
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
        elif depth == 0:
            out.append(c)
        i += 1
    return ''.join(out)


def main():
    src = open(os.path.join(root, 'src', 'syn.y'), encoding='utf-8').read()
    head, rules = src.split('\n%%', 2)[:2]
    decls = [l.rstrip() for l in head.split('\n')
             if re.match(r'%(token|type|left|right|nonassoc)\b', l)]
    lines = []
    for l in strip_actions(rules).split('\n'):
        l = l.rstrip().rstrip(';').rstrip()
        if l.strip():
            lines.append(l.expandtabs(8))
    body = []
    for l in lines:			# a blank line before each rule
        part = re.sub(r'\s+', ' ', l.strip())
        if not l[0].isspace():
            if body:
                body.append('')
            body.append(part)
        elif part.startswith('|'):
            body.append('        ' + part)
        else:				# the continuation of an alternative
            body[-1] += ' ' + part
    wrapped = []			# declarations at most 80 characters wide
    for d in decls:
        words = d.split()
        line = words[0]
        for w in words[1:]:
            if len(line) + 1 + len(w) > 80:
                wrapped.append(line)
                line = '%-8s' % words[0] + ' ' + w
            else:
                line += ' ' + w
        wrapped.append(line)
    text = '\n'.join(wrapped) + '\n%%\n\n' + '\n'.join(body) + '\n\n%%\n'
    out = os.path.join(root, 'tex', 'rewrite', 'syntax.txt')
    open(out, 'w', encoding='utf-8', newline='\n').write(text)
    print('grammar written to', out)


if __name__ == '__main__':
    main()
