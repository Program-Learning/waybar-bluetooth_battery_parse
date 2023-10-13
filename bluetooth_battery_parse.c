#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEVICES 10
#define BUFFER_SIZE 1024

// Structure for device information
typedef struct {
    char mac[18];
    char name[100];
    int battery;
} Device;

int main() {
    Device devices[MAX_DEVICES];
    int deviceCount = 0;

    // Execute bluetoothctl command to get connected devices
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char command[] = "bluetoothctl devices Connected";
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Error executing command.\n");
        return 1;
    }

    // Read the output of the command
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        // Extract MAC address and name
        char mac[18];
        char name[100];
        sscanf(buffer, "%*s %s %[^\n]", mac, name);

        // Get battery percentage
        int battery = -1;
        char infoCommand[BUFFER_SIZE];
        sprintf(infoCommand, "bluetoothctl info %s", mac);
        FILE* infoFp = popen(infoCommand, "r");
        if (infoFp != NULL) {
            while (fgets(buffer, BUFFER_SIZE, infoFp) != NULL) {
                if (strstr(buffer, "Battery Percentage:") != NULL) {
                    sscanf(buffer, "%*s (%d)", &battery);
                    break;
                }
            }
            pclose(infoFp);
        }

        // Create new device struct
        Device device;
        strcpy(device.mac, mac);
        strcpy(device.name, name);
        device.battery = battery;

        // Add the device to the array
        devices[deviceCount++] = device;
    }

    pclose(fp);

    // Output devices as JSON array
    printf("[");
    for (int i = 0; i < deviceCount; i++) {
        printf("{\"mac\":\"%s\",\"name\":\"%s\",\"battery\":%d}", devices[i].mac, devices[i].name, devices[i].battery);
        if (i < deviceCount - 1) {
            printf(",");
        }
    }
    printf("]\n");

    return 0;
}

