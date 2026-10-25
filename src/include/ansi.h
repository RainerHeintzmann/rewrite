#ifndef	_ANSI_H
#define	_ANSI_H
/*
 *	ansi.h -- 1.1 Jan 27 06:53:27 1991
 *	Copyright (c) 1991 Axel T. Schreiner
 *
 *	ANSI / K&R compatibility
 */

#ifdef	__STDC__			/* ANSI style */

#include <stdarg.h>

#define	va_beg(a, b, c)			va_start(a, c)

#define	_va(a,b)			(a, ...) {
#define	_vp(a,b)			(a, ...)
#define	_0a(a)				(a)
#define	_0p(a)				(a)
#define	_1a(l,a)			(a)
#define	_1p(a)				(a)
#define	_2a(l,a,b)			(a, b)
#define	_2p(a,b)			(a, b)
#define	_3a(l,a,b,c)			(a, b, c)
#define	_3p(a,b,c)			(a, b, c)
#define	_4a(l,a,b,c,d)			(a, b, c, d)
#define	_4p(a,b,c,d)			(a, b, c, d)
#define	_5a(l,a,b,c,d,e)		(a, b, c, d, e)
#define	_5p(a,b,c,d,e)			(a, b, c, d, e)
#define	_6a(l,a,b,c,d,e,f)		(a, b, c, d, e, f)
#define	_6p(a,b,c,d,e,f)		(a, b, c, d, e, f)
#define	_7a(l,a,b,c,d,e,f,g)		(a, b, c, d, e, f, g)
#define	_7p(a,b,c,d,e,f,g)		(a, b, c, d, e, f, g)
#define	_8a(l,a,b,c,d,e,f,g,h)		(a, b, c, d, e, f, g, h)
#define	_8p(a,b,c,d,e,f,g,h)		(a, b, c, d, e, f, g, h)
#define	_9a(l,a,b,c,d,e,f,g,h,i)	(a, b, c, d, e, f, g, h, i)
#define	_9p(a,b,c,d,e,f,g,h,i)		(a, b, c, d, e, f, g, h, i)

#else					/* K&R style */

#define	const				/* empty */

#include <varargs.h>

#define	va_beg(a, b, c)			va_start(a), c = va_arg(a, b)

#define	_va(a,b)			(va_alist)	\
						va_dcl	\
					{	a;
#define	_vp(a,b)			()
#define	_0a(a)				()
#define	_0p(a)				()
#define	_1a(l,a)			l a;
#define	_1p(a)				()
#define	_2a(l,a,b)			l a; b;
#define	_2p(a,b)			()
#define	_3a(l,a,b,c)			l a; b; c;
#define	_3p(a,b,c)			()
#define	_4a(l,a,b,c,d)			l a; b; c; d;
#define	_4p(a,b,c,d)			()
#define	_5a(l,a,b,c,d,e)		l a; b; c; d; e;
#define	_5p(a,b,c,d,e)			()
#define	_6a(l,a,b,c,d,e,f)		l a; b; c; d; e; f;
#define	_6p(a,b,c,d,e,f)		()
#define	_7a(l,a,b,c,d,e,f,g)		l a; b; c; d; e; f; g;
#define	_7p(a,b,c,d,e,f,g)		()
#define	_8a(l,a,b,c,d,e,f,g,h)		l a; b; c; d; e; f; g; h;
#define	_8p(a,b,c,d,e,f,g,h)		()
#define	_9a(l,a,b,c,d,e,f,g,h,i)	l a; b; c; d; e; f; g; h; i;
#define	_9p(a,b,c,d,e,f,g,h,i)		()

#endif
#endif
