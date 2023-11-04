

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "Padel.h"



/*******************GVARS****************/
/********************** 7amoksha********************/
u8  Hamoksha[8] = {
	0b00100,
	0b01010,
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b01010,
	0b01010
};

/**********************heart***************/
u8 heart[] = {
	0B00000,
	0B00000,
	0B11011,
	0B11111,
	0B11111,
	0B01110,
	0B00100,
	0B00000
};

u8 flag_direction=1;
u8 ch_1=1,ch_2=1;

u8 score1=0;
u8 score2=0;
u8 i=1,j=1;
BUTTON_STATUS_t L_Button =NOT_PRESSED;

BUTTON_STATUS_t R_Button =NOT_PRESSED;

/***************************************/
void Padel_Init(void)
{
	DIO_Init();
	LCD_Init();
	LCD_CustomerChar(1,Hamoksha);
	LCD_CustomerChar(2,heart);
	LCD_GoTo(4,0);
	LCD_WriteString("p1:0          p2:0");
}


void Padel_Runnable(void)
{
	if (score1==5||score2==5)
	{
		winner_dis();
		
		reset_game();
		
	}
	/********7amoksha & 7azl2oom position ****/
	LCD_GoTo(ch_2,19);
	LCD_WriteChar(HAMOKSHA);
	LCD_GoTo(ch_1,0);
	LCD_WriteChar(HAMOKSHA);
	
	L_Button=Get_L_Button();
	R_Button=Get_R_Button();
	
	
	if (flag_direction)
	{
		if(L_Button==BL_DOWN)
		{
			j++;
			if(j==4)
			{
				j=3;
			}
		}
		else if(L_Button==BL_UP)
		{
			j--;
			if(j==0)
			{
				j=1;
			}
		}
		if(R_Button==BR_DOWN)
		{
			LCD_GoTo(ch_2,19);
			LCD_WriteChar(' ');
			ch_2++;
			
			if(ch_2==4)
			{
				ch_2=3;
			}
		}
		
		else if(R_Button==BR_UP)
		{
			LCD_GoTo(ch_2,19);
			LCD_WriteChar(' ');
			ch_2--;
			if(ch_2==0)
			{
				ch_2=1;
			}
		}
		i++;
		if (i==18)
		{
			flag_direction=0;
			if(j!=ch_2)
			{
				DIO_WritePin(PUZ,HIGH);
				_delay_ms(300);
				DIO_WritePin(PUZ,LOW);
				score1++;
				LCD_GoTo(4,3);
				LCD_WriteNumber(score1);
			}
			
		}

	}
	else
	{
		
		if(R_Button==BR_DOWN)
		{
			j++;
			if(j==4)
			{
				j=3;
			}
		}
		else if(R_Button==BR_UP)
		{
			j--;
			if(j==0)
			{
				j=1;
			}
		}
		
		if(L_Button==BL_DOWN)
		{
			
			ch_1++;
			if(ch_1==4)
			{
				ch_1=3;
			}
			LCD_GoTo(ch_1-1,0);
			LCD_WriteChar(' ');
		}
		
		else if(L_Button==BL_UP)
		{
			
			
			ch_1--;
			if(ch_1==0)
			{
				ch_1=1;
			}
			LCD_GoTo(ch_1+1,0);
			LCD_WriteChar(' ');
		}
		i--;
		if (i==1)
		{
			if(j!=ch_1)
			{
				DIO_WritePin(PUZ,HIGH);
				_delay_ms(300);
				DIO_WritePin(PUZ,LOW);
				score2++;
				LCD_GoTo(4,17);
				LCD_WriteNumber(score2);
			}
			flag_direction=1;
		}
	}
	/***************ball position**************/
	LCD_GoTo(j,i);
	LCD_WriteChar('0');
	_delay_ms(50);
	LCD_GoTo(j,i);
	LCD_WriteChar(' ');
}


void winner_dis(void)
{
	_delay_ms(300);
	LCD_Clear();
	LCD_GoTo(1,0);
	LCD_WriteString("The winner is ......");
	LCD_GoTo(4,5);
	_delay_ms(1000);
	
	if (score1>score2)
	{
		LCD_WriteString("Hamoksha ");
		LCD_WriteChar(HEART);
		LCD_WriteChar(HEART);
		LCD_WriteChar(HEART);
		_delay_ms(1000);
		LCD_Clear();
	}
	
	
	else if (score2>score1)
	{
		LCD_WriteString("7azal2oom ");
		LCD_WriteChar(HEART);
		LCD_WriteChar(HEART);
		LCD_WriteChar(HEART);
		_delay_ms(1000);
		LCD_Clear();
	}
}


void reset_game(void)
{
	LCD_Clear();
	score1=0;
	score2=0;
	i=1;
	j=1;
	flag_direction=1;
	ch_1=1;
	ch_2=1;
	LCD_GoTo(4,0);
	LCD_WriteString("p1:0          p2:0");
	L_Button=NOT_PRESSED;
	R_Button=NOT_PRESSED;
}

BUTTON_STATUS_t Get_L_Button(void)
{
	BUTTON_STATUS_t button=NOT_PRESSED;
	if(!DIO_ReadPin(PIND7))
	{
		_delay_ms(3);
		while(!DIO_ReadPin(PIND7));
		button=BL_DOWN;
	}
	if(!DIO_ReadPin(PIND6))
	{
		_delay_ms(3);
		while(!DIO_ReadPin(PIND6));
		button=BL_UP;
	}
	return button;
	
}



BUTTON_STATUS_t Get_R_Button(void)
{
	BUTTON_STATUS_t button=NOT_PRESSED;
	if(!DIO_ReadPin(PIND5))
	{
		_delay_ms(3);
		while(!DIO_ReadPin(PIND5));
		button=BR_DOWN;
	}
	if(!DIO_ReadPin(PIND3))
	{
		_delay_ms(3);
		while(!DIO_ReadPin(PIND3));
		button=BR_UP;
	}
	
	return button;
	
}