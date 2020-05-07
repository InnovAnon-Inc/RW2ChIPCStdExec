#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <stdio.h>

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

   ssize_t countwr = 0;
   ssize_t count = 0;

   /* TODO read/write fully */

   while ((size_t) countwr != srcsz || (count != countwr && destsz > (size_t) count)) {
   if ((size_t) countwr != srcsz) { 
   /* Write to child’s stdin */
   error_check (countwr = r_write (wr, (*src) + (size_t) countwr, srcsz - (size_t) countwr) == -1) return -1;
   if (countwr != 0)
   printf ("countwr: %d\n", (int) countwr);
   }

   if (count != countwr && destsz > (size_t) count) { 
   /* Read from child’s stdout */
   count = r_read (rd, (*dest) + (size_t) count, destsz - (size_t) count);
   error_check (count == -1) return -2;
   /*if (count >= 0) {
   buffer[count] = 0;
   printf("%s", buffer);
   } else {
   printf("IO Error\n");
   }*/
   }
   }

   assert (dest     != NULL);
   assert (parentcb != NULL);
   return parentcb (dest, (size_t) count, parent_args);
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

