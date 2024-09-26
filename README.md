# windows-eye-control-of-external-devices
A Windows eye gaze controlled app for using an nRF52840 to play video games and control a phone

The video shows how controlling a phone works. The user can move a pointer, left click, right click, press and hold or drag by activating the latch button and typing can be done in the textbox in the center.

https://youtu.be/dj8lNFKD49U

There are also multiple pages for playing video games. The game starfield can be played with multiple different control screens. Multiple screens are required due to the complexity of the game. There is one screen for Minecraft.

The device uses an Adafruit Feather Express nRF52840 to act as a Bluetooth low energy mouse.The Nordic nRF52840 is an amazing device and the Adafruit implementation of it is awesome. Thanks Adafruit for the wonderfully easy to use libraries

The software has to be uploaded to the nRF52840. Platformio is recommended. Here is a link to the setup instructions: https://platformio.org/install/ide?install=vscode

An Android App that performs swipe gestures when clicked can be found here https://github.com/madcrow99/AndroidMousePointerSwipeGestures This is quite helpful for navigating an android device while dwell cicking.

The following guide describes process of setting up a pc with Windows Eye Control using a compatible eye tracking device. https://support.microsoft.com/en-us/windows/get-started-with-eye-control-in-windows-1a170a20-1083-2452-8f42-17a7d4fe89a9

The following guide describes how to set up visual studio with the required tools for UWPapps. https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/set-up-your-development-environment?tabs=cs-vs-community%2Ccpp-vs-community%2Cvs-2022-17-1-a%2Cvs-2022-17-1-b

The following is a great resource for gaze interaction concepts and how to use Microsoft's Gaze Interaction Library. The requirements near the end of the page need to be included in the project in order to use gaze interaction. https://learn.microsoft.com/en-us/windows/communitytoolkit/gaze/gazeinteractionlibrary


