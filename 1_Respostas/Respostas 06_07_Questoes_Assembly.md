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
int Potencia(int x, int N)
{
	int pow = 1;
	for (int i = 0; i < N; ++i)
	{
		pow = pow * x;
	}
	return pot;
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. `x` e `n` são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida no registrador R15.

```assembly
; R15 = x & R14 = n
POT: NOP
; #TODO - Casos triviais (n = 0,1)
MOV R14,R13 ; R13 = n
MOV R15,R14 ; R14 = x 
MOV #1, R15 ; R15 = pow = 1
FOR_POT: NOP
CMP #0,R13 ; n > 0 ? mult : ret
JEQ END
call #mult  ; multiplica pow (R15) por x (R14)
DEC R13     ; R13-- / n--
JMP FOR_POT
END: RET

; #TODO - Refazer os testes dessa função
MULT: NOP
PUSH R14 ; guarda x (R14) na pilha
PUSH R13 ; guarda n (R13) na pilha
MOV R15,R13 ; R13 guardará o valor de pow inalterado
FOR_MULT: NOP
CMP #1,R14 ; n > 0 ? soma : ret
JEQ END
ADD R13,R15
DEC R14
JMP FOR_MULT
END: NOP
POP R13
POP R14
RET
```
