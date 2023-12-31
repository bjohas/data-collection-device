﻿# 定时采样传感器规格列表

### 修订历史
|  | 时间| 备注|
| --- | --- | --- |
| 1 | 2023/6/23 | 添加产品说明与测量精度|
| 2 | 2023/6/26 | 根据实际测量修改产品尺寸，添加实物图片，补充使用方法，加入注意事项 |


### 产品说明
| 名称 | 规格|
| --- | --- |
| 产品尺寸 | 64.8X37.9X38.8 (mm X mm X mm) | 
| 实物图片 |![输入图片说明](/imgs/device.jpg) |
| 电源 | 2节5号电池 + 1节纽扣电池CR2032 |
| 使用寿命 | 6000h（以电池电量800mAh，采样间隔1h计算，平均消耗电量0.133mAh/h）
| 功能 | 以指定频率测量光照，温度，湿度，声强数据，并记录，可以以USB接口读出数据|
| 使用方法 | 初始先用USB线插入电脑，设备作为U盘接入电脑，运行U盘内的config.py(需要电脑已安装python)，输入每几小时采样一次，设备则会存下当前本机时间进行校准设备时间，以及存下采样时间间隔。安装电池，打开开关，设备则会以给定时间间隔进行采样，并把数据以csv的格式进行存储。每日存储一个csv文件，名称为FCyymmdd.CSV，如FC230601.CSV.|
|注意事项| 1.在校准时间成功后设备指示灯会闪烁一下; 2.在电池电压不足时设备指示灯会在USB电源插入后频闪.|

### 测量精度
（实验室环境下测试）
| 指标 | 精度|
| --- | --- |
|光照| +-10% (0~65535lux) |
| 温度 | +-3摄氏度 (0~85度) |
| 湿度 | +-2% (0~100%)|
| 声强 | +-3dB (35~100dB)|




