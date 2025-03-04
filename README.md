# 魔法棒项目

## 项目概述
本项目是一个基于UNIHIKER K10的魔法棒控制器，包含魔法棒(Transmitter)和魔法帽(Receiver)两套代码。项目集成了机器学习推理功能，使用EdgeImpulse训练后的模型进行手势识别。

## 文件结构
```
├─build #发射端编译文件，基于BETT英国站训练模型
├─Case  #魔法棒外壳设计文件
├─doc   #训练过程指导
│  ├─edgeimpulse config tutorial #edgeimpulse本地转发环境配置
│  ├─magicWond data forward #数据转发，模型训练教程
│  └─magicWond press releases #魔法棒新闻稿
├─lib   #编译使用库
│  ├─DFRobot_NeoPixel
│  ├─magic-xhl_inferencing
│  └─RMT
├─resource #资源文件
│  ├─TrasmitterPic #发送端SD卡文件
│  ├─conv.cpp #替换Arduino库内文件
│  └─depthwise_conv.cpp #替换Arduino库内文件
├─src
│  ├─Receiver.cpp #接收端代码
│  ├─Train.cpp #训练时数据转发代码
│  └─Trasmitterv.cpp #发送端代码

```

## 硬件要求
- UNIHIKER K10开发板 * 3
- NeoPixel LED灯带 * 1
- 按钮 * 1

## 软件依赖
- Arduino IDE 1.8.19(需要能正常开发并上传UNIHIKER K10程序)
- DFRobot_NeoPixel库
- RMT库
- Edge Impulse机器学习推理库（magic-xhl_inferencing）

## 安装说明
1. 复制DFRobot_NeoPixel库，RMT库，Edge Impulse机器学习推理库（magic-xhl_inferencing）到Arduino IDE的libraries目录，并且配置好UNIHIKER K10 Arduino 编译环境
2. 打开Arduino IDE，新建任意.ino文件，并且将Trasmitter.cpp或者Receiver.cpp复制到.ino文件中
4. 将resource->TrasmitterPic文件夹中所有.png复制到SD卡中，插入魔法棒发送端的k10

## 使用说明
1. 将Transmitter代码上传到魔法棒k10（默认内部已经上传代码）
2. 将Receiver代码上传到魔法帽k10，并且通过代码开头的宏定义注释切换不同的帽子（默认内部已经上传代码）
#define blackHAT<br/>
//#define orangeHAT
3. 安装3节AA电池到帽子，单节CR123A电池到魔法棒
4. 按下魔法棒按键，2秒内画圆，上下摇晃或者左右摇晃来控制魔法帽
上下摇晃，让黑色帽子动
左右摇晃，让橘色帽子动
画圆，让两个帽子停下

## 注意事项
- 魔法棒按钮本来并没有下拉电阻，很容易误触发，所以制作过程中在按钮背部手动焊接了下拉电阻。
- 魔法棒的P0接灯带，P1接按钮
- 魔法棒使用单节CR123A电池供电，续航时间约为3小时。
因为发射信息时候使用ESPNOW协议较为耗电，会突然拉低电池电压。
所以魔法棒快要没电的表现为发射信号的时候突然白屏重启，此时需要更换电池，掀开背部磁吸电池仓直接更换。

- 魔法帽中的三节AA电池(5号电池)同时给魔法帽的舵机以及K10本体供电，关闭屏幕后续航时间约为1~2小时
- 魔法帽通过继电器控制，继电器统一接到魔法帽k10内部的P0引脚

## 训练过程
EdgeImpulse: https://edgeimpulse.com/<br/>
项目链接：https://studio.edgeimpulse.com/studio/587543<br/>
指导过程：该仓库的doc文件夹下，先查看config tutorial，再查看data forward<br/>

- 如果后续想要新增手势，需要登录EdgeImpulse网站并且打开项目。
- 在魔法棒K10上上传scr->Train.cpp，并且打开串口监视器，确保串口输出有加速度传感器数据
- 配置edgeimpulse数据上传环境（参考doc->config tutorial文档）
- 选择数据上传到magic-xhl这个项目（参考doc->magic Wond data forward）
- 导出arduino library之后，使用该仓库中的resource->conv.cpp,depthwise_conv.cpp替换导出Arduino库中的magic-xhl_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels文件夹下的同名文件
- 将Transmit.cpp上传到魔法棒发射端UNHIKER K10即可