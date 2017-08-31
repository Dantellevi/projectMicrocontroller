#include "MainMenu.h"
#include "Messege.h"
#include <avr/pgmspace.h>

  typedef struct  {
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t      Select;
	 char   Text[];
}menuItem __attribute__((progmem))  ;


 

 menuItem* selectedMenuItem ; // текущий пункт меню

menuItem* menuStack[10] ;
 uint8_t  menuStackTop  ;



#define MAKE_MENU(Name, Next, Previous, Parent, Child, Select, Text) \
extern  menuItem Next;    \ 
extern  menuItem Previous; \
extern  menuItem Parent;   \
extern  menuItem Child;  \
menuItem  Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child,Select, { Text }}

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))
#define SELECT		(pgm_read_byte(&selectedMenuItem->Select))

const char  strNULL [] __attribute__((progmem))= "";


#define  NULL_ENTRY Null_Menu

 menuItem Null_Menu={(void*)0, (void*)0, (void*)0, (void*)0, 0, {0x00}};
	
	/*
					^
					|
				Previuos
		<-Parent			child->
				   Next
					|
					V		
	*/
	
	
	
	
	//основное меню работы
	//------------------------------------------------------------------------
	//        |Name   |Next   |Previos    |PARENT     |Child |select |Text
	MAKE_MENU(m_s1i1,m_s1i2,NULL_ENTRY,NULL_ENTRY,m_s2i1,0,"START Work");
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//        |Name   |Next   |Prev  |PARENT   |Child |select |Text
	 MAKE_MENU(m_s1i2,m_s1i3,m_s1i1,NULL_ENTRY,m_s3i1,0,"Settings Work");
	 
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//        |Name   |Next   |Prev  |PARENT   |Child |select |Text
	MAKE_MENU(m_s1i3,NULL_ENTRY,m_s1i2,NULL_ENTRY,m_s4i1,0,"Settings Time"); 
	//------------------------------------------------------------------------- 


//подменю запуска
//--------------------------------------------------------------
//           |Name   |Next   |Prev  |PARENT   |Child |select |Text
	MAKE_MENU(m_s2i1,m_s2i2,NULL_ENTRY,m_s1i1,NULL_ENTRY,Menu_Mode1,"Auto Mode");
	MAKE_MENU(m_s2i2,m_s2i3,m_s2i1,m_s1i1,NULL_ENTRY,Menu_Mode2,"Manual Mode");
	MAKE_MENU(m_s2i3,m_s2i4,m_s2i2,m_s1i1,NULL_ENTRY,Menu_Mode3,"Auto Mode +");
	MAKE_MENU(m_s2i4,m_s2i5,m_s2i3,m_s1i1,NULL_ENTRY,Menu_Mode4,"Testing Mode...");
	MAKE_MENU(m_s2i5,NULL_ENTRY,m_s2i4,m_s1i1,NULL_ENTRY,Menu_Mode5,"USART Mode...");
	
//--------------------------------------------------------------

//подменю настроек
//--------------------------------------------------------------
 //          |Name   |Next   |Prev  |PARENT   |Child |select |Text
   MAKE_MENU(m_s3i1,m_s3i2,NULL_ENTRY,m_s1i2,NULL_ENTRY,Menu_Zone1,"Settings Zone 1");
   MAKE_MENU(m_s3i2,NULL_ENTRY,m_s3i1,m_s1i2,NULL_ENTRY,Menu_Zone2,"Settings Zone 2");
//--------------------------------------------------------------

//подменю времени
//--------------------------------------------------------------
 //        |Name   |Next   |Prev  |PARENT   |Child |select |Text
 MAKE_MENU(m_s4i1,m_s4i2,NULL_ENTRY,m_s1i3,NULL_ENTRY,Menu_settings_Time,"Settings Real Time");
 MAKE_MENU(m_s4i2,NULL_ENTRY,m_s4i1,m_s1i3,NULL_ENTRY,Menu_timeMode3,"Settings Mode-Auto Mode +");
//--------------------------------------------------------------


void menuChange(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	return;

	selectedMenuItem = NewMenu;
}



unsigned char dispMenu(msg_par par) {
	menuItem* tempMenu;

	LCDclear();;
	// первая строка - заголовок. Или пункт меню верхнего уровня
	LCDGotoXY(1,0);
	tempMenu = (menuItem*)pgm_read_word(&selectedMenuItem->Parent);
	if ((void*)tempMenu == (void*)&NULL_ENTRY) { // мы на верхнем уровне
		LCDsendString(PSTR("MENU:"));
		} else {
		LCDsendString((char *)tempMenu->Text);
	}

	LCDclear();
	// Вторая строка - текущий пункт меню
	LCDGotoXY(2,1);
	LCDsendString((char *)selectedMenuItem->Text);

	return (1);
}

uint8_t menuKey(msg_par par) {
	switch (par) {
		case 0: {
			return 1;
		}
		case KEY_LEFT: {
			menuChange(PREVIOUS);
			break;
		}
		case KEY_RIGHT: {
			menuChange(NEXT);
			break;
		}
		case KEY_DOWN:
		;
		case KEY_OK:
		{ // выбор пункта
			uint8_t sel;
			sel = SELECT;
			if (sel != 0) {
				sendMessage(MSG_MENU_SELECT, sel);

				killHandler(MSG_KEY_PRESS, &menuKey);
				killHandler(MSG_DISP_REFRESH, &dispMenu);

				return (1);
				} else {
				menuChange(CHILD);
			}
			break;
		}
		case KEY_UP: { // отмена выбора (возврат)
			menuChange(PARENT);
		}
	}
	dispMenu(0);
	return (1);
}

uint8_t startMenu() {
	selectedMenuItem = (menuItem*)&m_s1i1;

	dispMenu(0);
	setHandler(MSG_KEY_PRESS, &menuKey);
	setHandler(MSG_DISP_REFRESH, &dispMenu);
	return (0);
}

void initMenu() {
LCDinit();
}


