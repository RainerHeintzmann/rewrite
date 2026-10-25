#ifndef DEFS_H
#define DEFS_H

/*
 *	defs.h V1.00
 *	Copyright (c) Rainer Heintzmann 1993
 *
 *	Function prototypes for parser run-time routines (definitions)
 */

extern void declare (Node * np);
extern void set_brackets (Node * np);
extern void other_fkt (Node * np);
extern void att_fkt (Node * np);
extern void att_sort (Node * np);
extern void spec (Node * np);
extern void a_spec_form (Node * np);
extern void spec_form (Node * np);
extern void block_begin(void);
extern void do_block_begin(Node * np);
extern void block_end(void);
extern void end_all_blocks(void);
extern void do_block_end(Node * np);
extern void clearBlockstufe (void);
extern void protect (void);
extern void no_protect (void);
extern Node * in_block_def(Node * np);
extern void return_fkt (Node * np);
extern Node * exe_function (Node * np);
extern Node * in_block_instruct (Node * np);
extern void is_running(void);
extern void is_not_running(void);
extern int  include_begin(void);
extern void include_end(int oldbase);

#endif
