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

```





