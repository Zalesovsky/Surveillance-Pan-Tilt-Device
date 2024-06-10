#define F_CPU 4000000
#include <avr/io.h>

int x, y, i=25, j=25, t=20, d=20;
bool stop1=0, stop2=0, stop3=0, stop4=0, e1, e2, e3, e4;

//Функция задержки
void delay(int m)
{
	for (x=0; x<m ;x++) asm ("nop");
}

//Функция длинной задержки
void long_delay(int p)
{
	for (y=0; y<p; y++)  delay (300);
}

//Функция поворота ротора вправо
void right (void)
{
	//PORTD = PORTD & ~(1 << 0); //обмотка A
	PORTD = PORTD | (1 << 3);
	long_delay(t);

	PORTD = PORTD | (1 << 2); //обмотка B
	PORTD = PORTD & ~(1 << 3);
	long_delay(t);

	PORTD = PORTD | (1 << 1); //обмотка C
	PORTD = PORTD & ~(1 << 2);
	long_delay(t);

	PORTD = PORTD | (1 << 0); //обмотка D
	PORTD = PORTD & ~(1 << 1);
	long_delay(t);
	PORTD = PORTD & ~(1 << 0);
}

//Функция поворота ротора влево
void left(void)
{
	PORTD = PORTD | (1 << 0); //обмотка D
	//PORTD = PORTD & ~(1 << 3);
	long_delay(t);

	PORTD = PORTD | (1 << 1); //обмотка C
	PORTD = PORTD & ~(1 << 0);
	long_delay(t);

	PORTD = PORTD | (1 << 2); //обмотка B
	PORTD = PORTD & ~(1 << 1);
	long_delay(t);

	PORTD = PORTD | (1 << 3); //обмотка A
	PORTD = PORTD & ~(1 << 2);
	long_delay(t);
	PORTD = PORTD & ~(1 << 3);
	
}

//Функция поворота ротора вверх
void up (void)
{
	PORTD = PORTD | (1 << 7); //обмотка A
	long_delay(t);

	PORTD = PORTD | (1 << 6); //обмотка B
	PORTD = PORTD & ~(1 << 7);
	long_delay(t);

	PORTD = PORTD | (1 << 5); //обмотка C
	PORTD = PORTD & ~(1 << 6);
	long_delay(t);

	PORTD = PORTD | (1 << 4); //обмотка D
	PORTD = PORTD & ~(1 << 5);
	long_delay(t);
	PORTD = PORTD & ~(1 << 4);
}

//Функция поворота ротора вниз
void down(void)
{
	PORTD = PORTD | (1 << 4); //обмотка D
	long_delay(t);

	PORTD = PORTD | (1 << 5); //обмотка C
	PORTD = PORTD & ~(1 << 4);
	long_delay(t);

	PORTD = PORTD | (1 << 6); //обмотка B
	PORTD = PORTD & ~(1 << 5);
	long_delay(t);

	PORTD = PORTD | (1 << 7); //обмотка A
	PORTD = PORTD & ~(1 << 6);
	long_delay(t);
	PORTD = PORTD & ~(1 << 7);
	
}


int main(void)
{
	DDRC = 0x00;//Конфигурирование порта C на вход
	PORTC = 0x00;//Отключаем подтягивающие резисторы порта C
	DDRD = 0xFF;//Конфигурирование порта D на выход
	PORTD = 0x00;//Выставляем низкий уровень на всех битах порта D
    while(1)
     {
      e1=0; e2=0; e3=0; e4=0;  //обнуляем флаги нажатия кнопок
      while ((e1 == 0)&&(e2 == 0)&&(e3 == 0)&&(e4 == 0)) // пока все клавиши отпущены
       {
	    if ((PINC & 1) == 0) // нажатие кнопки вправо
	     {
		  long_delay (d);            // Устранение дребезга контаткта клавиши

		  while ((PINC & 1) == 0 && stop1!=1)    // Ждем отпускание кнопки
		   {
			right();
		    e1=1;                    // Флаг нажатия клавиши
			stop2=0;                 // Флаг правого конечного положения двигателя
			i++;                     // Счетчик шагов двигателя
			if(i==50) stop1=1;
		   }
	     } 

	    if ((PINC & 0x2) == 0) // нажатие кнопки влево
	     {
		  long_delay (d);

		  while ((PINC & 0x2) == 0 && stop2!=1)
		   {
			left();
			e2=1;
			stop1=0;
			i--;
		    if(i==0) stop2=1;
		   }
	     }

	    if ((PINC & 0x4) == 0) // нажатие кнопки вверх
	     {
		  long_delay (d);

		  while ((PINC & 0x4) == 0 && stop3!=1)
		   {
			up();
			e3=1;
			stop4=0;
			j++;
			if(j==50) stop3=1;
		   }
	     }

	    if ((PINC & 0x8) == 0) // нажатие кнопки вниз
	     {
		  long_delay (d);

		  while ((PINC & 0x8) == 0 && stop4!=1)
		   {
			down();
			e4=1;
			stop3=0;
		    j--;
			if(j==0) stop4=1;
		   }
	     }
      }
   }
}