```mermaid
flowchart LR
A ---> B ---> C
```
```mermaid
flowchart TD
    A([Start]) --> B[Process]
    B --> C{Repeat?}
    C -->|Yes| B
    C -->|No| D([End])
```
