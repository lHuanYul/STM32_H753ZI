#pragma once

#include "main/config.h"

#include "HY_MOD/packet/fdcan.h"
extern FdcanPktPool fdcan_pkt_pool;
extern FdcanPktBuf fdcan_trsm_pkt_buf;
extern FdcanPktBuf fdcan_recv_pkt_buf;
#include "HY_MOD/fdcan/basic.h"
extern FdcanParametar fdcan_h;
#include "HY_MOD/packet/json.h"
extern JsonPktPool json_pkt_pool;
extern JsonPktBuf spi_recv_buf;
extern JsonPktBuf spi_trsm_buf;
#include "HY_MOD/spi_json/basic.h"
extern SpiJsonParametar spi1_h;
// #include "HY_MOD/dht/basic.h"
// extern DhtParametar dht_h;

void INIT_OWN(void);
