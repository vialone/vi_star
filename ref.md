# ViStar - Dynamic Typized Compiling Programming Language
It oriented to be simple, convenient and fast. It compiles to machine code,
but still flexible because of run-time dynamic typization.

## Hello, World!
Simple traditional fish code:

```rust
fn main() {
    print("Hello, World!");
}
```

## Supported at moment language features

### Assertions
Syntax is trivial:

```py
assert expression;
assert expression ? message;
```

It checks expression, and if it is false, raises AssertionErr and crushes with code -1
If message provided, it prints message to stderr and crushes with code -1

AssertionErr is a regular exception, so you can catch it like any other

### Deletion
Syntax:

```c++
delete name;
```

Deletes object assigned to name, after that read access to name is disabled and memory taken for it freed.

### Branching
Syntax:

```rust
if cond {
    ...
} elif cond {
    ...
} else {
    ...
}
```

`elif` is sinonimous to `else if`. Curly brackets could be skipped, if there is only one statement instead of them.

### Loops

### For-each loop
Syntax:

```rust
for item : iterable {
    ...
}

for item : iterable {
    ...
} else {
    ...
}
```

Rule about curly brackets still works. it works everwhere, keep it in mind. if second operand is not iterable,
this code will raise `ValueErr: bad operand for <for-each loop>`

It iterates on each element of `iterable` and puts them in `item`. else block will be executed alfter whole
iterable left, and `break` was not faced.

### while loop
Syntax:

```rust
while cond {
    if sth {
        break;
    }
}

do {
    if ath {
        continue;
    }
} while cond;
```

It stays in loop while cond is true. If cond is not boolean it will be casted, if unable - raises ValueErr.

`break` - breaks loop and drops flow to position after loop or any it's child statements (else blocks too)
`continue` - skips current iteration and goes to next.

### until loop
Syntax:

```rust
until cond {
    ...
}

do { ... } until cond;
```

Absolutely as `while` but inverts condition check (loops while cond is false)

### times loop
Syntax:

```rust
times 10 {
    ...
}

times 25 : step {
    ... // numeration begins from zero
}
```

Repeats some code N times. current iteration number you can redirect into object.

### forever loop
Syntax:

```rust
loop {
    ...
}
```

Repeats code forever. Also, you can use `break` and `continue` in this loop.
You can specify interval between iterations:

```rust
loop 10 { // sleep 10 seconds between iterations
    ...
}
```

Sleep duration in seconds can be float.

### Shifting
You can shift value. Depends on type, it can be:

* shifting number - shifts by bits
* shifting string - shifts by symbols
* shifting iterable - shifts by elements
* shifting buffer - shifts by bytes

```rust
value << shift;
value >> shift;
```

### Assignment

You can assign value to variable using `=` operator.
destination can be:

* variable
* attribute reference
* index reference

If destination is variable and it doesn't exist, it will be created and assigned to value.
If destination is attribute reference, it will be assigned to attribute of object.
If destination is index reference, it will be assigned to element of iterable.

```rust
var = value;
var.attr = value;
var[index] = value;
```

### Dictionaries

Dictionaries are a set of key-value pairs. They are created using `{}` syntax, or using `Dict()` constructor.

```rust
dict = {
    key1 : value1,
    key2 : value2,
    ...
};

dict = Dict(key1 = value1, key2 = value2, ...);

dict = Dict(keys = (key1, key2, ...), values = (value1, value2, ...));
```

You can access dictionary elements using `[]` operator or using method `get()` and `set()`.

```rust
a = dict[key];
b = dict.get(key, default);
dict.set(key, value);
```

### Slices
You can get subset of iterable using slice syntax. Slices are created using `:` operator.

```rust
iterable = (1, 2, 3, 4, 5);

a = iterable[1 : 2 : 2];
b = iterable[1 : 2];
c = iterable[2 :];
d = iterable[: 2];
e = iterable[:];
```

Here, a = (2,), b = (2, 3), c = (3, 4, 5), d = (1, 2), e = (1, 2, 3, 4, 5).

### Ranges
Ranges are created using `..` operator.

```rust
range = 1 .. 10;

for i : range {
    print(i);
}
```
Output:
```
1
2
3
4
5
6
7
8
9
10
```

Also, you can skip some operands:

```ViStar
range = .. 10; // range from 0 to 9
range = .. 10 .. 2; // range from 0 to 9 with step 2
range = 10 .. 30 .. 10; // range from 10 to 30 with step 10
```

