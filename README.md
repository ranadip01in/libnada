# nadalib

## User friendly C++ library for everyday basic needs
+ string manipulation
+ random number generation
+ ini (config) file reading/writing
+ basic logging
+ file system

## How to include in your project
1. Git clone or copy folder `libnada` to the same directory your `CMakeLists.txt` is in.
2. Add these 3 lines to your `CMakeLists.txt`
```cmake
    ...
    add_subdirectory(libnada)
    ...
    include_directories(libnada/include)
    ...
    target_link_libraries(PROJECT_NAME PRIVATE nada)
    ...
```
## Usage examples

### For generating random numbers 
### `#include <nada/random.hpp>`
```cpp
bool b1 = nada::random::b(100); // always true
bool b2 = nada::random::b(50); // is true 50% of the time
bool b3 = nada::random::b(25); // is true 25% of the time
bool b4 = nada::random::b(0); // always false

int i1 = nada::random::i(1,6); // like a dice: gives 1, 2, 3, 4, 5 or 6

float f1 = nada::random::f(0,1); // gives a random float between 0 and 1, 
                                 // i.e. 0.6621, 0.1551 or 0.99101 or something

double d1 = nada::random::d(1, 1000); // gives a random double between 1 and 1000
                                      // i.e. 551.07, 0.1987 or 851.29 or so
```


### For String manipulation
### `#include <nada/str.hpp>`
```cpp
std::string s1 = "hello world";
// Remove whitespace
nada::str::remove_whitespace(s1); // "helloworld"

// Remove all chars
nada::str::remove(s1, 'o'); // "hellwrld"

// Get text between tags or other delimiters
std::string tagged1 = "oh that is so <tacky> isn't it?";
std::string tag1 = nada::str::get_between(tagged1, '<', '>'); // "tacky"

std::string tagged2 = "oh that is so 'tacky' isn't it?";
std::string tag2 = nada::str::get_between(tagged2, '\'', '\''); // "tacky"

// Tokenize Strings
std::string s2 = "hello world, how are you?";
std::vector<std::string> v2 = nada::str::tokenize(s2, ' '); // ["hello", "world,", "how", "are", "you?"]

std::string s3 = "0.1,0.2,0.3,0.4";
std::vector<std::string> v3 = nada::str::tokenize(s3, ','); // ["0.1", "0.2", "0.3", "0.4"]
```

### For Reading and Writing INI 
### `#include <nada/ini.hpp>`

Given `subfolder/some_ini_file.ini`
```ini
# contents of example ini file
first=1
second=2.5
third=4
fourth=some value
```
```cpp
// Read values like this
nada::Ini ini("subfolder/some_ini_file.ini");
if (ini.good()) {
    int i = ini.get_int<int>("first"); // 1
    double d = ini.get_float<double>("second"); // 2.5
    std::string s = ini.get("fourth"); // "some value"
}
```

### For miscellaneous things 
### `#include <nada/misc.hpp>`
TODO
