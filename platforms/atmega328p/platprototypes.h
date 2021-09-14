/* platprototypes.h */

/* in file start.S */
extern	void	start(void);

/* in file platinit.c */
extern	void	platinit(void);

/* in file intr.c */
extern	intmask	disable(void);
extern	void	enable(void);
extern	void	restore(intmask);
extern	void	halt(void);

/* in file ctxsw.S */
extern	void	ctxsw(void *, void *);


