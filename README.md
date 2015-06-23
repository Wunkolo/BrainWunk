#BrainWunk
An interpreter for the "Brainfuck" language

![Demo](https://cloud.githubusercontent.com/assets/644247/8301685/16446c08-1945-11e5-8322-1a5d156cf45d.gif)

The interal buffer only takes up as much space as the Brainfuck program cares to attempt to address and will reallocate its self dynamically.


`-v`                : Enables verbose output

`-e "(expression)"` : Evalutes the brainfuck expression in quotes

`-d`                : Outputs the final memory array as formatted ascii text

Example:

```BrainWunk.exe -eval "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."```

will cause the program to output `Hello World!` along with a new line.
