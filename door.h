#ifndef _DOOR_H
#define _DOOR_H

#ifdef __cplusplus
extern "C" {
#endif


#define Gladoor 5//15 
#define Anjin_UP 12//16
#define Anjin_OFF 18//14
#define Anjin_STOP 19//12
#define Anjin_DOWN 23//13
#define Garage_Detect  13


#define Gladoor_Button_UP    HIGH// LOW
#define Gladoor_Button_DOWN  LOW//HIGH

#define Anjin_Button_UP      HIGH
#define Anjin_Button_DOWN    LOW


enum rolling_door_button
{
 rolling_door_Gladoor=1, 
 rolling_door_Anjin_UP, 
 rolling_door_Anjin_OFF, 
 rolling_door_Anjin_STOP, 
 rolling_door_Anjin_DOWN 
};


void door_init(void);
void door_handle(void);
void door_turn_off_Anjin(void);
void door_Anjin_press(int botton);
void door_Open_Garage(void);
void door_Close_Garage(void);
void door_Garage_off(unsigned short usDummyParam);
void door_detect(unsigned short usDummyParam);


#ifdef __cplusplus
} // extern "C"
#endif

#endif //_DOOR_H
