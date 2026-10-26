SORT real
REALNUM real

PAT A : real
PAT B : real
PAT C : real
PAT X : real
PAT Y : real
PAT Z : real
NUMPAT N : real
NUMPAT M : real

SYM x : real
SYM y : real
SYM z : real
SYM a : real
SYM b : real
SYM c : real

FUNC +     : real,real >> real LA2		ATT  2
FUNC *     : real,real >> real LA3		ATT  4

DEBUG 5

ALG Real
SPEC 	      Real : 0+X   = X         # special constants
ADDSPEC     Real : 0*X   = 0
ADDSPEC     Real : X*mi X  = 1
ADDSPEC     Real : mi X*X  = 1
