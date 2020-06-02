#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "dawn_iwinfo.h"
#include "utils.h"
#include "ieee80211_utils.h"

#include "datastorage.h"
#include "uface.h"

/*** External functions ***/
void ap_array_insert(ap entry);
ap ap_array_delete(ap entry);

/*** Testing structures, etc ***/
union __attribute__((__packed__)) mac_mangler
{
    struct {
        uint8_t b[6];
        uint8_t packing[2];
    } u8;
    uint64_t u64;
};

/*** Test Stub Fubctions - Called by SUT ***/
void ubus_send_beacon_report(uint8_t client[], int id)
{
    printf("send_beacon_report() was called...\n");
}

int send_set_probe(uint8_t client_addr[])
{
    printf("send_set_probe() was called...\n");
    return 0;
}

void wnm_disassoc_imminent(uint32_t id, const uint8_t* client_addr, char* dest_ap, uint32_t duration)
{
    printf("wnm_disassoc_imminent() was called...\n");
}

void add_client_update_timer(time_t time)
{
    printf("add_client_update_timer() was called...\n");
}

void del_client_interface(uint32_t id, const uint8_t* client_addr, uint32_t reason, uint8_t deauth, uint32_t ban_time)
{
    printf("del_client_interface() was called...\n");
}

int ubus_send_probe_via_network(struct probe_entry_s probe_entry)
{
    printf("send_probe_via_network() was called...\n");
    return 0;
}

int get_rssi_iwinfo(uint8_t* client_addr)
{
    printf("get_rssi_iwinfo() was called...\n");
    return 0;
}

int get_expected_throughput_iwinfo(uint8_t* client_addr)
{
    printf("get_expected_throughput_iwinfo() was called...\n");
    return 0;
}

int get_bandwidth_iwinfo(uint8_t* client_addr, float* rx_rate, float* tx_rate)
{
    printf("get_bandwidth_iwinfo() was called...\n");
    return 0;
}

/*** Local Function Prototypes ***/
int ap_array_helper_auto(int action, int i0, int i1);
int client_array_helper_auto(int action, int i0, int i1);
int auth_entry_array_helper_auto(int action, int i0, int i1);
int probe_array_helper_auto(int action, int i0, int i1);

/*** Test code */
int ap_array_helper_auto(int action, int i0, int i1)
{
    int m;
    int step = (i0 > i1) ? -1 : 1;
    int ret = 0;

    switch (action)
    {
    case 0:
    case 1:
        m = i0;
        int cont = 1;
        while (cont) {
            union mac_mangler this_mac;
            ap ap0;

            this_mac.u64 = m;
            memcpy(ap0.bssid_addr, this_mac.u8.b, sizeof(ap0.bssid_addr));
            if (action == 0)
                ap_array_insert(ap0);
            else
                ap_array_delete(ap0);

            if (m == i1)
                cont = 0;
            else
                m += step;
        }
        break;
    default:
        ret = 1;
        break;
    }

    return ret;
}

int client_array_helper_auto(int action, int i0, int i1)
{
    int m;
    int step = (i0 > i1) ? -1 : 1;
    int ret = 0;

    switch (action)
    {
    case 0:
    case 1:
        m = i0;
        int cont = 1;
        while (cont) {
            union mac_mangler this_mac;
            client client0;

            this_mac.u64 = m;
            memcpy(client0.bssid_addr, this_mac.u8.b, sizeof(client0.bssid_addr));
            memcpy(client0.client_addr, this_mac.u8.b, sizeof(client0.client_addr));
            if (action == 0)
                client_array_insert(client0);
            else
                client_array_delete(client0);

            if (m == i1)
                cont = 0;
            else
                m += step;
        }
        break;
    default:
        ret = 1;
        break;
    }

    return ret;
}

int auth_entry_array_helper_auto(int action, int i0, int i1)
{
    int m;
    int step = (i0 > i1) ? -1 : 1;
    int ret = 0;

    switch (action)
    {
    case 0:
    case 1:
        m = i0;
        int cont = 1;
        while (cont) {
            union mac_mangler this_mac;
            auth_entry auth_entry0;

            this_mac.u64 = m;
            memcpy(auth_entry0.bssid_addr, this_mac.u8.b, sizeof(auth_entry0.bssid_addr));
            memcpy(auth_entry0.client_addr, this_mac.u8.b, sizeof(auth_entry0.client_addr));
            if (action == 0)
                denied_req_array_insert(auth_entry0);
            else
                denied_req_array_delete(auth_entry0);

            if (m == i1)
                cont = 0;
            else
                m += step;
        }
        break;
    default:
        ret = 1;
        break;
    }

    return ret;
}

