#ifndef ETHERNET_H_
#define ETHERNET_H_

#include <linux/if_tun.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include <linux/if_ether.h>




struct eth_hdr{
    unsigned char dmc[6];
    unsigned char smac[6];
    uint16_t ethertype;
    unsigned char payload[];
}__attribute__((packed));



#endif
