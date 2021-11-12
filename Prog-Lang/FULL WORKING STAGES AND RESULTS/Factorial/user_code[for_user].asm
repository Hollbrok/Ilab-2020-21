	push 10
	pop rax
	push 1
	pop rbx

START_WHILE_0:

	push 0
	push rax
	push 1
	sub

	je :END_WHILE_0
	push rbx
	push rax
	mul

	pop rbx
	push rax
	push 1
	sub

	pop rax
	jmp :START_WHILE_0


END_WHILE_0:

	push rbx
	print
	hlt