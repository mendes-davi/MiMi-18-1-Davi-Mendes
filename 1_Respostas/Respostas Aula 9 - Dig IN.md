1. Escreva uma função em C que faz o debounce de botões ligados à porta P1.


> Maneiras de realizar o debounce dos botões:
>
> 1. Ignorar a entrada por X segundos (Ex: 10 ms) e testar novamente.
> 2. Detectar transição, inciar contador e testar entrada novamente. Se a entrada seguir igual decremente o contador, se a entrada for alterada resete o contador. Repita até o contador zerar.
> 3. Utilizar o método 2 só que deslocando os bits do contador no lugar das somas.

```C
int RespostaDebounce()
{
    if((P1IN & BTN )== 0)
    {
    	atraso(22000);
    	if((P1IN & BTN) == 0)
    		return 1;
    }
    return 0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	P1DIR |= LEDS;
	P1DIR &= ~BTN;
	P1REN |= BTN;
	P1OUT |= BTN;
	while(true)
	{
        if(RespostaDebounce() == 1)
            P1OUT |= LEDS;
        else
            P1OUT &= ~LEDS;
	}
	return 0;
}
```

2. Escreva um código em C que lê 9 botões multiplexados por 6 pinos, e pisca os LEDs da placa Launchpad de acordo com os botões. Por exemplo, se o primeiro botão é pressionado, os LEDs piscam uma vez; se o segundo botão é pressionado, os LEDs piscam duas vezes; e assim por diante. Se mais de um botão é pressionado, os LEDs não piscam.

> Pseudocódigo:
> X1, X2, X3 são saídas. Y1, Y2, Y3 são entradas (pullup - ativas em 0). Um botão é pressionado por vez.

```C
#include <msp430.h>

#define ROW1 BIT2
#define ROW2 BIT3
#define ROW3 BIT4

#define COL1 BIT5
#define COL2 BIT6
#define COL3 BIT7

#define LEDS (LED1|LED2)

void pisca(); // Função para piscar os leds.
void Atraso_ms(volatile unsigned int ms); // Função de atraso do timer.
int numPos(long unsigned int i, long unsigned int j); // Retorna pos do botão pressionado

void main(void)
{
    int coord[3][3]; // [ROW][COL]
    long unsigned int i, j;
    int q_press, num;

    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LEDS;
    P1DIR &= ~(ROW1 + ROW2 + ROW3); // entradas inicialmente
    P1DIR |= (COL1 + COL2 + COL3); // saidas inicialmente

    P1REN |= (ROW1 + ROW2 + ROW3); // ativa resistores nas entradas
    P1OUT |= (ROW1 + ROW2 + ROW3); // ativa-os como pull-up

    while(1)
    {
        q_press = 0;
        coord = [[0,0,0],[0,0,0],[0,0,0]];

        // ROWs são entradas, COLs são saídas
        P1DIR |= LEDS;
        P1DIR &= ~(ROW1 + ROW2 + ROW3); // entradas inicialmente
        P1DIR |= (COL1 + COL2 + COL3); // saidas inicialmente

        P1REN |= (ROW1 + ROW2 + ROW3); // ativa resistores nas entradas
        P1OUT |= (ROW1 + ROW2 + ROW3); // ativa-os como pull-up
			P1OUT &= ~(COL1 + COL2 + COL3);
        
        for (i = 1000; i <= 10000; i*= 10) 
            if ((P1IN & i) == 0 ) 
                for (j = 0; j < 3; j++)
                    coord[i][j] = 1; // soma 1 a toda a coluna que foi apertada
   
        // ROWs são saídas, COLs são entradas
        P1DIR |= (ROW1 + ROW2 + ROW3); // saídas
        P1DIR &= ~(COL1 + COL2 + COL3); // entradas

        P1REN |= (COL1 + COL2 + COL3); // ativa resistores nas entradas
        P1OUT |= (COL1 + COL2 + COL3); // ativa-os como pull-up
        P1OUT &= ~(ROW1 + ROW2 + ROW3);
        
        for (i = 100000; i <= 10000000; i*= 10)
            if ((P1IN & i) == 0 ))
            	for (j = 0; j < 3; j++)
              		coord[j][i] = 1; // soma 1 a toda a linha que foi apertada

        for (i = 0; i < 3; i++) 
        {
            for (j = 0; j < 3; j++) 
            {
                // conta quantos botões apertados foram registrados
                if(coord[i][j] == 2) 
                    q_press++;
					  num = cord[i][j] == 2 ? numPos(i,j) : num;
            }
        }
        if (q_press == 1)
            for(i=0; i < num; i++)
                pisca();
    }

}

void pisca()
{
	P1OUT |= LEDS;
	Atraso_ms(1000);
	P1OUT &= ~LEDS;	
}

void Atraso_ms(volatile unsigned int ms)
{
	TACCR0 = 1000-1;
	TACTL = TACLR;
	TACTL = TASSEL_2 + ID_0 + MC_1;
	while(ms--)
	{
		while((TACTL&TAIFG)==0);
		TACTL &= ~TAIFG;
	}
	TACTL = MC_0;
}

int numPos(long unsigned int i, long unsigned int j)
{
	return (int) 3*j+i+1;
}

```







