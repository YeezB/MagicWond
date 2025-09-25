# Magic Wand Model Training Tutorial
Visit the EdgeImpulse website and log in.
You can either fork an existing EdgeImpulse project for modification or create a new project.

EdgeImpulse: https://edgeimpulse.com/<br/>
Project Link: https://studio.edgeimpulse.com/studio/587543<br/>

# Web Panel Overview
![EIPanel](../resource/DocPic/EIpanel.png)

# Training Process
## Flash Training Code
Visit the [training code project](../src/ModelTrain/) and flash it.

## Data Forwarding
Open PowerShell and enter the following command to forward serial data to EdgeImpulse:
```bash
edge-impulse-data-forwarder --frequency 100
```
Follow the prompts to enter your EdgeImpulse platform account and password. Label the serial data as x, y, z, and name the device as esp32 to connect the K10 to the platform.
![dataforward](../resource/DocPic/dataforward.png)
![dataforward1](../resource/DocPic/dataforward1.png)

## Sampling
Select the data acquisition section, fill in the label for motion sensor data, set the sampling duration to 2000ms, and start sampling.
![sample](../resource/DocPic/sample.png)

## View Data Distribution
Select "View Data Distribution" and make targeted modifications to the data.
![checkdata](../resource/DocPic/checkdata.png)

## Define Network Structure
Customize the network structure and save it.
![NetworkSEL](../resource/DocPic/networkSEL.png)

## Generate Features
Generate feature values.
![Feat](../resource/DocPic/feature.png)
![Feat2](../resource/DocPic/fear2.png)

## Train Model
![train](../resource/DocPic/train.png)

## Export Model
![deploy](../resource/DocPic/deploy.png)
