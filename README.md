# lctech-2ch-relay

This sketch demonstrates how to set up a simple HTTP-like server.<br />
The server communicates with the LCTech 2 channel relay board via the Serial port<br />
http://www.chinalctech.com/index.php?_m=mod_product&_a=view&p_id=1261<br />
Adapt from http://www.esp8266.com/viewtopic.php?p=73808#p73808<br />
<br />
     http://server_ip/1/on will turn the relay 1 on<br />
     http://server_ip/1/off will turn the relay 1 off<br />
     http://server_ip/2/on will turn the relay 2 on<br />
     http://server_ip/2/off will turn the relay 2 off<br />
<br />
     There are no Serial.print lines of code<br />
