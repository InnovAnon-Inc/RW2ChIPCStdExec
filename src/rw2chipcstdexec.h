#ifndef _RW2CHIPCSTDEXEC_H_
#define _RW2CHIPCSTDEXEC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <rw2chipcstd.h>

typedef __attribute__ ((nonnull (1), warn_unused_result))
int (*bufparentcb_t) (char (*restrict buffer)[], size_t count, void *restrict) ;

int rw2chipcstdexec (
	char (*restrict dest)[], size_t destsz,
	char (*restrict src )[], size_t srcsz,
	char *(*restrict childcb_args)[],
	bufparentcb_t parentcb, void   *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _RW2CHIPCSTDEXEC_H_ */
