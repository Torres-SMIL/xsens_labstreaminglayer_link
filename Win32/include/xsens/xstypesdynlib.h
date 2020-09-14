#ifndef XSTYPESDYNLIB_H
#define XSTYPESDYNLIB_H

#include "xstypesconfig.h"

struct XsString;

#ifdef __cplusplus
extern "C" {
#endif

XSTYPES_DLL_API void xstypesPath(struct XsString* path);

#ifdef __cplusplus
}
#endif

#endif
