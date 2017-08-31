#include "Menu.h"

//===============================================================
void BlinkItem(unsigned char ind);
void MainMenuItemProcess(unsigned char ind);
void MainMenuProcess(void);
void Menu_Auto_mode(void);
void Menu_Manual_mode(void);
void Load_control(char number_load,char on_off);
void Load_control_Zone(char Zone,char on_off);
void AutoMode(uint8_t flag_work);
void List_one(void);
void List_two_out(void);
void Load_Time(int Zone);
void Serv_Action(float Temp, char flag);
void Indication_Load_Zone(char Zone);
void Serv_Action2(float Temp, char flag);
void initializ_Load_Mode_3(void);
void Serv_Action_Mode3_1(float Temp);
void Serv_Action_Mode3_2(float Temp);
void USART_Mode(void);
void Mode1(void);
void Mode2(void);
void Mode3(void);
void MenuSettingsProcess(void);
void MEnuSettingsItemProcess(unsigned char set);
void Control_Zone(void);
void Menu_setTimeProcess(void);
void TimeMenuItemProcess(unsigned char val);
void SET_TIME_clockds1307(void);

//флаги работы устройства
//===============================================================
 uint8_t  EEMEM flag_workZone;//флаг работы зоны
 char flag_Z1_N1;//переменная определения работы 1 нагрузки 1-ая зона(1 ON 0-OFF)
 char flag_Z1_N2;//переменная определения работы 2 нагрузки 1-ая зона
 char flag_Z2_N3;//переменная определения работы 3 нагрузки 2-ая зона
 char flag_Z2_N4;//переменная определения работы 4 нагрузки 2-ая зона
 char flag_Z1;//переменная определения работы нагрузок в зоне
 char flag_Z2;//переменная определения работы нагрузок в зоне
extern char flag_servo_work1;//флаг работы первого сервопривода
extern char flag_servo_work2;//флаг работы 2-ого сервопривода

 char flag_work_load_Time1=1;//переменная определения режима работы по времени или по датчику влажности(1-работа от датчиков , 2-работа от таймера)
 char flag_work_load_Time2=1;
//================================================================

char list=1;//переменная для управления выводом листом в ручной режим
char count_flag_list1=1;//первый лист счет позиций
char count_flag_list2=1;//второй лист счет позиций
char count_flag_list3=1;//третий лист счет позиций


//================================================================
extern unsigned char cnt_timer;
unsigned int i;

char str2[5];

  char str[5][35]=
{
	
	"Auto \0",
	"Manual  \0",
	"PC/Android\0",
	"settings \0",
	"Exit \0"
	
}; 

char podstr[2][18]=
{
	"Settings Zone \0",
	"Settings Time \0",
	
};

//================================================================
extern int second;//секунды
extern int minuts;//минуты
extern int hose;//часы
extern int day;//день недели
extern int data;//дата
extern int mesiac;//мес¤ц
extern int year;//год
//=================================================================

