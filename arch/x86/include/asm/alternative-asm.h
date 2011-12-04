#ifdef __ASSEMBLY__

#ifdef CONFIG_X86_32
# define X86_ALIGN .long
#else
# define X86_ALIGN .quad
#endif

#ifdef CONFIG_SMP
	.macro LOCK_PREFIX
1:	lock
	.section .smp_locks,"a"
	.align 4
	X86_ALIGN 1b
	.previous
	.endm
#else
	.macro LOCK_PREFIX
	.endm
#endif

#ifdef CONFIG_PAX_KERNEXEC_PLUGIN
	.macro pax_force_retaddr_bts rip=0
	btsq $63,\rip(%rsp)
	.endm
#ifdef CONFIG_PAX_KERNEXEC_PLUGIN_METHOD_BTS
	.macro pax_force_retaddr rip=0, reload=0
	btsq $63,\rip(%rsp)
	.endm
	.macro pax_force_fptr ptr
	btsq $63,\ptr
	.endm
	.macro pax_set_fptr_mask
	.endm
#endif
#ifdef CONFIG_PAX_KERNEXEC_PLUGIN_METHOD_OR
	.macro pax_force_retaddr rip=0, reload=0
	.if \reload
	pax_set_fptr_mask
	.endif
	orq %r10,\rip(%rsp)
	.endm
	.macro pax_force_fptr ptr
	orq %r10,\ptr
	.endm
	.macro pax_set_fptr_mask
	movabs $0x8000000000000000,%r10
	.endm
#endif
#else
	.macro pax_force_retaddr rip=0, reload=0
	.endm
	.macro pax_force_fptr ptr
	.endm
	.macro pax_force_retaddr_bts rip=0
	.endm
	.macro pax_set_fptr_mask
	.endm
#endif

#endif  /*  __ASSEMBLY__  */
