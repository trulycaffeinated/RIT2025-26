You are using Obsidian Markdown. Markdown is a great notetaking language that is incredibly versatile.

The theme as of writing this note is GitHub.

This vault will be used for all RIT 2025-2026 notes for Jeff Taylor (jet2898@rit.edu)

### Plugins

This vault uses

**Desmos**
**Git**
**LaTeX Math**
**Mermaid Tools**
### General Notation Table

There are two options for delimiting a math expression inline with your text. You can either surround the expression with dollar symbols (`$`), or start the expression with `` $` `` and end it with `` `$ ``. The latter syntax is useful when the expression you are writing contains characters that overlap with markdown syntax.

| Notation                                  | Example                                      | Inline                                             |
| ----------------------------------------- | -------------------------------------------- | -------------------------------------------------- |
| Addition                                  | a+b                                          | ``$a-b$``                                          |
| Subtraction                               | a-b                                          | ``$a-b$``                                          |
| Multiplication                            | $a \times b$                                 | ``$a \times b``                                    |
| Divison                                   | $a \div b$<br>$\frac{a}{b}$                  | ``$a \div b$``<br>``$\frac{a}{b}$``                |
| Remainder/Mod                             | $5\mod 2=1$                                  | ``$5\mod 2=1$``                                    |
| Negative                                  | $-a$                                         | ``$-a$``                                           |
| Plus or minus (+/-)                       | $\pm a$                                      | ``$\pm a$``                                        |
| Squared, <br>cubed, <br>nth power         | $a^2$<br>$a^3$<br>$a^n$                      | `$a^2$`<br>`$a^3$`<br>`$a^n$`                      |
| Square-root,<br>Cube-Root,<br>Nth-root    | $\sqrt{a}$<br>$\sqrt[3]{a}$<br>$\sqrt[n]{a}$ | `$\sqrt{a}$`<br>`$\sqrt[3]{a}$`<br>`$\sqrt[n]{a}$` |
| Equals                                    | $a=b$                                        | `$a=b$`                                            |
| Not equals                                | $a \neq b$                                   | `$a \neq b$`                                       |
| Identical/Equivalent                      | $a \equiv b$                                 | `$a \equiv b$`                                     |
| Proportional                              | $a \propto b$                                | `$a \propto b$`                                    |
| Approx. Equal                             | $a \approx b$                                | `$a \approx b$`                                    |
| Greater than<br>Less Than                 | $a > b$<br>$a < b$                           | `$a > b$`<br>`$a < b$`                             |
| Greater Than / Equal<br>Less Than / Equal | $a \geq b$<br>$a \leq b$                     | `$a \geq b$`<br>`$a \leq b$`                       |
| Factorial                                 | $a!$                                         | `$a!$`                                             |
| Abs Val                                   | $\|{a}\|$<br>(something funky here)          | `$\|{a}\|$`                                        |
| Delta                                     | $\Delta$                                     | `$\Delta$`                                         |
| Pi                                        | $\pi=3.14$                                   | `$\pi=3.14$`                                       |
| Euler                                     | $e = 2.71828$                                | `$e = 2.71828$`                                    |
| Sum                                       | $\displaystyle\sum_{k=a}^b f(x)=x$           | `$\displaystyle\sum_{k=a}^b f(x)=x$`               |
| Series Product                            | $\displaystyle\prod_{x=a}^b f(x)=x$          | `$\displaystyle\prod_{x=a}^b f(x)=x$`              |
| Angle                                     | $\angle$                                     | `$\angle$`                                         |
| Degree                                    | $a\degree$                                   | `$a\degree$`                                       |
| Radians                                   | $rad$                                        | `$rad$`                                            |
| Vectors                                   | $\mathbf{a}$<br>$\overline{a}$<br>$\vec{a}$  | `$\mathbf{a}$`<br>`$\overline{a}$`<br>`$\vec{a}$`  |
| Integration                               | $\int_a^b f(x)=x$                            | ``$\int_a^b f(x)=x$``                              |
| Derivative                                | $\frac{df}{dx}$                              | ``$\frac{df}{dx}$``                                |
| Partial Derivative                        | $\frac{\partial d}{\partial x}$              | ``$\frac{\partial d}{\partial x}$``                |

### Greek letters
Greek letters are just ``$\letter$``

As such Alpha is ``$\alpha$`` --> $\alpha$
As such Beta is ``$\beta$`` --> $\beta$
etc...

### Code blocks

Code blocks use three \`\`\` to start and end a code block as such

```
This is a code block with NO language
```

Starting a \`\`\` and stating a language will set that code block to that language and display it...

```powershell
Write-Host "This is a powershell block"
```

```C++
std::cout << "This is a C++ block" << std::endl;
```