Menu_StateTypeDef menu_state=MENU_STATE_IDLE;
MAIN_MENU_StateTypeDef main_menu_state=MAIN_MENU_STATE_IDLE;
MENU_SETTINGS_StateTypeDef menu_settings=MENU_SETTINGS_STATE_IDLE;
MENU_SET_Time_Typedef menu_times=MENU_SET_Time_IDLE;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void MenuProcess(void)
{
	
	switch (menu_state)
	{
		//---------------------------------
		case MENU_STATE_IDLE:
		menu_state=MENU_STATE_WAIT;
		LCDclear();
		LCDstringXY("Menu",5,0);
		LCDstringXY("Press",5,1);
		LCDstringXY("Select",5,2);
		break;
		//----------------------------------
		case MENU_STATE_WAIT:
		if (KeyPrress(Select)==1)
		{
			
			menu_state=MENU_STATE_MAIN;
			
		}
		break;
		//----------------------------------
		case MENU_STATE_MAIN:
		main_menu_state=MAIN_MENU_STATE_IDLE;
		MainMenuProcess();
		break;
		//----------------------------------
		
	}
	_delay_ms(10);
	
}
void MainMenuProcess(void)
{
	
 	while (1)
 	{
		switch (main_menu_state)
		{
//++++++++++++++++++++++++++++++++++++++++++++
			
			
			
		case MAIN_MENU_STATE_IDLE :
			
			for(i=0;i<5;i++)
			{
				if (i<4)
				{
					
					LCDstringXY(str[i],5,i);
				}
				else
				{
					LCDsendString(str[i]);
					
				}
				
			}
			
			main_menu_state=MAIN_MENU_STATE_WAIT;
			break;
//++++++++++++++++++++++++++++++++++++++++++++
			
			
			
			
			case MAIN_MENU_STATE_WAIT:
			LCDstringXY("->",2,0);
			if (KeyPrress(DOWN)==1)
			{
			
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto_WAIT;
				
			}
			break;
//++++++++++++++++++++++++++++++++++++++++++++
			
			
			
			
			case MAIN_MENU_STATE_Menu1_Auto_WAIT:
			//BlinkItem(0);
			//нажатие вниз
			LCDstringXY("  ",2,1);
			LCDstringXY("  ",2,3);
			LCDstringXY("  ",19,3);
			LCDstringXY("->",2,0);
			if (KeyPrress(DOWN)==1)
			{
				
				main_menu_state=MAIN_MENU_STATE_Menu2_Manual_WAIT;
				
			}
			//=========================================
			//нажатие вверх
			if (KeyPrress(UP)==1)
			{
				main_menu_state=MAIN_MENU_STATE_EXIT_WAIT;
				
			}
			//==========================================
			//нажатие подтверждение
			if (KeyPrress(Select)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto;
				
			}
			//==========================================
			break;
//++++++++++++++++++++++++++++++++++++++++++++
			case MAIN_MENU_STATE_Menu2_Manual_WAIT:
			
			//нажатие вниз
			LCDstringXY("  ",2,0);
			LCDstringXY("  ",2,2);
			LCDstringXY("  ",2,3);
			LCDstringXY("  ",19,3);
			LCDstringXY("->",2,1);
			if (KeyPrress(DOWN)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu3_PC_Android_WAIT;
				
			}
			//----------------------------------
			
			
			//нажатие вверх
			if (KeyPrress(UP)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto_WAIT;
				
			}
			//-------------------------------------
			//нажатие вправа
			if (KeyPrress(Right)==1)
			{
				main_menu_state=MAIN_MENU_STATE_EXIT_WAIT;
				
			}
			//--------------------------------------
			//нажатие выбора
			if (KeyPrress(Select)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu2_Manual;
				
			}
			//---------------------------------------
			
			break;
			
//++++++++++++++++++++++++++++++++++++++++++++
			case MAIN_MENU_STATE_Menu3_PC_Android_WAIT:
			
			//нажатие вверх
			LCDstringXY("  ",2,0);
			LCDstringXY("  ",2,1);
			LCDstringXY("  ",2,3);
			LCDstringXY("  ",19,3);
			LCDstringXY("->",2,2);
			
			//---------------------------
			if (KeyPrress(UP)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu2_Manual_WAIT;
				LCDstringXY(str[2],5,2);
			}
			//-----------------------------
			//нажатие вниз
			if (KeyPrress(DOWN)==1)
			{
				
				main_menu_state=MAIN_MENU_STATE_Menu4_Settings_WAIT;
				LCDstringXY(str[2],5,2);
			}
			//-----------------------------
			//нажатие вправо
			if (KeyPrress(Right)==1)
			{
				main_menu_state=MAIN_MENU_STATE_EXIT_WAIT;
				LCDstringXY(str[2],5,2);
			}
			//------------------------------
			//нажатие выбора
			if (KeyPrress(Select)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu3_PC_Android;
				LCDstringXY(str[2],5,2);
			}
			//------------------------------
			break;			
//++++++++++++++++++++++++++++++++++++++++++++++++++++	


//++++++++++++++++++++++++++++++++++++++++++++
			case MAIN_MENU_STATE_Menu4_Settings_WAIT:
			//BlinkItem(3);
			//нажатие вверх
			LCDstringXY("  ",2,0);
			LCDstringXY("  ",2,1);
			LCDstringXY("  ",2,2);
			LCDstringXY("->",2,3);
			LCDstringXY("  ",19,3);
			//---------------------------
			if (KeyPrress(UP)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu3_PC_Android_WAIT;
				LCDstringXY(str[3],5,3);
			}
			//-----------------------------
			//нажатие вниз
			if (KeyPrress(DOWN)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto_WAIT;
				LCDstringXY(str[3],5,3);
			}
			//-----------------------------
			//нажатие вправо
			if (KeyPrress(Right)==1)
			{
				main_menu_state=MAIN_MENU_STATE_EXIT_WAIT;
				LCDstringXY(str[3],5,3);
			}
			//------------------------------
			//нажатие выбора
			if (KeyPrress(Select)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu4_Settings;
				LCDstringXY(str[3],5,3);
			}
			//------------------------------
			break;
//++++++++++++++++++++++++++++++++++++++++++++++++++++		

			case MAIN_MENU_STATE_EXIT_WAIT:
			LCDstringXY("  ",2,0);
			LCDstringXY("  ",2,1);
			LCDstringXY("  ",2,2);
			LCDstringXY("  ",2,3);
			LCDstringXY("?",19,3);
			//нажатие вверх
			//---------------------------
			if (KeyPrress(UP)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu4_Settings_WAIT;
				
				
			}
			//-----------------------------
			//нажатие вниз
			if (KeyPrress(DOWN)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto_WAIT;
				//координаты ?
				
			}
			//-----------------------------
			//нажатие вправо
			if (KeyPrress(Right)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu1_Auto_WAIT;
				
			}
			//------------------------------
			//нажатие влево
			if (KeyPrress(Left)==1)
			{
				main_menu_state=MAIN_MENU_STATE_Menu4_Settings_WAIT;
				
			}
			//------------------------------
			
			//нажатие выбора
			if (KeyPrress(Select)==1)
			{
				main_menu_state=MAIN_MENU_STATE_EXIT;
				
			}
			//------------------------------
			break;
//++++++++++++++++++++++++++++++++++++++++++++++++++++

//непосредственно меню:
			case MAIN_MENU_STATE_Menu1_Auto:
			main_menu_state=MAIN_MENU_STATE_IDLE;
			
				MainMenuItemProcess(1);
				LCDclear();
			
				
			
			break;
			case MAIN_MENU_STATE_Menu2_Manual:
			main_menu_state=MAIN_MENU_STATE_IDLE;
			MainMenuItemProcess(2);
			LCDclear();
			break;
			case MAIN_MENU_STATE_Menu3_PC_Android:
			main_menu_state=MAIN_MENU_STATE_IDLE;
			MainMenuItemProcess(3);
			LCDclear();
			break;
			case MAIN_MENU_STATE_Menu4_Settings:
			main_menu_state=MAIN_MENU_STATE_IDLE;
			MainMenuItemProcess(4);
			LCDclear();
			break;
			
			case MAIN_MENU_STATE_EXIT:
			menu_state=MENU_STATE_IDLE;
			return;
		
			break;
			
			

		}
		
		
		
		
		
	}
}