### Mapping statements

You can map some code over iterable. Here is example:

```rust

source = (1, 2, 3, 4, 5);

dest  = map i : source (-i);

print(dest);
```

Output:
```
(-1, -2, -3, -4, -5)
```

`map` statement is a shortcut for evaluatable iterating expression. It creates new iterable, and evaluates
expression for each element of source iterable to it's new iterable. It returns new iterable.

If you want map to send result to some existing iterable, you can use `:` operator:

```rust

source = (1, 2, 3, 4, 5);

dest  = List();

map i : source (-i) : dest;

print(dest);
```

Output:
```
(-1, -2, -3, -4, -5)
```

It works the same way as `for-each` loop.

### Errors

Sometimes errors can occur, and you can catch them. There are two types of errors:

* Internal errors - they are raised by runtime, and you can handle them only by creating interrupt handler.
* Runtime errors - they are raised by your code, and you can handle them by catching or creating callback to handler.

### Interrupt handlers

Interrupt handlers are regular functions, but they have special flag:
```rust
@interrupt(4)
fn handler() {
    ...
}
```

It means, that this function will be called on interrupt. It can be used to handle interrupts, like
breakpoint (INT 3), page fault (INT 4), etc.

You can create as many interrupt handlers as you want, but you can't have more than one handler for
each interrupt.

if leave handler without number of interrupt, it will be called on any interrupt that is not handled
by any other handler.

### Runtime errors

Runtime errors are exceptions, that are raised by your code or runtime to prevent interrupt fault.

Here is syntax to catch runtime error:

```c++
try {
    ...
} catch KindOfErr { // KindOfErr is type of exception, it is class
    ...
}
```

If you want to catch all runtime errors, you can use `catch` without specifying type:

```c++
try {
    ...
} catch {
    ...
}
```

If you want to get info about what happened, you can use `catch` with `:` operator:

```c++
try {
    ...
} catch : err {
    print(err);
}
```

`err` is a variable, that will contain info about error. It is of type of error that was raised.

Also, you can catch multiple errors:

```c++
try {
    ...
} catch KindOfErr1, KindOfErr2 : err2 {
    ...
}
```

In this case, this `catch` block will be activated if any of `KindOfErr1` or `KindOfErr2` was raised.

Also, you can raise an error, of course:

```python
raise ValueErr("bad operand");
```

It raises `ValueErr` error with message "bad operand".

### Namespaces

Namespaces are a way to group your code.
So, you have two namespaces: global and local.

Global namespace is a namespace, that is always available, and it is root namespace.

Local namespace is a namespace, that is created for each function or block of code.

You can access global namespace like any other variable.

If variable was created in global namespace, any access to it from local namespace will be redirected to global namespace.
If variable was created in global namespace, any access modifying it's type or deleting it affects only local namespace.
If you want to change type or delete global varaiable (It is bad practice, keep it in mind), you can use `global` keyword:

```c++
global var = value;
global delete var;
```

### Number systems

ViStar supports these number systems with bases 2-36, you can specify base using `\`` symbol:

16`234567cf

### Bitwise operations

ViStar supports bitwise operations, you can use them in any expression:

```rust
a = 1 << 2;
b = a >> 2;
c = a & b;
d = a | b;
e = a ^ b;
```
Also, here is a type `set`, it supports bitwise operations (it works as selection of elements)

For example:

```c++
set = <1, 2, 3, 4, 5>;