int probe_array_helper_auto(int action, int i0, int i1)
{
    int m;
    int step = (i0 > i1) ? -1 : 1;
    int ret = 0;

    switch (action)
    {
    case 0:
    case 1:
        m = i0;
        int cont = 1;
        while (cont) {
            union mac_mangler this_mac;
            probe_entry probe0;

            this_mac.u64 = m;
            memcpy(probe0.bssid_addr, this_mac.u8.b, sizeof(probe0.bssid_addr));
            memcpy(probe0.client_addr, this_mac.u8.b, sizeof(probe0.client_addr));
            if (action == 0)
                probe_array_insert(probe0);
            else
                probe_array_delete(probe0);

            if (m == i1)
                cont = 0;
            else
                m += step;
        }
        break;
    default:
        ret = 1;
        break;
    }

    return ret;
}

int main(int argc, char** argv)
{
int ret = 0;
int args_ok = 1;
int args_required = 0; // Suppress compiler warming by assigning initial value

    printf("DAWN datastorage.c test harness.  Ready for commands...\n");

    /* Step past command name on args, ie argv[0]*/
    int curr_arg = 1;
    argv++;

    while (curr_arg < argc && args_ok)
    {
        if (strcmp(*argv, "help") == 0)
        {
            args_required = 1;
	        if (curr_arg + args_required > argc) goto next_command;

	        printf("Help is on its way...\n");
        }
        else if (strcmp(*argv, "ap_show") == 0)
        {
            args_required = 1;
            if (curr_arg + args_required > argc) goto next_command;

            print_ap_array();
        }
        else if (strcmp(*argv, "probe_show") == 0)
        {
            args_required = 1;
            if (curr_arg + args_required > argc) goto next_command;

            print_probe_array();
        }
        else if (strcmp(*argv, "probe_sort") == 0)
        {
            args_required = 2;
            if (curr_arg + args_required > argc) goto next_command;

            sort_string = argv[1];
        }
        else if (strcmp(*argv, "client_show") == 0)
        {
            args_required = 1;
            if (curr_arg + args_required > argc) goto next_command;

            print_client_array();
        }
        else if (strcmp(*argv, "auth_entry_show") == 0)
        {
            args_required = 1;
            if (curr_arg + args_required > argc) goto next_command;

            printf("--------APs------\n");
            for (int i = 0; i <= denied_req_last; i++) {
                print_auth_entry(denied_req_array[i]);
            }
            printf("------------------\n");
        }
        else if (strcmp(*argv, "ap_add_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            ap_array_helper_auto(0, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "ap_del_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            ap_array_helper_auto(1, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "probe_add_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            probe_array_helper_auto(0, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "probe_del_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            probe_array_helper_auto(1, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "client_add_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            client_array_helper_auto(0, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "client_del_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            client_array_helper_auto(1, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "auth_entry_add_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            auth_entry_array_helper_auto(0, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else if (strcmp(*argv, "auth_entry_del_auto") == 0)
        {
            args_required = 3;
            if (curr_arg + args_required > argc) goto next_command;

            auth_entry_array_helper_auto(1, atoi(*(argv + 1)), atoi(*(argv + 2)));
        }
        else
	    {
            args_required = 1;
	        if (curr_arg + args_required > argc) goto next_command;

	        printf("COMMAND \"%s\": Unknown - skipping!\n", *argv);
	    }

next_command:
	    curr_arg += args_required;
        if (curr_arg <= argc)
        {
            // Still need to continue consuming args
            argv += args_required;
        }
        else
        {
            // There aren't enough args left to give the parameters of the current action
            printf("Commands are mangled at: \"%s\"!\n", *argv);
            args_ok = 0;
        }
    }

    printf("\n\nDAWN datastorage.c test harness - finshed.  \n");

    return ret;
}
