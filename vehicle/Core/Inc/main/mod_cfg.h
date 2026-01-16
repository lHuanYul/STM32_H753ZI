#pragma once

#include "main/config.h"
#include "HY_MOD/fdcan/basic.h"
#include "HY_MOD/packet/fdcan.h"
#include "HY_MOD/spi_json/basic.h"
#include "HY_MOD/packet/json.h"

extern FdcanPktPool fdcan_pkt_pool;

extern FdcanPktBuf fdcan_trsm_pkt_buf;
extern FdcanPktBuf fdcan_recv_pkt_buf;

extern FdcanParametar fdcan_h;

extern SpiParametar spi1_h;

extern JsonPktPool json_pkt_pool;
extern JsonPktBuf spi_recv_buf;
extern JsonPktBuf spi_trsm_buf;
