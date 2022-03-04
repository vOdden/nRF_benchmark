
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_HWINFO_H
#define Z_INCLUDE_SYSCALLS_HWINFO_H


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

extern ssize_t z_impl_hwinfo_get_device_id(uint8_t * buffer, size_t length);

__pinned_func
static inline ssize_t hwinfo_get_device_id(uint8_t * buffer, size_t length)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (ssize_t) arch_syscall_invoke2(*(uintptr_t *)&buffer, *(uintptr_t *)&length, K_SYSCALL_HWINFO_GET_DEVICE_ID);
	}
#endif
	compiler_barrier();
	return z_impl_hwinfo_get_device_id(buffer, length);
}


extern int z_impl_hwinfo_get_reset_cause(uint32_t * cause);

__pinned_func
static inline int hwinfo_get_reset_cause(uint32_t * cause)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&cause, K_SYSCALL_HWINFO_GET_RESET_CAUSE);
	}
#endif
	compiler_barrier();
	return z_impl_hwinfo_get_reset_cause(cause);
}


extern int z_impl_hwinfo_clear_reset_cause(void);

__pinned_func
static inline int hwinfo_clear_reset_cause(void)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke0(K_SYSCALL_HWINFO_CLEAR_RESET_CAUSE);
	}
#endif
	compiler_barrier();
	return z_impl_hwinfo_clear_reset_cause();
}


extern int z_impl_hwinfo_get_supported_reset_cause(uint32_t * supported);

__pinned_func
static inline int hwinfo_get_supported_reset_cause(uint32_t * supported)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (int) arch_syscall_invoke1(*(uintptr_t *)&supported, K_SYSCALL_HWINFO_GET_SUPPORTED_RESET_CAUSE);
	}
#endif
	compiler_barrier();
	return z_impl_hwinfo_get_supported_reset_cause(supported);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */