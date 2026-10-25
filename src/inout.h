#ifndef	INOUT_H
#define	INOUT_H

/*
 *	inout.h  V1.00
 *
 *	Copyright (c)  Rainer Heintzmann 	(1992)
 *
 *	Interface for input/output
 */

extern int changeOut(const char * filename); /* "stdout" -> stdout */

extern int printfOut(const char * format,...);
extern void out_capture_begin (void);	/* 2026: printfOut into a string */
extern char * out_capture_end (void);

extern int printfErr(const char * format,...);

extern int printfDebug(int pri,const char * format,...);

extern int changeData(const char * filename);

extern double readData (void);

extern int mustDebug(int pri);

extern void setDebug(int pri);

#ifdef DEBUG
#define DEBG(x) printfDebug x
#define DBFN(pri,funct) if (mustDebug(pri)) funct
#else
#define DEBG(x)    
#define DBFN(pri,funct)    
#endif

#endif