a = set & <1, 3, 5>;
b = set | <1, 3, 5, 6>;
c = set ^ <1, 3, 5>;
```
Output:
```
<1, 3, 5>
<1, 2, 3, 4, 5, 6>
<2, 4>
```

### Expressions

The following table summarizes the operator precedence in ViStar, from
highest precedence (most binding) to lowest precedence (least
binding).  Operators in the same box have the same precedence.  Unless
the syntax is explicitly given, operators are binary.  Operators in
the same box group left to right (except for exponentiation, which
groups from right to left).

Note that comparisons, membership tests, and identity tests, all have
the same precedence and have a left-to-right chaining feature as
described in the Comparisons section.

| Operator                                                          | Description                                                   |
| ----------------------------------------------------------------- | ------------------------------------------------------------- |
| "(expressions...)",  "[expressions...]", "{key:                   | Binding or parenthesized expression,                          |
| value...}", "<expressions...>"                                    | list display, dictionary display, set                         |   
|                                                                   | display                                                       |
| "x[index]", "x[index:index]",<br>"x(arguments...)", "x.attribute" | Subscription, slicing, call,<br>attribute reference           |
| "**"                                                              | Exponentiation                                                |
| "|x", "-x", "~x"                                                  | Positive, negative, bitwise NOT                               |
| "*", "@", "/", "//", "%"                                          | Multiplication, matrix<br>multiplic                           |
| "^"                                                               | Bitwise XOR                                                   |
| "|"                                                               | Bitwise OR                                                    |
| "in", "is", "<", "<=", ">",<br>">=", "!=", "=="                   | Comparisons, including membership<br>tests and identity tests |
| "!x"                                                              | Boolean NOT                                                   |
| "&&"                                                              | Boolean AND                                                   |
| "||"                                                              | Boolean OR                                                    |
| "?" – ":"                                                         | Conditional expression                                        |

#### Footnotes

1. While "abs(x%y) < abs(y)" is true mathematically, for floats it
may not be true numerically due to roundoff.  For example, and
assuming a platform on which a ViStar float is an IEEE 754 double-
precision number, in order that "-1e-100 % 1e100" have the same
sign as "1e100", the computed result is "-1e-100 + 1e100", which
is numerically exactly equal to "1e100".  The function
"math.fmod()" returns a result whose sign matches the sign of the
first argument instead, and so returns "-1e-100" in this case.
Which approach is more appropriate depends on the application.

2. The Unicode standard distinguishes between *code points* (e.g.
U+0041) and *abstract characters* (e.g. “LATIN CAPITAL LETTER A”).
While most abstract characters in Unicode are only represented
using one code point, there is a number of abstract characters
that can in addition be represented using a sequence of more than
one code point.  For example, the abstract character “LATIN
CAPITAL LETTER C WITH CEDILLA” can be represented as a single
*precomposed character* at code position U+00C7, or as a sequence
of a *base character* at code position U+0043 (LATIN CAPITAL
LETTER C), followed by a *combining character* at code position
U+0327 (COMBINING CEDILLA).<br>
The comparison operators on strings compare at the level of
Unicode code points. This may be counter-intuitive to humans.  For
example, ""\u00C7" == "\u0043\u0327"" is "false", even though both
strings represent the same abstract character “LATIN CAPITAL
LETTER C WITH CEDILLA”.

3. The power operator "**" binds less tightly than an arithmetic or
bitwise unary operator on its right, that is, "2**-1" is "0.5".

### OOP and inheritance

Firstly, you can create a class:

```c++
class A {
    Int x;
    fn $new() {
        this.x = 1;
    }
}
```

It creates a class, with name `A`. It has one method, called `$new`, that is called on object creation.

You can create an object of class `A` like usual:

```c++
a = A();
```

And you can access its attributes using dot notation:

```c++
a.x;
```

If you want to create mutable object of class `A`, you can use `new` keyword:

```c++
a = new A();
```

Also, you can create a class with parent class:

```c++
class B : A {
    fn $new() {
        this.x = 2;
    }
}

