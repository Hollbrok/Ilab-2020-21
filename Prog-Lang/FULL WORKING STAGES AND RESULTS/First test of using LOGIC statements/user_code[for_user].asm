	push 1
	pop rax
	push 0
	push 2
	je :END_IF_0
	push 2
	pop rax

END_IF_0:

	push rax
	push 1
	add

	pop rax
	hlt