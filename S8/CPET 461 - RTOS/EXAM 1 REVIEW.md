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
Lastly, the operating system allows one application exclusive use of a hardware device (STM32 GPIO).