
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_LIBC_HOOKS_H
#define Z_INCLUDE_SYSCALLS_LIBC_HOOKS_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#include <linker/sections.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#if !defined(__XCC__)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_zephyr_read_stdin(char * buf, int nbytes);

__pinned_func
static inline int zephyr_read_stdin(char * buf, int nbytes)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&buf, *(uintptr_t *)&nbytes, K_SYSCALL_ZEPHYR_READ_STDIN);
	}
#endif
	compiler_barrier();
	return z_impl_zephyr_read_stdin(buf, nbytes);
}


extern int z_impl_zephyr_write_stdout(const void * buf, int nbytes);

__pinned_func
static inline int zephyr_write_stdout(const void * buf, int nbytes)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&buf, *(uintptr_t *)&nbytes, K_SYSCALL_ZEPHYR_WRITE_STDOUT);
	}
#endif
	compiler_barrier();
	return z_impl_zephyr_write_stdout(buf, nbytes);
}


extern int z_impl_zephyr_fputc(int c, FILE * stream);

__pinned_func
static inline int zephyr_fputc(int c, FILE * stream)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke2(*(uintptr_t *)&c, *(uintptr_t *)&stream, K_SYSCALL_ZEPHYR_FPUTC);
	}
#endif
	compiler_barrier();
	return z_impl_zephyr_fputc(c, stream);
}


extern size_t z_impl_zephyr_fwrite(const void *_MLIBC_RESTRICT ptr, size_t size, size_t nitems, FILE *_MLIBC_RESTRICT stream);

__pinned_func
static inline size_t zephyr_fwrite(const void *_MLIBC_RESTRICT ptr, size_t size, size_t nitems, FILE *_MLIBC_RESTRICT stream)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (size_t) arch_syscall_invoke4(*(uintptr_t *)&ptr, *(uintptr_t *)&size, *(uintptr_t *)&nitems, *(uintptr_t *)&stream, K_SYSCALL_ZEPHYR_FWRITE);
	}
#endif
	compiler_barrier();
	return z_impl_zephyr_fwrite(ptr, size, nitems, stream);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