//вход в любой пункт главного меню
void MainMenuItemProcess(unsigned char ind)
{
	
	LCDclear();
	//обработчик для внутренних меню или внутренних функций
	
		switch (ind)
		{
			case 1 :
			goto Cleanup;
			Cleanup: ; 
			
			uint8_t flagcontrol=eeprom_read_byte(&flag_workZone);
			
			AutoMode(flagcontrol);
			if (KeyPrress(Select)==1)
			{
				LCDclear();
				main_menu_state=MAIN_MENU_STATE_IDLE;
				break;
				
			}
			break;
			
			case 2:
			Menu_Manual_mode();
			if (KeyPrress(Select)==1)
			{
				LCDclear();
				main_menu_state=MAIN_MENU_STATE_IDLE;
				break;
				
				
			}
			break;
			
			case 3:
			{
				
				
				USART_Mode();
				if (KeyPrress(Select)==1)
				{
					LCDclear();
					main_menu_state=MAIN_MENU_STATE_IDLE;
					break;
					
					
				}
				break;
			}
			
			case 4:
			{
				LCDclear();
				MenuSettingsProcess();
				if (KeyPrress(Select)==1)
				{
					LCDclear();
					main_menu_state=MAIN_MENU_STATE_IDLE;
					break;
					
					
				}
				break;
			}
			
		
	}
	
	
	
	
}
//-----------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ручное управление++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//функция ручного управления системой полива
void Menu_Manual_mode(void)
{
	
	
	while (1)
	{
		if (KeyPrress(Select)==1)
		{
			break;
		}
		if (count_flag_list1>2)
		{
			list=2;
			count_flag_list1=1;
		}
		if (count_flag_list1<1)
		{
			list=3;
			count_flag_list1=1;
		}
		if (count_flag_list2>2)
		{
			list=3;
			count_flag_list2=1;
		}
		if (count_flag_list2<1)
		{
			list=1;
			count_flag_list2=1;
		}
		
		if (count_flag_list3>2)
		{
			list=1;
			count_flag_list3=1;
		}
		if (count_flag_list3<1)
		{
			list=2;
			count_flag_list3=1;
		}
		
		//======================================================================
		switch (list)
		{
		case 1 :
		//------------------------------------------------------
			if (KeyPrress(UP)==1)
			{
				count_flag_list1-=1;
			}
			if (KeyPrress(DOWN)==1)
			{
				count_flag_list1+=1;
			}
			
			//+++++++++++++++++++++++++++++++++++++++++++++++++
			switch(count_flag_list1)
			{
				case 1:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,2);
				LCDstringXY("->",3,1);
				LCDstringXY("Load 1-",5,1);
				LCDstringXY("Load 2-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					LCDstringXY("ON ",13,1);
					Load_control(Load1,ON);
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					Load_control(Load1,OFF);
				}
				
				
				break;
				
				
				
				case 2:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,1);
				LCDstringXY("->",3,2);
				LCDstringXY("Load 1-",5,1);
				LCDstringXY("Load 2-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					LCDstringXY("ON ",13,2);
					Load_control(Load2,ON);
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					Load_control(Load2,OFF);
				}
				
				
				break;
				
			}
			
			
		
		//------------------------------------------------------
			break;
			
		case 2 :
		{
			
			if (KeyPrress(UP)==1)
			{
				count_flag_list2-=1;
			}
			if (KeyPrress(DOWN)==1)
			{
				count_flag_list2+=1;
			}
			
			//+++++++++++++++++++++++++++++++++++++++++++++++++
			switch(count_flag_list2)
			{
				case 1:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,2);
				LCDstringXY("->",3,1);
				LCDstringXY("Load 3-",5,1);
				LCDstringXY("Load 4-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					LCDstringXY("ON ",13,1);
					Load_control(Load3,ON);
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					Load_control(Load3,OFF);
				}
				
				
				break;
				
				
				
				case 2:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,1);
				LCDstringXY("->",3,2);
				LCDstringXY("Load 3-",5,1);
				LCDstringXY("Load 4-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					LCDstringXY("ON ",13,2);
					Load_control(Load4,ON);
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					Load_control(Load4,OFF);
				}
				
				
				break;
				
			}
			break;
		}
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		case 3 :
		{
			
			if (KeyPrress(UP)==1)
			{
				count_flag_list3-=1;
			}
			if (KeyPrress(DOWN)==1)
			{
				count_flag_list3+=1;
			}
			
			//+++++++++++++++++++++++++++++++++++++++++++++++++
			switch(count_flag_list3)
			{
				case 1:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,2);
				LCDstringXY("->",3,1);
				LCDstringXY("SERV1-",5,1);
				LCDstringXY("SERV2-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					LCDstringXY("ON",13,1);
					
					ServoPrivod_One_90();
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					ServoPrivod_One_0();
				}
				
				
				break;
				
				
				
				case 2:
				LCDstringXY("^",10,0);
				LCDstringXY("v",10,3);
				LCDstringXY("  ",3,1);
				LCDstringXY("->",3,2);
				LCDstringXY("SERV1-",5,1);
				LCDstringXY("SERV2-",5,2);
				LCDstringXY("<",0,2);
				LCDstringXY(">",19,2);
				
				if (KeyPrress(Left))
				{
					
					LCDstringXY("ON",13,2);
					ServoPrivod_Two_0();
				}
				else{
					LCDstringXY("OFF",13,1);
					LCDstringXY("OFF",13,2);
					ServoPrivod_Two_90();
				}
				
				
				break;
				
			}
			break;
		}
			
		
		
		}
		//=================================================================================
	}
	
	
}
//+++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//функция управления одиночной нагрузкой 
void Load_control(char number_load,char on_off)
{
	if (number_load!=2)
	{
		if (on_off==1)
		{
			ONL(PORTA,number_load);
		}
		else if(on_off==0)
		{
			OFFL(PORTA,number_load);
			
		}
	}
	else if (number_load==2)
	{
		if (on_off==1)
		{
			ONL(PORTD,number_load);
		}
		else if(on_off==0)
		{
			OFFL(PORTD,number_load);
			
		}
		
	}
	
	
}
//+++++++++++++++++++++++++++++++++++++++
//вкл/выкл. нагрузок в зоне 1 и 2
void Load_control_Zone(char Zone,char on_off)
{
	if (on_off==1)
	{
		
		if (Zone==1)
		{ flag_Z1=1;
			Load_control(Load1,ON);
			Load_control(Load2,ON);
		}
		else if (Zone==2)
		{
			flag_Z2=1;
			Load_control(Load3,ON);
			Load_control(Load4,ON);
		}
		
		
	}
	else if (on_off==0)
	{
		if (Zone==1)
		{
			flag_Z1=0;
			Load_control(Load1,OFF);
			Load_control(Load2,OFF);
		}
		else if (Zone==2)
		{
			flag_Z2=0;
			Load_control(Load3,OFF);
			Load_control(Load4,OFF);
		}
	}
	
}

