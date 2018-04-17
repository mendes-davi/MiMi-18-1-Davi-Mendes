1. (a) Escreva uma função em C que calcule a raiz quadrada `x` de uma variável `S` do tipo float, utilizando o seguinte algoritmo: após `n+1` iterações, a raiz quadrada de `S` é dada por

```c
x(n+1) = (x(n) + S/x(n))/2
```

O protótipo da função é:

```C
unsigned int Raiz_Quadrada(unsigned int S);
```

```C
unsigned int Raiz_Quadrada(unsigned int S)
{
	int counter, x = 1; // x é o valor inicial para o problema
    if (S < 2)
    	return s;
    else
    {
        for(counter = 0; counter < 10; counter ++)
            x = (x + S/x)/2;
        return x;
    }
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável S é fornecida pelo registrador R15, e a raiz quadrada de S (ou seja, a variável x) é fornecida pelo registrador R15 também.

```assembly
Raiz_Quadrada: cmp #2,R15 ; compara se o valor de x**2 é 1 ou 0, evitando calculos
jge Raiz_Nao_Trivial
ret
Raiz_Nao_Trivial: push R5 ; guarda o valor de R5 na pilha
push R6 ; guarda R6 na pilha
mov R15, R5 ; R5 = s
inc R5 ; s+=1
rra R5 ; s = (s+1)/2
clr R6 ; limpa R6
Raiz_Loop: cmp #10000,R6 ; verifica se n é menor do que 10**4
jeq Raiz_End
push R15
mov R5,R14
call #Div ; implementar a sub-rotina de divisao
add R15,R5
rra R5
pop R15
inc R6
jump Raiz_Loop
Raiz_End: mov R5,R15
pop R6
pop R5
ret
```

2. (a) Escreva uma função em C que calcule `x` elevado à `N`-ésima potência, seguindo o seguinte protótipo: 

```C
int Potencia(int x, int N);
```

```C
int Multiplica(int a, int b)
{
    int res = 0;
    for (int i = 0; i < b; i++) // Laço de multiplicação
    {
        res += a;
    }
    return res;
}

int Potencia(int x, int N)
{
	int res = x;
    if(N == 1)
    	return x;
    else if(N == 0)
    	return 1;
    else
    {
	    for (int k = 0; k < N-1; k++)
		{
			res = Multiplica(res,x); 
		}
	}
	return res;
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. `x` e `n` são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida no registrador R15.

```assembly
POT: NOP
cmp #0,R14
jne POTC
mov #1,R15
ret

cmp #1,R14
jne POTC
ret 

POTC: NOP
sub #1,R14
push R13
push R12
push R11
mov #0,R13 ;r13 é k
mov R15,R12 ;r12 é res=x
mov R15,R11 ;R11 é x
POTL: cmp R13,R14
jeq POTE
;res = Multiplica(res,x)
push R15
mov R12,R15
push R14
mov R11,R14
call #MULT
pop R14
mov R15,R12
pop R15
inc R13
jmp POTL
POTE: mov R12,R15
pop R11
pop R12
pop R13
ret

MULT: NOP
push R13
push R12
mov #0,R13
mov #0,R12
MFOR: NOP
cmp R12,R14
jeq MEXIT
add R15,R13
inc R12
jmp MFOR
MEXIT: mov R13,R15
pop R12
pop R13
ret
```

3. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula a divisão de `a` por `b`, onde `a`, `b` e o valor de saída são inteiros de 16 bits. `a` e `b` são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.

```assembly
DIV: NOP
cmp #0,R14
jne DI2
mov #-1,R15
ret
DI2: cmp R14,R15
jge DIVL
mov #0,R15
ret
DIVL: NOP
push R13 ; R13 é i
push R12 ; R12 é res
mov #1,R13
DIVT: NOP
push R15
mov R13,R15
call #MULT
mov R15,R12
pop R15
cmp R15,R12
jge DIVE
inc R13
jmp DIVT
DIVE: NOP
mov R13,R15
dec R15
pop R12
pop R13
ret
```

4. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o resto da divisão de `a` por `b`, onde `a`, `b` e o valor de saída são inteiros de 16 bits. `a` e `b` são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.

```assembly
MODF: NOP
push R13
push R12
mov R15,R13
mov R14,R12
call #DIV
mov R12,R14
call #MULT
sub R15,R13
mov R13,R15
pop R12
pop R13
ret
```

5. (a) Escreva uma função em C que indica a primalidade de uma variável inteira sem sinal, retornando o valor 1 se o número for primo, e 0, caso contrário. Siga o seguinte protótipo:

```C
int Primalidade(unsigned int x);
```

```C
int Primalidade(unsigned int x)
{
	int i,k;

	if(x < 2)
		return 0;
	else if(x < 4)
		return 1;
	else if(x % 2 == 0)
		return 0;
	else if(x % 3 == 0)
		return 0;
	i = 5;
	while(Multiplica(i,i) <= x)
	{
		k = i+2;
		if(x % i == 0)
			return 0;
		if(x % k == 0)
			return 0;
		i += 6;
	}
	return 1;
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável de entrada é fornecida pelo registrador R15, e o valor de saída também.

```assembly
PRIM: NOP
push R14
push R13
push R12
mov R15,R14
cmp #2,R15
jl NPRIM
cmp #4,R15
jl SPRIM

push R14
mov #2,R14
call #MODF
pop R14
cmp #0,R15
jeq NPRIM

push R14
mov #3,R14
call #MODF
pop R14
cmp #0,R15
jeq NPRIM

mov #5,R13
PRW: NOP
push R15
push R14
mov R13,R15
mov R13,R14
call #MULT
mov R15,R13
pop R14
pop R15
cmp R13,R15
jge PROPER
jmp SPRIM

PROPER: NOP
mov R13,R12
add #2,R12

push R14
push R15
mov R13,R14
call #MODF
cmp #0,R15
jeq NPRIM
pop R15
mov R12,R14
cmp #0,R15
jeq NPRIM        
pop R14

add #6,R13
jmp PRW

NPRIM: mov #0,R15
jmp PRIME

SPRIM: mov #1, R15
jmp PRIME

PRIME: NOP
pop R12
pop R13
pop R14
ret
```