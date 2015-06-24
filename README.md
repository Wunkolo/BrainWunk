#BrainWunk
An interpreter for the "Brainfuck" language

![Demo](https://cloud.githubusercontent.com/assets/644247/8301685/16446c08-1945-11e5-8322-1a5d156cf45d.gif)

The interal buffer only takes up as much space as the Brainfuck program cares to attempt to address and will reallocate its self dynamically.


`-v`                : Enables verbose output

`-e "(expression)"` : Evalutes the brainfuck expression in quotes

`-d`                : Outputs the final memory array as formatted ascii text

`-i`                : Interactive mode:

![Interactive Mode](https://cloud.githubusercontent.com/assets/644247/8323507/3c014f82-19fa-11e5-98f3-36e61471cf48.gif)
`quit` to exit
`reset` or `r` to reset the interpretor into its default state.
`dump` or `d` shows a hexadecimal dump of the current memory state

Example:

```BrainWunk.exe -eval "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."```

will cause the program to output `Hello World!` along with a new line.
