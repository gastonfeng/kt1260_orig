#include "beremiz.h"
#ifndef __program0_H
#define __program0_H
#include "POUS.h"
// PROGRAM PROGRAM0
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,X0)
  __DECLARE_EXTERNAL(BOOL,X1)
  __DECLARE_EXTERNAL(BOOL,X2)
  __DECLARE_EXTERNAL(BOOL,X3)
  __DECLARE_EXTERNAL(BOOL,X4)
  __DECLARE_EXTERNAL(BOOL,X5)
  __DECLARE_EXTERNAL(BOOL,X6)
  __DECLARE_EXTERNAL(BOOL,X7)
  __DECLARE_EXTERNAL(BOOL,Y0)
  __DECLARE_EXTERNAL(BOOL,Y1)
  __DECLARE_EXTERNAL(BOOL,Y2)
  __DECLARE_EXTERNAL(BOOL,Y3)
  __DECLARE_EXTERNAL(BOOL,Y4)
  __DECLARE_EXTERNAL(BOOL,Y5)
  __DECLARE_EXTERNAL(BOOL,Y6)
  __DECLARE_EXTERNAL(BOOL,Y7)

} PROGRAM0;

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain);
// Code part
void PROGRAM0_body__(PROGRAM0 *data__);
#endif /* __program0_H */
