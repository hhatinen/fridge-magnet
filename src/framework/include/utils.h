#pragma once

#ifdef MIN
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
