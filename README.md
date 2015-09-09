# edison-ifttt-sketch
This Edison sketch aims to allow the integration of an IOT solution with the IFTTT Service.

The main objective of this Edison/Arduino sketch was to learn how to connect Intel Edison to WiFi and send HTTP requests to the IFTTT service.

Instructions:
- Change the value of the SSID and PASSWORD variables to let your Edison connect to the WiFi;
- Set the variable makerChannelKey with your Maker channel key, that could be obtained here: https://ifttt.com/maker;
- Create your IFTTT rules using the Maker Channel as trigger;
- Call "fireIftttEvent("EVENT-NAME");" or "fireIftttEvent("EVENT-NAME", "TEST-VALUE1", "TEST-VALUE2", "TEST-VALUE3");" whenever you want to notify IFTTT about an event;
- Profit!

Possible applications:
- Notify your Android wear device about the temperature in your room;
- Register the light sensor readings into a spreadsheet;
- Tweet something everytime that someone presses a button;
- Etc, etc, etc!

This is my first Arduino sketch, I hope you appreciate it.
