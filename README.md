# SSB-Web

本仓库是为易迈科技 RFID无人购物解决方案制作的原型。内含若干子项目


1. [hardware](./hardware):

无人购物车RFID识别终端，用于挂载在普通购物车上帮助用户进行自主购物。 


| 模块          |解决方案             | 
| ------------- |--------------------|
| 主控     | 意法半导体 stm32f103c8t6 |
| 通信     | 移远 BC26 NB-IOT         |
| RFID识别 | 恩智浦 MFRC522           |

本目录主要存储为主控芯片编写的固件。（固件基于 `STM32duino` + `FreeRTOS` ，使用 `cpp` 语言编写)

2. [ssb-front](./ssb-front) + [SSBClient](./SSBClient)

无人购物车用户终端，用于使能用户自助结账及管理已购买商品。

使用 `Typescript` + `React` + `Ant design`实现用户界面及主要的交互逻辑，使用 `java` 编写了 `native` 容器, 并在容器中完成条形码及二维码扫描功能。`  java Native` 程序通过 `webview` 和`React` 前端一起作为 `Hybrid App` 交付

3. [SSBWeb](./SSBWeb)

后端服务器，负责处理核心业务逻辑，使用 `django` + `django-restframework` + `django-channels`编写。

4. [tcpserver](./tcpserver)

负责处理RFID识别终端中NBIOT模组与服务器的TCP自由通信，使用 `python` + `tornado` 实现。
