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


