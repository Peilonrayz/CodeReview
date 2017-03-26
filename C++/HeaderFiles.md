# <a id="HeaderFiles"></a>Header Files

These are headers from the "C" language.  
You should note this is a completely different language.

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
There are C++ equivalent for these headers.

    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
Note most C headers `<HEAD.h>` have a C++ equivalent `<cHEAD>`.

By using the C++ version of these headers you put all the functionality they provide in the `std` namespace. If you use the C version of the header file the functionality be placed in the global namespace.

Here is a list of C headers that are deprecated in C++ in favor of the C++ version `<cHEAD>`:

    <assert.h>   <ctype.h>   <errno.h>  <fenv.h>   <float.h>  
    <inttypes.h> <limits.h>  <locale.h> <math.h>   <setjmp.h>   
    <signal.h>   <stdarg.h>  <stddef.h> <stdint.h> <stdio.h>    
    <stdlib.h>   <string.h>  <time.h>   <uchar.h>  <wchar.h>    
    <wctype.h>

**Note I**:  
Though the C version(s) of these headers must place the functionality in the global namespace, they may also optionally place the functionality in the `std` namespace. This can be an issue if your code uses the above files and `std::<type>` then it may compile on your compiler but will potentially fail on other compilers making your code less portable.

**Note II**:  
The following headers are not part of C++ at all.

    <stdatomic.h> <stdnoreturn.h> <threads.h>

This is because there functionality is superseded by alternative C++ functionality.

