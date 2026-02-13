![[Pasted image 20260213122238.png]]

# Print Module
"Provides a module (.h and .c files) which protects access to the UART with a binary
semaphore and allows text strings to be printed to the UART through a module-defined
function"

Print Module will hold a ``Print_Line()`` function that will transmit to the UART after acquiring the semaphore.
```C
void Print_Line(const char *fmt, ...)
{
	char buffer[256];
	
	/*
	arb argument stuff so I can pass %d, %i blah
	*/
	
	Down(); 
	HAL_UART_Transmit()
}
```