b = B();
```

Now, you can access `x` attribute of `b` using dot notation:

```c++
b.x;
```

### Special fields and methods

There are some special fields and methods, that are available for all classes:

| Field \/ method | Description |
| :-------------: | :---------- |
| $class: Object | Class object. It presents class, that object belongs to. |
| $add(other)                  | Method for adding       |
| $sub(other)                  | Method for substracting |
| $mul(other)                  | Method for multiplying  |
| $div(other)                  | Method for dividing     |
| $mod(other)                  | Method for modulo       |
| $neg()                       | Method for negating     |
| $not()                       | Method for inverting    |
| $delattr(String attr)        | Method for deleting attribute of object |
| $dir()                       | Method for listing object content |
| $doc()                       | String field containing object's info |
| $cmp(other)                  | Method for comparing objects (-1 - less, 0 - equal, 1 - greater) |
| $getattr(String attr)        | Method for getting attribute value |
| $hash()                      | Method for converting any object to int object that can't represent the object |
| $new(ANY)                    | Method calls on object initializing |
| $repr()                      | Method returns string with in-language representation of object |
| $setattr(String attr, value) | Method for setting attribute value |
| $getitem(index)              | Method for getting value by index/slice |
| $setitem(index, value)       | Method for setting value by index/slice |
| $sizeof()                    | returns real RAM object size in bytes |
| $addrof()                    | returns real RAM object address |
| $str()                       | returns string representation of object |
| $errhook()                   | Method to handle in-class errors |
| $and(other)                  | Bitwise AND |
| $or(other)                   | Bitwise OR |
| $xor(other)                  | Bitwise XOR |
| $land(other)                 | Logic AND |
| $lor(other)                  | Logic OR |
| $lnot()                      | Logic NOT |
| $lxor(other)                 | Logic XOR (by default behaves like `!=`) |
| $bool()                      | Boolean representation of object |
| $ceil()                      | Ceiling |
| $int()                       | Integer representation of object |
| $float()                     | Float representation of object |
| $pos()                       | +X operator |
| $pow(other)                  | x ** y operator |
| $lshift(other)               | bitwise shift left |
| $rshift(other)               | bitwise shift right |
| $contains(other)             | check if object contains inside other object |
| $next()<br>$end()<br>        | Iterating methods |
| $len()                       | Getting length of object |
| $cval()                      | Getting C value representation (API only, not accessible or overloadable in ViStar code) |
| $range(other)                | x..y operator |
| $step()                      | x : y operator |
| $prestep(other)              | :y operator |
| $del()                       | Destructor |
| $dict()                      | Dict representation of object |
| $tuple()                     | Tuple representation of object |
| $set()                       | Set representation of object |

### Foundamental types/classes

* `Numeric`
    * `Int`
    * `Float`
* `Iterable`
    * `List`
    * `String`
    * `Tuple`
    * `Set`
    * `Array`
    * `Buffer`
* `Abstract`
    * `File`
    * `Stream`
    * `Special`
        * `Function`
        * `ClassObject`
        * `CFunction`
        * `Pointer` (also `Numeric`)

## Compilation & Other stuff

To compile program for your host arch & os:

```
Windows:
    REM hello.vs - put your program main file instead
    vsc /o hello.exe hello.vs

Linux/MacOS:
    # hello.vs - put your program main file instead
    vsc -o hello hello.vs
```

If you want, and you have installed, you can use C Preprocessor, using flag `--cpp`
If you want to attach custom or written by you preprocessor, you can pass path to preprocessor's executable using flag `--pp <PATh>`
If you want to use custom optimizer, use flag `--op <PATH>`
If you want to pass argument to preprocessor, use `--ppa <STRING>`
If you want to pass argument to optimizer, use `--opa <STRING>`
To specify arch, use `--arch <NAME>`
To specify subarch, use `--subarch <NAME>`

For example, command to compile program using my own preprocessor and optimizer for 32-bit ARM linux:

```
Windows:
    vsc /arch aarch /subarch v7 /pp C:\vstools\mypp.exe /op C:\vstools\myop.exe /o hello hello.vs

Linux/MacOS:
    vsc --arch aarch --subarch v7 --pp /bin/mypp --op /bin/myop -o hello hello.vs
```

For cross-compiling, you need to install ViStar Cross-Compiling Tools package (coming soon) or configure you VSC to use different `g++` and stdlibs
(if enabled using of libc++ in config, otherwise you can't use ViStar stdlib, builtin classes/types and other things)

## Configuring

Config for VSC stored in `/etc/vistar/vistar.conf.d` on linux/MacOS and `%VISTARPATH%\config` on Windows.

In this directory you can see multiple *.conf files. their names doesn't matter, but it's recommended to store settings in matching file.
ViStar's *.conf files are JSON configurations for compiler and other stuff. Be careful, modifying them, it can break your compiler!
But, if you failed anyway, you can run `vsmgr rollback`. This command will roll your config back to previous saved state. To save state, run
`vsmgr stateshot`. By default you have stateshot with default ViStar configs, so if yo want to reset config and didn't make a stateshot, don't
worry, it will work. If you already have some rollback points, but you wanna rollback to default state, you can run `vsmgr rollback full`.

## License

ViStar is licensed under the terms of the GNU General Public License version 3.

## Contact

If you have any questions, feel free to contact me on [Telegram](https://t.me/vi_chapmann).


## Coming soon
1. Named loops
2. Metaclasses
3. Asynchronous coroutines
4. multi-threading
5. multi-processing
6. Modular stdlib patches
7. remote updates
8. Strong (forced) types
