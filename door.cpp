#include "general.h"

static T_TMR_Timer door_off_TimerId = -1;
static T_TMR_Timer door_detect_TimerId = -1;

bool is_garage_open=false;

void door_init(void)
{
  pinMode(Garage_Detect, INPUT);
  pinMode(Gladoor, OUTPUT);	
  pinMode(Anjin_UP, OUTPUT);	
  pinMode(Anjin_OFF, OUTPUT);	
  pinMode(Anjin_STOP, OUTPUT);	
  pinMode(Anjin_DOWN, OUTPUT);

  digitalWrite(Gladoor, Gladoor_Button_UP);
  digitalWrite(Anjin_UP, Anjin_Button_UP);
  digitalWrite(Anjin_OFF, Anjin_Button_UP);
  digitalWrite(Anjin_STOP, Anjin_Button_UP);
  digitalWrite(Anjin_DOWN, Anjin_Button_UP);  

  //mqtt_set_garage_publish(digitalRead(Garage_Detect));

  if (digitalRead(Garage_Detect) == CLOSE) 
  {
	 is_garage_open = false;
      mqtt_set_garage_publish(CLOSE);		
  }
  else
  {
	  is_garage_open = true;
       mqtt_set_garage_publish(OPEN);	
  }
	
  
   if(door_off_TimerId == (T_TMR_Timer)-1)
	   door_off_TimerId= TMR_TimerAdd(TMR_OneShot, door_Garage_off, 0);

   if(door_detect_TimerId == (T_TMR_Timer)-1)
	   door_detect_TimerId= TMR_TimerAdd(TMR_Cyclic, door_detect, 0); 

   TMR_TimerStart(door_detect_TimerId, 2000);
 
}
//================================================================================================
void door_handle(void)
{
    if (digitalRead(Garage_Detect) == CLOSE) 
    {
        Serial.println("garage_detect LOW");
	
        if (true == is_garage_open)	
	   {
	       mqtt_set_publish(msg_Garage_OFF);
            TMR_TimerStart(door_off_TimerId, 3000);
	    }
         is_garage_open = false;				
	}
	else
	{
	    Serial.println("garage_detect HIGH");

         if (false == is_garage_open)	
	    {
             mqtt_set_publish(msg_Garage_ON);	
	    }			
	    is_garage_open = true;			
	}    
}
//======================================================================================================================
void door_turn_off_Anjin(void)
{
     Serial.println(__FUNCTION__);
	door_Anjin_press(Anjin_OFF);
}
//======================================================================================================================
void door_Anjin_press(int botton)
{
    digitalWrite(botton, Anjin_Button_DOWN);
	delay(500);
	digitalWrite(botton, Anjin_Button_UP);	
}
//======================================================================================================================
void door_Open_Garage(void)
{
    Serial.println("Anjin_Open");
	door_Anjin_press(Anjin_STOP);
	delay(500);
	door_Anjin_press(Anjin_UP);
}
//======================================================================================================================
void door_Close_Garage(void)
{
    Serial.println("Anjin_Close");
	door_Anjin_press(Anjin_DOWN);
    TMR_TimerStart(door_off_TimerId, 10000);
    
}
//================================================================================================
void IRAM_ATTR door_Garage_off(unsigned short usDummyParam)
{
	Event_EventSend(MN_DoorOff, (void *)NULL);
}
//================================================================================================
void IRAM_ATTR door_detect(unsigned short usDummyParam)
{
	Event_EventSend(MN_DoorDetect, (void *)NULL);
}
//================================================================================================
