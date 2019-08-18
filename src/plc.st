TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


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
