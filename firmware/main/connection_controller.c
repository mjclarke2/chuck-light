/*connection_controller.c*/
#include "lib/connection_controller.h"

#define SSID "The Super Sexys"
#define PASS "7153048030"

#define TAG "Connection Manager"

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;

static esp_err_t connection_event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        ESP_LOGI(TAG, "start");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      switch(event->event_info.disconnected.reason){
            case AUTH_EXPIRE:
              ESP_LOGI(TAG, "Auth Expired");
              goto RECON;
            break;
            case AUTH_FAIL:
              ESP_LOGI(TAG, "Auth Failed");
              goto RECON;
            break;
            case NO_AP_FOUND:
              ESP_LOGI(TAG, "AP not Found");
              goto RECON;
            break;
            default:
              ESP_LOGI(TAG, "Discon %d", event->event_info.disconnected.reason);
RECON:
              esp_wifi_connect();
              xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        }
        break;
    case SYSTEM_EVENT_WIFI_READY:
        ESP_LOGI(TAG,"WIFI READY");
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        ESP_LOGI(TAG,"SCAN DONE");
        break;
    case SYSTEM_EVENT_STA_STOP:
        ESP_LOGI(TAG,"STA STOP");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        ESP_LOGI(TAG,"STA CONNECTED");
        break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        ESP_LOGI(TAG,"STA AUTH CHANGE");
        break;
    case SYSTEM_EVENT_STA_LOST_IP:
        ESP_LOGI(TAG,"LOST IP");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
        ESP_LOGI(TAG,"STA WPS ER SUCCESS");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
        ESP_LOGI(TAG,"STA WPS ER FAILED");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
        ESP_LOGI(TAG,"STA WPS ER TIMEOUT");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
        ESP_LOGI(TAG,"STA WPS ER PIN");
        break;
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG,"AP START");
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG,"AP STOP");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG,"AP STACONNECTED");
        break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        ESP_LOGI(TAG,"AP PROBEREQRECVED");
        break;
    case SYSTEM_EVENT_AP_STA_GOT_IP6:
        ESP_LOGI(TAG,"AP STA GOT IP6");
        break;
    case SYSTEM_EVENT_ETH_START:
        ESP_LOGI(TAG,"ETH START");
        break;
    case SYSTEM_EVENT_ETH_STOP:
        ESP_LOGI(TAG,"ETH STOP");
        break;
    case SYSTEM_EVENT_ETH_CONNECTED:
        ESP_LOGI(TAG,"ETH CONNECTED");
        break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
        ESP_LOGI(TAG,"ETH DISCONNECTED");
        break;
    case SYSTEM_EVENT_ETH_GOT_IP:
        ESP_LOGI(TAG,"GOT IP");
        break;
    case SYSTEM_EVENT_MAX:
        ESP_LOGI(TAG,"EVENT MAX");
        break;

    default:
        ESP_LOGI(TAG, "EVENT %d", event->event_id);
        break;
    }
    return ESP_OK;
}

void init_connection_controller(void)
{
    wifi_config_t wifi_config;
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();


    tcpip_adapter_init();

    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(connection_event_handler, NULL) );
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    memset(&wifi_config, 0, sizeof(wifi_config));

    strcpy( (char *) wifi_config.sta.ssid, SSID );
    strcpy( (char *) wifi_config.sta.password, PASS );

    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_LOGI(TAG, "Setting WiFi configuration PASS %s...", wifi_config.sta.password);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");
}

void printConnectionInfo(void)
{
  tcpip_adapter_ip_info_t ip;
  memset(&ip, 0, sizeof(tcpip_adapter_ip_info_t));
  if (tcpip_adapter_get_ip_info(ESP_IF_WIFI_STA, &ip) == 0) {
      ESP_LOGI(TAG, "~~~~~~~~~~~");
      ESP_LOGI(TAG, "IP:"IPSTR, IP2STR(&ip.ip));
      ESP_LOGI(TAG, "Netmask:"IPSTR, IP2STR(&ip.netmask));
      ESP_LOGI(TAG, "Gateway:"IPSTR, IP2STR(&ip.gw));
      ESP_LOGI(TAG, "~~~~~~~~~~~");
  }
}
