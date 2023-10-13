#!/usr/bin/env python

import subprocess
import json
import re

devices = []

# 获取已连接蓝牙设备列表
connected_devices = (
    subprocess.check_output(["bluetoothctl", "devices", "Connected"])
    .decode("utf-8")
    .splitlines()
)

# 提取设备MAC地址和名称
formatted_devices = []
for device in connected_devices:
    mac = device.split()[1]
    name = ' '.join(device.split()[2:])
    formatted_devices.append({"mac": mac, "name": name})

# 遍历每个设备
for device in formatted_devices:

    # 获取设备的电池信息
    battery = -1
    battery_output = subprocess.check_output(["bluetoothctl", "info", device['mac']]).decode("utf-8")
    battery_line = next(
        (line for line in battery_output.splitlines() if "Battery Percentage:" in line),
        None,
    )
    if battery_line:
        battery = int(re.search(r'\((\d+)\)', battery_line).group(1))

    # 构建设备字典
    device_info = {"mac": device['mac'], "name": device['name'], "battery": battery}

    # 将设备字典添加到设备列表中
    devices.append(device_info)

# 输出设备列表为JSON数组
print(json.dumps(devices))

