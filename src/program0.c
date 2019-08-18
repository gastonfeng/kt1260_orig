#include "program0.h"
#include "POUS.h"
void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_EXTERNAL(BOOL,X0,data__->X0,retain)
  __INIT_EXTERNAL(BOOL,X1,data__->X1,retain)
  __INIT_EXTERNAL(BOOL,X2,data__->X2,retain)
  __INIT_EXTERNAL(BOOL,X3,data__->X3,retain)
  __INIT_EXTERNAL(BOOL,X4,data__->X4,retain)
  __INIT_EXTERNAL(BOOL,X5,data__->X5,retain)
  __INIT_EXTERNAL(BOOL,X6,data__->X6,retain)
  __INIT_EXTERNAL(BOOL,X7,data__->X7,retain)
  __INIT_EXTERNAL(BOOL,Y0,data__->Y0,retain)
  __INIT_EXTERNAL(BOOL,Y1,data__->Y1,retain)
  __INIT_EXTERNAL(BOOL,Y2,data__->Y2,retain)
  __INIT_EXTERNAL(BOOL,Y3,data__->Y3,retain)
  __INIT_EXTERNAL(BOOL,Y4,data__->Y4,retain)
  __INIT_EXTERNAL(BOOL,Y5,data__->Y5,retain)
  __INIT_EXTERNAL(BOOL,Y6,data__->Y6,retain)
  __INIT_EXTERNAL(BOOL,Y7,data__->Y7,retain)
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_EXTERNAL(data__->,Y0,,__GET_EXTERNAL(data__->X0,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





