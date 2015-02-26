# FIZ
The FIZ is a very LISP-y scripting languages that is basically useless. This is
a project done as a part of CS252 Operating Systems course at Purdue University.

## FIZ Language

### Builtin Functions
| Function | Description |
| -------- | ----------- |
| `inc`    | Increases the argument by 1. |
| `dec`    | Decreases the argument by 1. Prints an error on attempt to decrease 0. |
| `ifz`    | If first argument is not 0, evaluates and returns the second argument; otherwise evaluates and returns the third argument. |
| `halt`   | Accepts no arguments. Terminates the interpreter. |

**Note**: New builtin functions can be added easily if needed. For details, check `builtin.cc`.

### Example Scripts
*The following scripts were taken from the course web-page*

```
(dec
  (ifz 0 4 (inc 1))
)                            ; interpreter prints 3
```

```
(define (add x y)
  (ifz y x
    (add
      (inc x)
      (dec y)
    )
  )
)
(add 1 2)                    ; interpreter prints 3
```


## Testing
I used [Mocha](http://mochajs.org/) for automated testing of the project, which sure is a bit unorthodox.
I execute the interpreter and pipe in scripts, then let Mocha observer output.

Following are instructions to run tests:

1. Install [Node.js and NPM](http://nodejs.org).
2. Install mocha
```
$ npm i -g mocha
```
3. In the `lab2-src` directory
```
$ npm i
```
4. Finally, in the `lab2-src` directory
```
mocha
```

## License
### The MIT License

Copyright (c) 2015 Denis Luchkin-Zhou

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
