#include "general.h"


//Ryan begin
#ifndef ledPin
#define ledPin 2 // GPIO2
#endif

#ifndef button
#define button 0 //gpio to use to trigger delay
#endif


//T_MN_Event event;
static T_TMR_Timer TimerId = -1;
T_MN_Event event;
void *msg;


volatile byte LED_Active = LOW;

void IRAM_ATTR BlinkLed(unsigned short usDummy)
{   
   digitalWrite(ledPin, LED_Active);	   
   LED_Active = !LED_Active;
}

void IamAlive(void)
{
   /* Init SW timer to blink led#0 every one second */
   if(TimerId == (T_TMR_Timer)-1)
		TimerId = TMR_TimerAdd(TMR_Cyclic, BlinkLed, 0);
	/* and start it */
	TMR_TimerStart(TimerId, 1000);
}

void gpio_init()
{
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);    
  //pinMode(buttonPin, INPUT);
}

void setup() {
	
  gpio_init();  
  uart_init_0();
  Evnet_Init();
  timer_init2();
  nvm_init();

  wifi2_init(); 
  webpage_init(); //after wifi init
	 
  
  Serial.println();
  Serial.print("Hardware ID =");Serial.println(nvm_get_HW_ID());
  if (nvm_get_HW_ID()>1000)
  {
	  nvm_set_HW_ID(999);
	  Serial.print("Hardware ID =");Serial.println(nvm_get_HW_ID());
  }

  mqtt_init();
  door_init();
  thingspeak_init();
  device_init();
  wdt_init(); 
  IamAlive();
 
}
//====================================================================================================================
void loop() {
	wdt_handle();
	webpage_handleClient();
	uart_handle();
	mqtt_handle();


	/* Get new event */
	event = Event_GetEvent((void **)&msg);

	switch (event)
	{
		case MN_WifiCheck: 				/*	operator instruction */
              wifi2_handle();
	  	    break;
		case MN_mqttCheck: 				
              //mqtt_handle();	
		    break; 
		case MN_SaveSettings: 				/*	operator instruction */
            nvm_handle();
	  	    break; 
		case MN_DoorOff: 				
            door_turn_off_Anjin();
	  	    break; 	
		case MN_DoorDetect: 				
             door_handle();
	  	    break; 	
		case MN_thingspeak_upload: 				
             thingspeak_handle();
	  	    break; 			
		case MN_location: 				
             device_handle();
	  	    break; 				
	}

}
//====================================================================================================================

//====================================================================================================================
