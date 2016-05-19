# Sigfox SmartEverything downlinks

## Description
This project demonstrates how to realise a SIGFOX downlink using the SmartEverything Evaluation Kit.
Depending on the ACK value, the led will change its color when it is received by the SmartEveryThing board.
The request will be asked by the card every 10 minutes or when the button is pressed.

## Hardware
This project is using the SmartEverything IoT Evaluation Kit (http://www.smarteverything.it).

If nothing happens when you try to perform a downlink request, you may need to upgrade your board's firmware.

It is a simple procedure that for the 90% of the cases does not require any Hw patch.
do the following steps:

1) run the example "ChangeSerial" that change the internal baudrate to 115200 (a fixed baudrate used by the Telit Fw for the upgrade).
	Read carefully the comments everything is explained.

2) run the example "FwUpgrade" following the steps that are showed on the terminal.
	Choose 1.

3) unplug and plug back agin the power (a simple reset is not enougth).

4) run the "ChangeSerial" again but assigning the old baudrate (otherwise all the other examples are no more running).

If something goes wrong on step (2)... do not panic, run it again but with an easy HW patch just do a  shotcut in this two hole on JP1.

## Sigfox Backend

## NodeJS app

## About Sigfox
What is Sigfox?

Sigfox is an connectivity solution dedicated to the Internet of Things.

The operated network is currently operating in +15 countries, on every continent.

Focused on tiny messages (up to 12 bytes) & low energy consumption, it currently powers 7 million devices. Various Sigfox-compatible technical solutions are available, from different silicon vendors. This project uses a SmartEverything prototyping kit

## Contributors
Louis Moreau

## License
The MIT License (MIT)

Copyright (c) 2016 Louis MOREAU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
