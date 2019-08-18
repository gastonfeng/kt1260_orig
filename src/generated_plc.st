PROGRAM program0
  VAR_EXTERNAL
    X0 : BOOL;
    X1 : BOOL;
    X2 : BOOL;
    X3 : BOOL;
    X4 : BOOL;
    X5 : BOOL;
    X6 : BOOL;
    X7 : BOOL;
    Y0 : BOOL;
    Y1 : BOOL;
    Y2 : BOOL;
    Y3 : BOOL;
    Y4 : BOOL;
    Y5 : BOOL;
    Y6 : BOOL;
    Y7 : BOOL;
  END_VAR

  Y0 := X0;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    VAR_GLOBAL
      X0 : BOOL;
      X1 : BOOL;
      X2 : BOOL;
      X3 : BOOL;
      X4 : BOOL;
      X5 : BOOL;
      X6 : BOOL;
      X7 : BOOL;
      Y0 : BOOL;
      Y1 : BOOL;
      Y2 : BOOL;
      Y3 : BOOL;
      Y4 : BOOL;
      Y5 : BOOL;
      Y6 : BOOL;
      Y7 : BOOL;
    END_VAR
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
