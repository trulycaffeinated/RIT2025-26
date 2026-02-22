# H1
Why do we need an operating system? 
- Provides a virtual machine for applications
	- Each application can be written without regard to the existence of any other application
		- i.e. each application does not care about other applications - it just does what it's designed to do
- Provides a means for applications to easily migrate across platforms
	- as new hardware becomes available, the application can still work seamlessly
		- As updates in hardware arrive, the application should still work the same on the new hardware across different operating systems. NO functionality should be changed
- Manage hardware resources across applications
	- Allow one application exclusive use of a hardware device
	- Coordinate / manage multiple applications use of a hardware device

**TLDR;**
Operating Systems are used to provide a "virtual machine" for applications, and allow applications to exist and run without concern for other applications.
Because an application is run on this "virtual machine" - changes in hardware should not cause any issue for the application, and no update should be required. 
Lastly, the operating system allows one application exclusive use of a hardware device (like the STM32 GPIO). And manages the applications when multiple require the use of a hardware device.

# H2
![[Pasted image 20260222115241.png]]
RTOS Contains only **one** kernel function - which are functions that involve interactions between tasks or between tasks and the RTOS itself

Generally the RTOS does not contain device drivers. However, it is not uncommon that an RTOS will be packaged with a collection of device drivers.

**We need an RTOS for *Guaranteed Temporal Performance***
Which is when something needs to be happening in real time, it is.

We give up 2 things to achieve this GTP
- Support for a wide variety of hardware devices, as RTOS are usually designed with specific hardware device(s) in mind
- Common API

