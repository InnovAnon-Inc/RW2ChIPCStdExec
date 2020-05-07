#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>

#include <restart.h>

#include <rw2chipcstdexec.h>

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int mychildcb (void *restrict args) {
   char *(*restrict argv)[] = args;
   return execv ((*argv)[0], *argv);
}

typedef struct {
   bufparentcb_t  parentcb;
   void *restrict args;
   char (*restrict dest)[]; size_t destsz;
   char (*restrict src )[]; size_t srcsz;
} pargs_t;
 
__attribute__ ((nonnull (4), warn_unused_result))
static int myparentcb (pid_t cpid, fd_t rd, fd_t wr, void *restrict args) {
   pargs_t *restrict pargs           = args;
   bufparentcb_t     parentcb        = pargs->parentcb;
   void    *restrict parent_args     = pargs->args;
   char (*restrict dest)[] = pargs->dest;
   size_t destsz                     = pargs->destsz;
   char (*restrict src )[] = pargs->src;
   size_t srcsz                      = pargs->srcsz;

   size_t  totwr = 0;
   size_t  totrd = 0;

   /* TODO read/write fully */

   while (totwr != srcsz && totrd != destsz) {
      ssize_t cntwr, cntrd;

      /* Write to child’s stdin */
      cntwr = r_write (wr, &((*src)[totwr]), srcsz - totwr);
      error_check (cntwr == -1) return -1;
      if (cntwr != 0)

      /* Read from child’s stdout */
      cntrd = r_read (rd, &((*dest)[totrd]), destsz - totrd);
      error_check (cntrd == -1) return -2;

      totwr += (size_t) cntwr;
      totrd += (size_t) cntrd;
   }

   assert (dest     != NULL);
   assert (parentcb != NULL);
   return parentcb (dest, (size_t) totrd, parent_args);
}

__attribute__ ((nonnull (1, 3), warn_unused_result))
int rw2chipcstdexec (char (*restrict dest)[], size_t destsz,
                     char (*restrict src )[], size_t srcsz,
                     char *(*restrict cargs)[], bufparentcb_t parentcb, void *restrict pargs) {
   pargs_t parent_args;
   parent_args.dest     = dest;
   parent_args.destsz   = destsz;
   parent_args.src      = src;
   parent_args.srcsz    = srcsz;
   parent_args.args     = pargs;
   parent_args.parentcb = parentcb;
   return rw2chipcstd (mychildcb, cargs, myparentcb, &parent_args);
}

