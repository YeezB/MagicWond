# 魔法棒模型训练教程
访问EdgeImpulse网站并登录
可以直接fork现成的EdgeImpulse项目进行修改，或者自己新建项目

EdgeImpulse: https://edgeimpulse.com/<br/>
项目链接：https://studio.edgeimpulse.com/studio/587543<br/>

# 网页面板一览
![EIPanel](../resource/DocPic/EIpanel.png)

# 训练过程
## 烧录训练代码
访问[训练代码工程](../src/ModelTrain/)并烧录

## 数据转发
打开powershell，输入以下指令将串口数据转发到EdgeImpulse
```bash
edge-impulse-data-forwarder --frequency 100
```
按照提示输入EdgeImpulse平台的账号和密码，给串口数据的标签为x,y,z，给设备起一个名字为esp32，让K10连接上平台
![dataforward](../resource/DocPic/dataforward.png)
![dataforward1](../resource/DocPic/dataforward1.png)

## 采样
选择数据采集部分，label填运动传感器数据的标签，采样时长选2000ms，即可开始采样
![sample](../resource/DocPic/sample.png)

## 查看数据分布
选择查看数据分布，针对性的修改数据
![checkdata](../resource/DocPic/checkdata.png)

## 定义网络结构
自定义网络结构，并保存
![NetworkSEL](../resource/DocPic/networkSEL.png)

## 生成特征值
生成特征值
![Feat](../resource/DocPic/feature.png)
![Feat2](../resource/DocPic/fear2.png)

## 训练模型
![train](../resource/DocPic/train.png)

## 导出模型
![deploy](../resource/DocPic/deploy.png)
