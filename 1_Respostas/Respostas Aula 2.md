1.  Quais as diferenças entre os barramentos de dados e de endereços?

    Os barramentos de dados carregam dados e instruções de maneira bidirecional entre a CPU e periféricos. Os barramentos de endereços funcionam de maneira unidirecional para interegir com memórias e periféricos. O tamanho dos barramentos de endereço em varia de acordo com as necessidades de tal maneira que m bits podem representar 2**m endereços diferentes, já o barramento de dados tem um tamanho definido de acordo com a capacidade de cada CPU.

2.  Quais são as diferenças entre as memórias RAM e ROM?

    As memórias RAM são voláteis, mais velozes e podem ser facilmente alteradas durante a execução de programas, apresentam menor capacidade de armazenamento. As informações importantes devem ser armazenadas em uma memória ROM que não é volátil de maneira que as informações sejam preservadas e mantidas em um espaço que geralmente possui maior capacidade de armazenamento. Ao requisitar informações da memória ROM elas devem ser transferidas para memória RAM para serem utilizadas durante a execução de um programa.

3.  Considere o código abaixo:

```c
#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}
```

Para este código, responda: (a) A variável `i` é armazenada na memória RAM ou ROM? Por quê? (b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?

A variável `i` Será armazenada na memória RAM, pois essa variável faz parte de um dado gerado durante a execução de um programa e será alocada na memória RAM para que possa ser lida/escrita. Já o programa compilado será armazenado na memória ROM, pois é um dado não volátil e dever ser salvo.

4.  Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?

    Em uma arquitetura Harvard temos barramentos separados para dados e endereços, podendo ter diferentes tamanhos entre si. Geralmente essa arquitetura é mais elaborada e apresenta maior complexidade com memórias separadas. A arquitetura Von Neumann emprega um único barramento para dados e endereços, podendo acessar a memória de programas e dados juntamente. Por utilizar um único barramento, temos como vantagem uma menor complexidade de projeto do microprocessador.

5.  Considere a variável inteira `i`, armazenando o valor `0x8051ABCD`. Se `i` é armazenada na memória a partir do endereço `0x0200`, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian; (b) Big-endian.
| Little Endian  | Big Endian      |
| -------------- | --------------- |
| `0x200` - `CD` | `0x200` - `CD`  |
| `0x201` - `AB` | `0x01FF` - `AB` |
| `0x202` - `51` | `0x01FE` - `51` |
| `0x203` - `80` | `0x01FD` - `80` |

6.  Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?

    O MSP pode realizar essa soma utilizando os registradores de _carry_ para transferir o excesso da soma para o outro registrador e utiliza o registrador de _overflow_ para indicar se houve _overflow_ na execução dessa soma.