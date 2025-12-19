#ifndef BONE_H
#define BONE_H

#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
#define CPU_ARCH "x86-64");
#elif defined(i386) || defined(__i386__) || defined(_M_IX86)
#define CPU_ARCH "x86");
#elif defined(__aarch64__)
#define CPU_ARCH "AArch64");
#elif defined(__arm__)
#define CPU_ARCH "ARM");
#elif defined(__ppc__) || defined(__PPC__)
#define CPU_ARCH "PowerPC");
#elif defined(__mips64)
#define CPU_ARCH "mips64");
#elif defined(__mips__)
#define CPU_ARCH "mips");
#else
printf("Target architecture: Unknown/Generic\n");
#endif

void logo(void);
void user(void);
void host(void);
void os(void);
void kernel(void);
void packages(void);
void shell(void);
void termical(void);
void cpu(void);
void gpu(void);
void memory(void);
void swap(void);
void disk(void);
void ip(void);
void net_interfacw(void);
void locale(void);
void colors(void);

#endif // !BONE_H
