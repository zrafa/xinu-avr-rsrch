/* avr specific values. Original saved under orig/ folder */

/* in file bufinit.c */
extern	status	bufinit(void);

/* in file intr.c */
extern	intmask	disable(void);
extern	void	enable(void);
extern	void	restore(intmask);

/* in file chprio.c */
extern	pri16	chprio(pid32, pri16);

/* in file clkhandler.c */
extern	inline void clkhandler(void);

/* in file clkinit.c */
extern	void	clkinit(void);

/* in file create.c */
extern	pid32	create(int (*procaddr)(), int, int, char *, int, ...);

/* in file ctxsw.S */
extern	void	ctxsw(void *, void *);

/* in file freebuf.c */
extern	syscall	freebuf(char *);

/* in file freemem.c */
extern	syscall	freemem(char *, uint32);

/* in file getbuf.c */
extern	char	*getbuf(bpid32);

/* in file getitem.c */
extern	pid32	getfirst(qid16);
extern	pid32	getlast(qid16);
extern	pid32	getitem(pid32);

/* in file getmem.c */
extern	char	*getmem(uint32);

/* in file getpid.c */
extern	pid32	getpid(void);

/* in file getprio.c */
extern	syscall	getprio(pid32);

/* in file getstk.c */
extern	char	*getstk(uint32);

/* in file halt.S */
extern	void	halt(void);

/* in file insert.c */
// extern	status	insert(pid32, qid16, int32);
extern	status	insert(pid32, qid16, char);

/* in file insertd.c */
// extern	status	insertd(pid32, qid16, int32);
extern	status	insertd(pid32, qid16, int16);

/* in file kill.c */
extern	syscall	kill(pid32);

/* in file mark.c */
extern	void	_mkinit(void);

/* in file memcpy.c */
extern	void	*memcpy(void *, const void *, int32);

/* in file memcmp.c */
extern	int32	*memcmp(void *, const void *, int32);

/* in file memset.c */
extern  void    *memset(void *, const int, int32);

/* in file mkbufpool.c */
extern	bpid32	mkbufpool(int32, int32);

/* in file newqueue.c */
extern	qid16	newqueue(void);

/* in file panic.c */
extern	void	panic(char *);

/* in file platinit.c */
extern	void	platinit(void);

/* in file ptcount.c */
extern	int32	ptcount(int32);

/* in file ptcreate.c */
extern	syscall	ptcreate(int32);

/* in file ptdelete.c */
extern	syscall	ptdelete(int32, int32 (*)(int32));

/* in file ptinit.c */
extern	syscall	ptinit(int32);

/* in file ptrecv.c */
extern	uint32	ptrecv(int32);

/* in file ptreset.c */
extern	syscall	ptreset(int32, int32 (*)(int32));

/* in file ptsend.c */
extern	syscall	ptsend(int32, umsg32);

/* in file queue.c */
extern	pid32	enqueue(pid32, qid16);
extern	pid32	dequeue(qid16);

/* in file ready.c */
extern	status	ready(pid32);

/* in file receive.c */
extern	umsg32	receive(void);

/* in file recvclr.c */
extern	umsg32	recvclr(void);

/* in file recvtime.c */
extern	umsg32	recvtime(int32);

/* in file resched.c */
extern	void	resched(void);
extern	status	resched_cntl(int32);

/* in file resume.c */
extern	pri16	resume(pid32);

/* in file semcount.c */
extern	syscall	semcount(sid32);

/* in file semcreate.c */
extern	sid32	semcreate(int32);

/* in file semdelete.c */
extern	syscall	semdelete(sid32);

/* in file semreset.c */
extern	syscall	semreset(sid32, int32);

/* in file send.c */
extern	syscall	send(pid32, umsg32);

/* in file signal.c */
extern	syscall	signal(sid32);

/* in file signaln.c */
extern	syscall	signaln(sid32, int32);

/* in file sleep.c */
extern	syscall	sleepms(int32);
extern	syscall	sleep(int32);

/* in file suspend.c */
extern	syscall	suspend(pid32);

/* in file unsleep.c */
extern	syscall	unsleep(pid32);

/* in file userret.c */
extern	void	userret(void);

/* in file wait.c */
extern	syscall	wait(sid32);

/* in file wakeup.c */
extern	void	wakeup(void);

/* in file xdone.c */
extern	void	xdone(void);

/* in file yield.c */
extern	syscall	yield(void);

typedef unsigned int size_t;
#define hibyte(x) (unsigned char)(((int)(x)>>8)&0xff)
#define lobyte(x) (unsigned char)(((int)(x))&0xff)

