#ifndef _DEVICE_H
#define _DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEVICE_MAX	10
#define _id_len_ 32

typedef struct {
  char id[_id_len_]; 
  char device_ip[_id_len_];
  float lat;
  float lon;
  bool loc_update_flag;
  } T_Dev_data;


void device_init(void);
void device_handle(void);
void device_get_ip(int dev, char* ip);
void device_set_loction(int dev, float dLat,float dLon);
bool device_ip_tracking(int dev);



#ifdef __cplusplus
} // extern "C"
#endif

#endif 

