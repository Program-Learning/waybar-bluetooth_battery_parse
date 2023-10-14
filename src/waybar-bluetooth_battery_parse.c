#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_DEVICES 10
#define BUFFER_SIZE 1024

// Structure for device information
typedef struct {
    char mac[18];
    char name[100];
    int battery;
} Device;

void getConnectedBluetoothDevices(Device devices[], int *deviceCount) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char command[] = "bluetoothctl devices Connected";
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Error executing command.\n");
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char mac[18];
        char name[100];
        sscanf(buffer, "Device %17s %99[^\n]", mac, name);

        int battery = -1;
        char infoCommand[BUFFER_SIZE];
        sprintf(infoCommand, "bluetoothctl info %s", mac);
        FILE* infoFp = popen(infoCommand, "r");
        if (infoFp != NULL) {
            while (fgets(buffer, BUFFER_SIZE, infoFp) != NULL) {
                if (strstr(buffer, "Battery Percentage:") != NULL) {
                    sscanf(buffer, "%*[^()] (%d)", &battery);
                    break;
                }
            }
            pclose(infoFp);
        }

        Device device;
        strcpy(device.mac, mac);
        strcpy(device.name, name);
        device.battery = battery;

        devices[(*deviceCount)++] = device;
    }

    pclose(fp);
}

int main() {
    Device devices[MAX_DEVICES];
    int deviceCount = 0;

    while (1) {
        deviceCount = 0;
        getConnectedBluetoothDevices(devices, &deviceCount);

        if (deviceCount == 0) {
            printf("{\"text\": \"No device is connected\"}");
        } else {
            printf("{\"text\": \"%d device is connected\", \"class\": \"class\", \"tooltip\": \"", deviceCount);
            for (int i = 0; i < deviceCount; i++) {
                printf("%s: %d%%", devices[i].name, devices[i].battery);
                if (i < deviceCount - 1) {
                    printf("\\n");
                }
            }
            printf("\", \"alt\": \"");
            for (int i = 0; i < deviceCount; i++) {
                printf("%s: %d%%", devices[i].name, devices[i].battery);
                if (i < deviceCount - 1) {
                    printf("\\n");
                }
            }
            printf("\"}\n");
        }
        fflush(stdout);

        sleep(60);
    }

    return 0;
}