//---------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++=функция управления по USART/интерфейсу+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void USART_Mode(void)
{
	unsigned char count=0;
	unsigned char count_pos=1;
	while (1)
	{
		if (KeyPrress(Select)==1)
		{
			break;
		}
		
		
		switch(Get_char_usart())
		{
			case '1' :
			{
				LCDclear();
				count=1;
				LCDstringXY("  Manual control   ",0,0);
				
				break;
			}
			
			case '2':
			{
				LCDclear();
				count=2;
				LCDstringXY(" Auto-control   ",0,0);
				break;
			}
			case '3':{
				count=3;
				
			    LCDstringXY("Monitor System!!",0,0);
			break;	
			}
			
			case '0':
			{
				
				LCDclear();
				LCDstringXY("Reset command ",0,0);
				_delay_ms(500);
				LCDclear();
				break;
			}
			
			
			
		}
		
		switch(count)
		{
			case 1:
			{
				switch(Get_char_usart())
				{
					case 'a':
					{
						LCDstringXY(">OFF-1load",0,count_pos);
						Load_control(Load1,OFF);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'A':
					{
						LCDstringXY(">ON -1load",0,count_pos);
						Load_control(Load1,ON);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					case 'b':
					{
						LCDstringXY(">OFF-2load",0,count_pos);
						Load_control(Load2,OFF);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'B':
					{
						LCDstringXY(">ON -2load",0,count_pos);
						Load_control(Load2,ON);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					case 'c':
					{
						LCDstringXY(">OFF-3load",0,count_pos);
						Load_control(Load3,OFF);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					case 'C':
					{
						LCDstringXY(">ON -3load",0,count_pos);
						Load_control(Load3,ON);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					
					case 'd':
					{
						LCDstringXY(">OFF-4load",0,count_pos);
						Load_control(Load4,OFF);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'D':
					{
						LCDstringXY(">ON -4load",0,count_pos);
						Load_control(Load4,ON);
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					//-----------------
					case 'e':
					{
						LCDstringXY(">OFF-Serv1",0,count_pos);
						ServoPrivod_One_0();
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'E':
					{
						LCDstringXY(">ON -Serv1",0,count_pos);
						ServoPrivod_One_90();
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'f':
					{
						LCDstringXY(">OFF-Serv2",0,count_pos);
						ServoPrivod_Two_0();
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					case 'F':
					{
						LCDstringXY(">ON -Serv2",0,count_pos);
						ServoPrivod_Two_90();
						count_pos+=1;
						if (count_pos>3)
						{
							count_pos=1;
						}
						break;
					}
					
					
					
				}
				break;
			}
			
			case 2:
			{
				
				switch(Get_char_usart())
				{
					case 'M':
					{
						LCDstringXY(">Mode One!",0,1);
						Mode1();
						break;
					}
					case 'N':{
						
						LCDstringXY(">Mode Two!",0,1);
						Mode2();
						break;
					}
					case 'S':{
						Mode3();
						LCDstringXY(">Mode 3!!!",0,1);
						
						
						break;
					}
				
					
				}
				
				break;
			}
			
			case 3:
			{
				while(1)
				{
					if (KeyPrress(Select)||(Get_char_usart()=='P'))
					{
						break;
					}
					char buffer_T[50];
					char buffer_M[50];
					sprintf(buffer_T,"T=%.1f",Temperature_LM35(0));
					Transmit_str_usart(buffer_T);
					_delay_ms(200);
					Transmit_char_usart(0x0a);
					Transmit_char_usart(0x0d);
					sprintf(buffer_T,"T=%.1f",Temperature_LM35(1));
					Transmit_str_usart(buffer_T);
					Transmit_char_usart(0x0a);
					Transmit_char_usart(0x0d);
					_delay_ms(200);
					
					sprintf(buffer_M,"T=%.1f",Semsor_swit(2));
					Transmit_str_usart(buffer_M);
					_delay_ms(200);
					Transmit_char_usart(0x0a);
					Transmit_char_usart(0x0d);
					sprintf(buffer_M,"T=%.1f",Semsor_swit(3));
					Transmit_str_usart(buffer_M);
					Transmit_char_usart(0x0a);
					Transmit_char_usart(0x0d);
					_delay_ms(200);
				}
				
				break;
			}
			
			
			
		}
	}
	
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Mode1(void)
{
	I2C_SendByteAddr(0,0b11010000);
	_delay_ms(300);
	STart_I2C();

	I2C_SendByte(0b11010001);//отправл¤ем в устройство бит чтени¤
	second=I2C_ReadByte();
	minuts=I2C_ReadByte();
	hose=I2C_ReadByte();
	day=I2C_ReadByte();
	data=I2C_ReadByte();
	mesiac=I2C_ReadByte();
	year=I2C_ReadLastByte();
	STop_I2C();
	second=RTC_ConvertDEC(second);
	minuts=RTC_ConvertDEC(minuts);
	hose=RTC_ConvertDEC(hose);
	day=RTC_ConvertDEC(day);
	data=RTC_ConvertDEC(data);
	mesiac=RTC_ConvertDEC(mesiac);
	year=RTC_ConvertDEC(year);
	
	
	if (hose==15)
	{
		if (minuts>10&&minuts<12)
		{
			
			Load_control_Zone(Zone1,ON);
			LCDstringXY(">Load1-ON ",0,2);
		}
		else{
			LCDstringXY(">Load1-OFF",0,2);
			Load_control_Zone(Zone1,OFF);
			
		}
	}
	
	if (hose==17)
	{
		if (minuts>20&&minuts<23)
		{
			LCDstringXY(">Load2-ON ",0,2);
			Load_control_Zone(Zone2,ON);
		}
		else{
			
			LCDstringXY(">Load2-OFF",0,2);
		Load_control_Zone(Zone2,OFF);	
		}
	}
	
	
}

void Mode2(void)
{
	I2C_SendByteAddr(0,0b11010000);
	_delay_ms(300);
	STart_I2C();

	I2C_SendByte(0b11010001);//отправл¤ем в устройство бит чтени¤
	second=I2C_ReadByte();
	minuts=I2C_ReadByte();
	hose=I2C_ReadByte();
	day=I2C_ReadByte();
	data=I2C_ReadByte();
	mesiac=I2C_ReadByte();
	year=I2C_ReadLastByte();
	STop_I2C();
	second=RTC_ConvertDEC(second);
	minuts=RTC_ConvertDEC(minuts);
	hose=RTC_ConvertDEC(hose);
	day=RTC_ConvertDEC(day);
	data=RTC_ConvertDEC(data);
	mesiac=RTC_ConvertDEC(mesiac);
	year=RTC_ConvertDEC(year);
	
	if (hose==9)
	{
		if(minuts>10&&minuts<13)
		{
			LCDstringXY(">Load1_ON ",0,2);
			Load_control(Load1,ON);
		}
		else{
			LCDstringXY(">Load1_OFF",0,2);
			Load_control(Load1,OFF);
		}
		
		if (minuts>30&&minuts<33)
		{
			LCDstringXY("Load2_ON ",0,2);
			Load_control(Load2,ON);
		}
		else{
			LCDstringXY("Load2_OFF",0,2);
			Load_control(Load2,OFF);
			
		}
		
	}
	else if (hose==15)
	{
		if(minuts>30&&minuts<33)
		{
			LCDstringXY(">Load2_ON ",0,2);
			Load_control(Load1,ON);
		}
		else{
			LCDstringXY(">Load2_OFF",0,2);
			Load_control(Load2,OFF);
		}
		
		if (minuts>10&&minuts<12)
		{
			LCDstringXY("Load1_ON ",0,2);
			Load_control(Load1,ON);
		}
		else{
			LCDstringXY("Load1_OFF",0,2);
			Load_control(Load1,OFF);
			
		}
	}
	
	
	
	
}
void Mode3(void)
{
	I2C_SendByteAddr(0,0b11010000);
	_delay_ms(300);
	STart_I2C();

	I2C_SendByte(0b11010001);//отправл¤ем в устройство бит чтени¤
	second=I2C_ReadByte();
	minuts=I2C_ReadByte();
	hose=I2C_ReadByte();
	day=I2C_ReadByte();
	data=I2C_ReadByte();
	mesiac=I2C_ReadByte();
	year=I2C_ReadLastByte();
	STop_I2C();
	second=RTC_ConvertDEC(second);
	minuts=RTC_ConvertDEC(minuts);
	hose=RTC_ConvertDEC(hose);
	day=RTC_ConvertDEC(day);
	data=RTC_ConvertDEC(data);
	mesiac=RTC_ConvertDEC(mesiac);
	year=RTC_ConvertDEC(year);
	
	if (hose==9)
	{
		if(minuts>10&&minuts<13)
		{
			LCDstringXY(">Load3_ON ",0,2);
			Load_control(Load3,ON);
		}
		else{
			LCDstringXY(">Load3_OFF",0,2);
			Load_control(Load3,OFF);
		}
		
		if (minuts>30&&minuts<33)
		{
			LCDstringXY("Load4_ON ",0,2);
			Load_control(Load4,ON);
		}
		else{
			LCDstringXY("Load4_OFF",0,2);
			Load_control(Load4,OFF);
			
		}
		
	}
	else if (hose==15)
	{
		if(minuts>30&&minuts<33)
		{
			LCDstringXY(">Load4_ON ",0,2);
			Load_control(Load4,ON);
		}
		else{
			LCDstringXY(">Load4_OFF",0,2);
			Load_control(Load4,OFF);
		}
		
		if (minuts>10&&minuts<12)
		{
			LCDstringXY("Load3_ON ",0,2);
			Load_control(Load3,ON);
		}
		else{
			LCDstringXY("Load3_OFF",0,2);
			Load_control(Load3,OFF);
			
		}
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++автоматический режим управления-начало+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AutoMode(uint8_t flag_work)
{
	char buffer[120];
	char buffer2[120];
	//******************************************************************************************
		if (flag_work==1)
		{
			while(1)
			{
				
				if (KeyPrress(Select)==1)
				{
					STop_I2C();
					LCDclear();
					
					break;
					
				}
				else{
				//функция срабатывания нагрузки по часам
				//----------------------------------------
				if (KeyPrress(Select)==1)
				{
					STop_I2C();
					LCDclear();
					
					break;
				}
				Clockds_USART();
				//Transmit_int(flag_work_load_Time);
				//Transmit_char_usart(0x0d);
				//Transmit_char_usart(0x0a);
				Load_Time(1);
				//----------------------------------------
				//опрос и вывод показания по датчику влажности
					LCDstringXY("Zone-1-ON",5,0);
					sprintf(buffer,"T1=%.1fC",Temperature_LM35(0));
					LCDstringXY(buffer,5,1);
					Indication_Load_Zone(1);
					Serv_Action(Temperature_LM35(0),flag_servo_work1);
					if (Semsor_swit(2)<2 && (flag_work_load_Time1==1))
					{
						LCDstringXY("Low    level",5,2);
						Load_control_Zone(Zone1,ON);
					}
					else if (Semsor_swit(2)>2 &&(Semsor_swit(2)<=3) && (flag_work_load_Time1==1))
					{
						LCDstringXY("Middle level",5,2);
						Load_control_Zone(Zone1,OFF);
						
					}
					else if (Semsor_swit(2)>3 && (flag_work_load_Time1==1))
					{
						LCDstringXY("High   Level",5,2);
						Load_control_Zone(Zone1,OFF);
						
					}
					
					
					
					
				}
					}
					
//********************************************************

		}
		if (flag_work==2)
		{
			while(1)
			{
				if (KeyPrress(Select)==1)
				{
					STop_I2C();
					LCDclear();
					
					break;
				}
				else{
				
				//функция срабатывания нагрузки по часам
				//----------------------------------------
				Clockds_USART();
				//Transmit_int(flag_work_load_Time);
				//Transmit_char_usart(0x0d);
				//Transmit_char_usart(0x0a);
				Load_Time(2);
				//----------------------------------------
				//опрос и вывод показания по датчику влажности
				LCDstringXY("Zone-2-ON",5,0);
				sprintf(buffer2,"T2=%.1fC",Temperature_LM35(1));
				LCDstringXY(buffer2,5,1);
				Indication_Load_Zone(2);
				Serv_Action2(Temperature_LM35(1),flag_servo_work2);
				if (Semsor_swit(3)<2 && (flag_work_load_Time2==1))
				{
					LCDstringXY("Low    level",5,2);
					Load_control_Zone(Zone2,ON);
				}
				else if (Semsor_swit(3)>2 &&(Semsor_swit(3)<=3) && (flag_work_load_Time2==1))
				{
					LCDstringXY("Midlle level",5,2);
					Load_control_Zone(Zone2,OFF);
					
				}
				else if (Semsor_swit(3)>3 && (flag_work_load_Time2==1))
				{
					LCDstringXY("High   Level",5,2);
					Load_control_Zone(Zone2,OFF);
					
				}
				
				
				
				
				}
			}
		}
		
		//*******************************************************************
		
		
		if (flag_work==3)
		{
			char buf1[80];
			char buf2[80];
			while(1){
				
				if (KeyPrress(Select)==1)
				{
					STop_I2C();
					LCDclear();
					
					break;
				}
				else{
				//----------------------------------------------
			//функция срабатывания нагрузки по часам
			//----------------------------------------
			Clockds_USART();
			//Transmit_int(flag_work_load_Time);
			//Transmit_char_usart(0x0d);
			//Transmit_char_usart(0x0a);
			Load_Time(3);
			//----------------------------------------
			//опрос и вывод показания по датчику влажности
			
			LCDstringXY("Zone-1-ON",0,0);
			LCDstringXY("|",10,0);
			LCDstringXY("Zone-2-ON",11,0);
			//----------------------------------
			sprintf(buf1,"T1=%.1fC",Temperature_LM35(0));
			LCDstringXY(buf1,0,1);
			LCDstringXY("|",10,1);
			sprintf(buf2,"T2=%.1fC",Temperature_LM35(1));
			LCDstringXY(buf2,11,1);
			//-----------------------------------
			if (Semsor_swit(2)<2 && (flag_work_load_Time1==1))
			{
				LCDstringXY("Low    lev",0,2);
				Load_control_Zone(Zone1,ON);
			}
			else if (Semsor_swit(2)>2 &&(Semsor_swit(2)<=3) && (flag_work_load_Time1==1))
			{
				LCDstringXY("Midlle lev",0,2);
				Load_control_Zone(Zone1,OFF);
				
			}
			else if (Semsor_swit(2)>3 && (flag_work_load_Time1==1))
			{
				LCDstringXY("High   Lev",0,2);
				Load_control_Zone(Zone1,OFF);
				
			}
			//-----------------------------------
			LCDstringXY("|",10,2);
			//-----------------------------------
			if (Semsor_swit(3)<2 && (flag_work_load_Time2==1))
			{
				LCDstringXY("Low   lev",11,2);
				Load_control_Zone(Zone2,ON);
			}
			else if (Semsor_swit(3)>2 &&(Semsor_swit(3)<=3) && (flag_work_load_Time2==1))
			{
				LCDstringXY("Midlle-l",11,2);
				Load_control_Zone(Zone2,OFF);
				
			}
			else if (Semsor_swit(3)>3 && (flag_work_load_Time2==1))
			{
				LCDstringXY("High  Lev",11,2);
				Load_control_Zone(Zone2,OFF);
				
			}
			//-----------------------------------
			LCDstringXY("|",10,3);
			 initializ_Load_Mode_3();
			//-----------------------------------
			
			Serv_Action_Mode3_1(Temperature_LM35(0));
			Serv_Action_Mode3_2(Temperature_LM35(1));
			//-----------------------------------------------
			
			//-----------------------------------------------
			
			
			//---------------------------------------------
			
			
			
			
			}
			}
			
		}
		

		
		}
	//=======================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++автоматический режим управления-конец+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	

//+++++++++++++++++++++++++++++++++++++++++++++
//функция вкл/выкл. нагрузки по часам !!!
void Load_Time(int Zone)
{
	
	if (hose==19)
	{
		if (minuts==10&& minuts<14)
		{
			if (Zone==1)
			{
				flag_work_load_Time1=2;
				Load_control_Zone(Zone1,ON);
			}
			else if (Zone==2)
			{
				flag_work_load_Time2=2;
				Load_control_Zone(Zone2,ON);
			}
			else if (Zone==3)
			{
				flag_work_load_Time1=2;
				flag_work_load_Time2=2;
				Load_control_Zone(Zone2,ON);
				Load_control_Zone(Zone1,ON);
			}
			
		}
		
		
	}
	else{
	flag_work_load_Time1=1;	
	flag_work_load_Time2=1;	
	}
	
	
}

//------------------------------------------------
//функция срабатывания сервоприводов.
void Serv_Action(float Temp, char flag)
{
	if (Temp>50)
	{
		ServoPrivod_One_90();
		if (flag==2)
		{
			
			LCDstringXY("S1-ON ",0,3);
		}
		else if (flag==1)
		{
			LCDstringXY("S1-OFF",0,3);
		}
	}
	else {
		ServoPrivod_One_0();
		LCDstringXY("S1-OFF",0,3);
		
	}
	
}

//------------------------------------------------
void Serv_Action_Mode3_1(float Temp)
{
	if (Temp>50)
	{
		ServoPrivod_One_90();
		
	}
	else {
		ServoPrivod_One_0();
		
	}
	
}
//------------------------------------------------
void Serv_Action_Mode3_2(float Temp)
{
	if (Temp>50)
	{
		ServoPrivod_Two_90();
		
	}
	else {
		ServoPrivod_Two_0();
		
	}
	
}
//------------------------------------------------

//функция срабатывания сервоприводов.
void Serv_Action2(float Temp, char flag)
{
	if (Temp>50)
	{
		ServoPrivod_Two_90();
		if (flag==2)
		{
			
			LCDstringXY("S2-ON ",0,3);
		}
		else if (flag==1)
		{
			LCDstringXY("S2-OFF",0,3);
		}
	}
	else {
		ServoPrivod_Two_0();
		LCDstringXY("S2-OFF",0,3);
		
	}
	
}

//------------------------------------------------
//функция работы нагрузок в зоне 

void Indication_Load_Zone(char Zone)
{
	if (Zone==1)
	{
		if (flag_Z1==1)
		{
			LCDstringXY("Z1-ON ",10,3);
			
		}
		else if (flag_Z1==0)
		{
			LCDstringXY("Z1-OFF",10,3);
		}
	}
	else if (Zone==2)
	{
		if (flag_Z2==1)
		{
			LCDstringXY("Z2-ON ",10,3);
			
		}
		else if (flag_Z2==0)
		{
			LCDstringXY("ZL2-OFF",10,3);
		}
	}
	
	
}

//-------------------------------------------------


void initializ_Load_Mode_3(void)
{
	
	if (flag_Z1==1)
	{
		LCDstringXY("Z1-ON ",0,3);
		
	}
	else if (flag_Z1==0)
	{
		LCDstringXY("Z1-OFF",0,3);
	}


	if (flag_Z2==1)
	{
		LCDstringXY("Z2-ON ",11,3);
		
	}
	else if (flag_Z2==0)
	{
		LCDstringXY("Z2-OFF",11,3);
	}
	
}
//------------------------------------------------
//функция работы отдельных нагрузок

//-------------------------------------------------


//----------------------------------------------------------подменю Settings-----------------------------------------------------------------------------------------
void MenuSettingsProcess(void)
{
	while(1)
	{
		
		
		if (KeyPrress(Select)==1)
		{
			menu_settings=MENU_SETTINGS_STATE_IDLE;
			break;
		}
		
		switch(menu_settings)
		{
			case MENU_SETTINGS_STATE_IDLE:
			{
				for ( int j=0;j<2;j++)
				{
					LCDstringXY(podstr[j],3,j+1);
				}
				_delay_ms(50);
				menu_settings=MENU_SETTINGS_STATE_WAIT;
				break;
			}
			//------------
			
			case MENU_SETTINGS_STATE_WAIT:
			{
				
				if (KeyPrress(DOWN)==1)
				{
					
					menu_settings=MENU_SETTINGS_Menu_Zone_WAIT;
					
				}
				break;
			}
			//------------------------------------
			case MENU_SETTINGS_Menu_Zone_WAIT :
			{
				LCDstringXY("->",0,1);
				
				LCDstringXY("  ",0,2);
				
				if (KeyPrress(Right)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Zone;
				}
				if (KeyPrress(DOWN)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Time_WAIT;
				}
				if (KeyPrress(UP)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Time_WAIT;
				}
				
				
				
				break;
			}
			//--------------------------------------
			case MENU_SETTINGS_Menu_Time_WAIT :
			{
				LCDstringXY("  ",0,1);
				LCDstringXY("->",0,2);
				
				if (KeyPrress(Right)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Time;
				}
				if (KeyPrress(DOWN)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Zone_WAIT;
				}
				if (KeyPrress(UP)==1)
				{
					menu_settings=MENU_SETTINGS_Menu_Zone_WAIT;
				}
				break;
			}
			//-------------------------------------------
			
			//-------------------------------------------
			
			
			case MENU_SETTINGS_Menu_Zone:
			{
				
				
				LCDclear();
				MEnuSettingsItemProcess(1);
				menu_settings=MENU_NULL;
				break;
			}
			case MENU_SETTINGS_Menu_Time:
			{
				
				
				LCDclear();
				MEnuSettingsItemProcess(2);
				menu_settings=MENU_NULL;
				break;
			}
			
			//-------------------------------------------
		}
		
		
	}
}


void MEnuSettingsItemProcess(unsigned char set)
{
	LCDclear();
	
	switch(set)
	{
		case 1:{
			
			
			//написать функцию переключения зон
			Control_Zone();
			menu_settings=MENU_NULL;
			break;
		}
		
		case 2:
		{
			
			//Menu_setTimeProcess();
			LCDclear();
			Menu_setTimeProcess();
			//LCDstringXY("TIME",0,0);
			menu_settings=MENU_NULL;
			break;
		}
		
		
	}
}

//--------------------------------------------------------------функция управления зонами-----------------------------------------

void Control_Zone(void)
{
	//дописать обработку считывания с eeprom и исходя из значения строить данные на экране !!!!
	while (1)
	{
		
		if (KeyPrress(Select)==1)
		{
			break;;
		}
	static	char  Z1=1;
	static char Z2=1;
	static char position=1;
	uint8_t flag_zzone;
	
	flag_zzone=eeprom_read_byte(flag_workZone);
	
	if (flag_zzone==1)
	{
		Z1=1;
		Z2=0;
	}
	else if (flag_zzone==2)
	{
		Z1=0;
		Z2=1;
		
	}
	else if (flag_zzone==3)
	{
		Z1=1;
		Z2=1;
		
	}
	
	
	if (KeyPrress(UP)==1)
	{
		position=1;
	}
	else if (KeyPrress(DOWN)==1)
	{
		position=2;
	}
	if (position==1)
	{
		LCDstringXY("  ",2,2);
		LCDstringXY("->",2,1);
	}
	 if (position==2)
	{
		LCDstringXY("  ",2,1);
		LCDstringXY("->",2,2);
	}
	LCDstringXY("^",10,0);
	LCDstringXY("V",10,3);
	LCDstringXY(">",18,2);
	LCDstringXY("<",0,2);
	if (position==1 && KeyPrress(Right)==1)
	{
		Z1=0;
	}
	else if (position==1 && KeyPrress(Left)==1)
	{
		Z1=1;
	}
		
		
	
	if (position==2 && KeyPrress(Right)==1)
	{
		Z2=0;
	}
	else if (position==2 && KeyPrress(Left)==1)
	{
		Z2=1;
	}
	
	if (Z1==1 && Z2==1)
	{
		LCDstringXY("Zone1-ON ",5,1);
		LCDstringXY("Zone2-ON ",5,2);
		eeprom_write_byte(&flag_workZone,3);
	}
	else if (Z1==1 && Z2==0)
	{
		LCDstringXY("Zone1-ON ",5,1);
		LCDstringXY("Zone2-OFF",5,2);
		eeprom_write_byte(&flag_workZone,1);
	}
	else if (Z1==0 && Z2==1)
	{
		LCDstringXY("Zone1-OFF",5,1);
		LCDstringXY("Zone2-ON ",5,2);
		eeprom_write_byte(&flag_workZone,2);
	}
	
	}
	
			
	
}
//-------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++контроль времени+++++++++++++++++++++++++++++++++++++++
void Menu_setTimeProcess(void)
{
	while (1)
	{
		if (KeyPrress(Select)==1)
		{
			break;
		}
		
		switch(menu_times)
		{
			case MENU_SET_Time_IDLE:
			{
				LCDstringXY("Time clock",3,1);
				LCDstringXY("Time Control",3,2);
				menu_times=MENU_SET_Time_WAIT;
				break;
			}
			
			case MENU_SET_Time_WAIT:
			{
				
				if (KeyPrress(DOWN)==1)
				{
					menu_times=MENU_SET_Time_TimeDateSetting_WAIT;
				}
				break;
			}
			
			case MENU_SET_Time_TimeDateSetting_WAIT:
			{
				LCDstringXY("->",1,1);
				LCDstringXY("  ",1,2);
				if (KeyPrress(DOWN)==1)
				{
					
					menu_times=MENU_SET_Time_TimecontrolSetting_WAIT;
					
				}
				//=========================================
			
				if (KeyPrress(UP)==1)
				{
					menu_times=MENU_SET_Time_TimecontrolSetting_WAIT;
					
				}
				//==========================================
				if (KeyPrress(Right)==1)
				{
					menu_times=MENU_SET_Time_TimeDateSetting;
					
				}
				//==========================================
				
				break;
			}
			
			
			case MENU_SET_Time_TimecontrolSetting_WAIT:
			{
				LCDstringXY("->",1,2);
				LCDstringXY("  ",1,1);
				if (KeyPrress(DOWN)==1)
				{
					
					menu_times=MENU_SET_Time_TimeDateSetting_WAIT;
					
				}
				//=========================================
				
				if (KeyPrress(UP)==1)
				{
					menu_times=MENU_SET_Time_TimeDateSetting_WAIT;
					
				}
				//==========================================
				if (KeyPrress(Right)==1)
				{
					menu_times=MENU_SET_Time_TimecontrolSetting;
					
				}
				//==========================================
				
				break;
			}
			
			case MENU_SET_Time_TimeDateSetting:
			{
				
				TimeMenuItemProcess(1);
				LCDclear();
				menu_times=Menu_Time_Null;
				break;
			}
			case MENU_SET_Time_TimecontrolSetting:
			{
				
				TimeMenuItemProcess(2);
				LCDclear();
				menu_times=Menu_Time_Null;
				break;
			}
			
		}
	}
	
}

void TimeMenuItemProcess(unsigned char val)
{
	LCDclear();
	while(1)
	{
		if (KeyPrress(Select))
		{
			break;
		}
		switch(val)
		{
			case 1:
			{
				LCDstringXY("Set Time",5,0);
				SET_TIME_clockds1307();
				menu_times=Menu_Time_Null;
				
				break;
			}
			
			case 2:
			{
				
				break;
			}
			
		}
		
		
	}
	
}

//------------------------------------------------------------------------------------------
void SET_TIME_clockds1307(void)
{
	 int hos=0;
	 int min=0;
	 int sec=0;
	unsigned char pos_time=1;
	while(1)
	{
		if (KeyPrress(Select))
		{
			
			//Устанавливаем время
			STart_I2C();
			I2C_SendByte(0b11010000);
			I2C_SendByte(0);//Переходим на 0x00
			I2C_SendByte(RTC_ConvertBinDec((unsigned char)sec)); //секунды
			I2C_SendByte(RTC_ConvertBinDec((unsigned char)min)); //минуты
			I2C_SendByte(RTC_ConvertBinDec((unsigned char)hos)); //часы
			
			STop_I2C();
			break;
			
		}
		
		
		LCDGotoXY(2,2);
		PrintInt(hos);
		LCDdataXY(':',4,2);
		LCDGotoXY(6,2);
		PrintInt(min);
		LCDdataXY(':',8,2);
		LCDGotoXY(10,2);
		PrintInt(sec);
		
		if (KeyPrress(Right)==1)
		{
			pos_time++;
			if (pos_time>3)
			{
				pos_time=1;
			}
		}
		
		if (pos_time==1)
		{
			LCDdataXY(' ',6,1);
			LCDdataXY(' ',6,3);
			
			
			LCDdataXY(' ',10,1);
			LCDdataXY(' ',10,3);
			
			
			LCDdataXY('^',2,1);
			LCDdataXY('V',2,3);
			
		}
		else if (pos_time==2)
		{
			LCDdataXY(' ',10,1);
			LCDdataXY(' ',10,3);
			
			
			LCDdataXY(' ',2,1);
			LCDdataXY(' ',2,3);
			
			LCDdataXY('^',6,1);
			LCDdataXY('V',6,3);
			
		}
		else if (pos_time==3)
		{
			LCDdataXY(' ',2,1);
			LCDdataXY(' ',2,3);
			
			LCDdataXY(' ',6,1);
			LCDdataXY(' ',6,3);
			
			LCDdataXY('^',10,1);
			LCDdataXY('V',10,3);
		}
		
		
		
		if (KeyPrress(UP)==1&& pos_time==1)
		{
			hos++;
			if (hos>23)
			{
				hos=0;
			}
		}
		else if (KeyPrress(UP)==1&& pos_time==2)
		{
			min++;
			if (min>59)
			{
				min=0;
			}
		}
		else if (KeyPrress(UP)==1&& pos_time==3)
		{
			sec++;
			if (sec>59)
			{
				sec=0;
			}
		}
		
		if (KeyPrress(DOWN)==1&& pos_time==1)
		{
			hos--;
			if (hos<0)
			{
				hos=23;
			}
		}
		else if (KeyPrress(DOWN)==1&& pos_time==2)
		{
			min--;
			if (min<0)
			{
				min=59;
			}
		}
		else if (KeyPrress(DOWN)==1&& pos_time==3)
		{
			sec--;
			if (sec<0)
			{
				sec=59;
			}
		}
		
		
		
		
	}
	
	
	LCDclear();
	LCDstringXY("Save",5,0);
	_delay_ms(500);
	LCDclear();
	
	
	
}



//--------------------------------------------------------------
//  [5/24/2017 Dante_L_Levi]

