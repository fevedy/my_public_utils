#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

int get_mac( char* mac, int len_limit)
{
    struct ifreq t_ifreq;
    int sock;

    if (( sock = socket ( AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror ("socket");
        return -1;
    }
    strcpy (t_ifreq.ifr_name, "eth0");    //TODO:可配置

    if ( ioctl( sock, SIOCGIFHWADDR, &t_ifreq) < 0)
    {
        perror ("ioctl");
        return -1;
    }
    
    //可以自己决定大小写
    return snprintf ( mac, len_limit, "%02X:%02X:%02X:%02X:%02X:%02X", (unsigned char) t_ifreq.ifr_hwaddr.sa_data[0], 
                                (unsigned char) t_ifreq.ifr_hwaddr.sa_data[1], (unsigned char) t_ifreq.ifr_hwaddr.sa_data[2], 
                                (unsigned char) t_ifreq.ifr_hwaddr.sa_data[3], (unsigned char) t_ifreq.ifr_hwaddr.sa_data[4], 
                                (unsigned char) t_ifreq.ifr_hwaddr.sa_data[5]);
}

//test
int main()
{
    char mac[ 32] = { 0};
    int nRtn = get_mac( mac, sizeof( mac));
    if( nRtn > 0)
    {
        printf("MAC ADDR: %s\n", mac);
    }
    return 0;
}
