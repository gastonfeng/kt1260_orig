/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

// RESOURCE RESOURCE1

extern unsigned long long common_ticktime__;

#include "accessor.h"
#include "POUS.h"

#include "config.h"
__DECLARE_GLOBAL(BOOL,RESOURCE1,X0)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X1)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X2)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X3)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X4)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X5)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X6)
__DECLARE_GLOBAL(BOOL,RESOURCE1,X7)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y0)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y1)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y2)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y3)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y4)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y5)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y6)
__DECLARE_GLOBAL(BOOL,RESOURCE1,Y7)

BOOL TASK0;
PROGRAM0 RESOURCE1__INSTANCE0;
#define INSTANCE0 RESOURCE1__INSTANCE0

void RESOURCE1_init__(void) {
  BOOL retain;
  retain = 0;
  __INIT_GLOBAL(BOOL,X0,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X1,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X2,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X3,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X4,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X5,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X6,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,X7,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y0,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y1,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y2,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y3,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y4,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y5,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y6,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,Y7,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  TASK0 = __BOOL_LITERAL(FALSE);
  PROGRAM0_init__(&INSTANCE0,retain);
}

void RESOURCE1_run__(unsigned long tick) {
  TASK0 = !(tick % 1);
  if (TASK0) {
    PROGRAM0_body__(&INSTANCE0);
  }
}

