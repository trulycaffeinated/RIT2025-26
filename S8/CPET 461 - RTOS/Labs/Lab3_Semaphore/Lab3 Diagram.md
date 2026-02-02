```mermaid
%%{init: {"flowchart": {"curve": "basis"}} }%%
flowchart LR
	B[UART Print Once] ---> A[DefaultTask]
	C[Button Task] <--> A
	C <--> D
	D[LED Task] <--> A
```
