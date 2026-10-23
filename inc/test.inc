SORT real
NUM real

VAR A : real
VAR B : real
VAR C : real
VAR X : real
VAR Y : real
VAR Z : real
NUM N : real
NUM M : real

CONST x : real
CONST y : real
CONST z : real
CONST a : real
CONST b : real
CONST c : real

FUNC +     : real,real >> real LA2		ATT  2
FUNC *     : real,real >> real LA3		ATT  4

DEBUG 5

ALG Real
SPEC 	      Real : 0+X   = X         # spezielle Konstanten
ADDSPEC     Real : 0*X   = 0
ADDSPEC     Real : X*mi X  = 1
ADDSPEC     Real : mi X*X  = 1
