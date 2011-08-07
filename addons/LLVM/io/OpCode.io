LLVM OpCode := Object clone do(
  /* Terminator Instructions */
  ret := 1
  br := 2
  switch := 3
  indirectBr := 4
  invoke := 5
  unwind := 6
  unreachable := 7

  /* Standard Binary Operators */
  add := 8
  fAdd := 9
  sub := 10
  sSub := 11
  mul := 12
  fMul := 13
  uDiv := 14
  sDiv := 15
  fDiv := 16
  uRem := 17
  sRem := 18
  fRem := 19

  /* Logical Operators */
  shl := 20
  lShr := 21
  aShr := 22
  and := 23
  or := 24
  xor := 25

  /* Memory Operators */
  alloca := 26
  load := 27
  store := 28
  getElementPtr := 29

  /* Cast Operators */
  trunc := 30
  zExt := 31
  sExt := 32
  fpToUI := 33
  fpToSI := 34
  uiToFP := 35
  siToFP := 36
  fpTrunc := 37
  fpExt  := 38
  ptrToInt := 39
  intToPtr := 40
)