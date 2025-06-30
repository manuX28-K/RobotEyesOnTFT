# What is RobotEyesOnTFT ?

Well, it is a project to bring the classic Robot Eyes onto the TFT display platform.

![Project-Preview](https://github.com/manuX28-K/RobotEyesOnTFT/blob/main/Beta-Build-Preview.jpg)

### What does this project has to offer ?

Currently blinking and glazing is supported, more effects will be added in the future ( only if i figure out how to 🫠 )

### How does it work ?

This project uses Sprite function to create animations in the ESP's ram and uses PushSprite method to push the animation onto the screen.
I do not know well on how to explain the thing but this is what it sums up to.

# Where do I get started ?

Well, you need to get the source code.zip file from the releases tab. Extract it and open up the TFT-Eyes.ino file from the Arduino IDE ( latest build...older ones will work ig )
and flash it to your ESP. You can read the code for yourself and most of the things are commented so it will be easy to figure out the process for yourself.

## ----- ESP32 S3 SPECIAL NOTICE -----

Esp32 S3 has a different method to flash, means you need to add few commands to your TFT_eSPI library to make it work well with the TFT screen.
These commands are mentioned in the .ino file so read it carefully before proceeding. Every other ESP32 will work just fine ( i have tested with both Wroom32u
and S3 supermini and both worked as expected ). NodeMCU devices such as Esp8266/D1 Mini ARE NOT tested, so results are not guaranteed. 

# Final thoughts

I am no expert in coding and my oled screen going to shadow realm inspired me to make this project. ( LOL 🥸😅 ). As well as i made a lot ( an actual lot ) 
of mistakes whilst in the process and ChatGPT ( GOATGPT 🗿 ) helped me overcome those struggles. KUDOS FOR THAT THING FOR IT'S S TIER WORK ♡. 
Thank you a lot for testing this project out, if you have any suggestions/improvements please let me know. Enjoy!!!


## Gallery

Eyes Open Animation Preview

![Eyes-Open](https://github.com/manuX28-K/RobotEyesOnTFT/blob/main/Eyes-Open-Animation.jpg)

Eyes Closed Animation Preview

![Eyes-Closed](https://github.com/manuX28-K/RobotEyesOnTFT/blob/main/Blinking-Animation.jpg)


Clear Visibility in Darkness Preview

![Clear-Visibility](https://github.com/manuX28-K/RobotEyesOnTFT/blob/main/Clear-Visibilty-in-Dark.jpg)
