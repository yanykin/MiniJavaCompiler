[Factorial$main]
CLABEL_1: 
	MOV T8, 0
	PUSH T8
	CALL malloc
	MOV T0, EAX
	MOV T9, 10
	PUSH T9
	PUSH T0
	CALL Factorial$ComputeFac
	MOV T1, EAX
	PUSH T1
	CALL System.out.println
	JUMP CLABEL_2
[Fac$ComputeFac]
CLABEL_4: 
	MOV T10, 1
	CMP T3, T10
	JGE CLABEL_7
	JUMP CLABEL_6
CLABEL_6: 
	MOV T11, 1
	MOV [T4], T11
	JUMP CLABEL_8
CLABEL_7: 
	MOV T7, T4
	MOV T6, T3
	MOV T13, 1
	MOV T12, T3
	SUB T12, T13
	PUSH T12
	PUSH T2
	CALL Fac$ComputeFac
	MOV T5, EAX
	MOV T14, T6
	IMUL T14, T5
	MOV [T7], T14
CLABEL_8: 
	MOV T15, T4
	JUMP CLABEL_5

