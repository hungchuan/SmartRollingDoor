#include "general.h"




static T_Dev_data My_Device[DEVICE_MAX];//[DEVICE_MAX];

//ryan: 192.168.68.101      
//emma: 192.168.68.103
void device_init(void)
{
    //memset(My_Device[0].device_ip, '\0', lenOfName2);
    My_Device[0].loc_update_flag=false;
    My_Device[1].loc_update_flag=false;
    strcpy(My_Device[0].device_ip, "192.168.68.101");
    strcpy(My_Device[1].device_ip, "192.168.68.103");
    //My_Device[0].device_ip="192.168.68.101";
    //My_Device[1].device_ip="192.168.68.103";        
}
//====================================================================================
void device_handle(void)
{
    char* ip;
    
    if (true==My_Device[0].loc_update_flag)
    {
        Serial.println("device_handle____0");       
        My_Device[0].loc_update_flag=false;
        //strcpy(ip,My_Device[0].device_ip);
        wifi_ping(My_Device[0].device_ip);
    }

    if (true==My_Device[1].loc_update_flag)
    {
        Serial.println("device_handle____1");     
        My_Device[1].loc_update_flag=false;
        wifi_ping(My_Device[1].device_ip);

    }

}
//====================================================================================
void device_get_ip(int dev, char* ip)
{
    strcpy(ip,My_Device[dev].device_ip);
}
//====================================================================================
void device_set_loction(int dev, float dLat,float dLon)
{
    My_Device[dev].loc_update_flag=true;
    My_Device[dev].lat=dLat;
    My_Device[dev].lon=dLon;
}
//====================================================================================
bool device_ip_tracking(int dev)
{
    return (wifi_ping(My_Device[dev].device_ip));
}
//====================================================================================

