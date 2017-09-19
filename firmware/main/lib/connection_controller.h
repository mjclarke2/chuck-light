/*connection_controller.h*/
#ifndef CONNECTION_CONTROLLER_H
#define CONNECTION_CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#define AUTH_EXPIRE 2
#define AUTH_FAIL 202
#define NO_AP_FOUND 201

static esp_err_t connection_event_handler(void *ctx, system_event_t *event);
void initialise_wifi(void);
void printConnectionInfo(void);

#endif
