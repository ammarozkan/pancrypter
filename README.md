# Pancrypter
## Abstract
An file encryption library/program that written with C, and only standart libraries that can be provided from GCC. Contains a hashing-like algorithm in bytehasher.h.
**If you dont want to get confused with details, then you can go to the "If Just Compiled From main.c and Didn't Customized" part.**
## Logic of Algorithm

### Hashing Algorithm
Hashing algorithm is going first byte of hash to the last byte repeately. While it doing that, it adds numbers that gotten from the string (array of bytes, I resume) that given to it to hash it.
This procees will give instinct unique numbers for each string (string is a good short name for array of bytes). For getting more unique hashes from that,
the algorithm multiples the numbers from string with a great constant. So the hashed result will be more effected from a little byte on the string. The algorithm also does
something to other bytes that is not will be effected on the process in one loop. While algorithm circles on the hash, not effecting the next byte only, also
effecting other bytes. Next 10 bytes (that can be modified with redefining the **EFFECT_COUNT** before including the library) will be effected from only one byte. But when byte is far from 
main one, this byte will be less effected then the closer one. This deacreasing by distance effect is getted from another constant named **EFFECT_CONST**. That can also be modified
with redefining it before including any libraries. Also, the hashing process is strictly creating hashes looking to **HASH_BYTE** constant. That constant defines that the count
of bytes that gotten from hashing a value. You can change it with redefining it before including any libraries to get 256 bytes and get a 'SHA256 effect' (that will be look really dumb I guess. My algorithm could not work with 256 bytes well
but it will create really unique things with that too, I hope.) Or try just 2 bytes and get "confused decryption" thing. That will be useless.

### Encryption and Decryption Algorithm
With defining the hashing algorithm, we can say we have a specific value for everything. With that, we can use it for encryption.
Let's say we have key that is "amazingkey". If we need to encrypt the letter "B" we can hash "amazingkeyB" and get a unique thing
from that. Nobody can understand the hashed value until tries to match it with something with doing hashing again and again. If you know
the key and encryption style, you can decrypt it with trying **"amazingkeyA", "amazingkeyB"... "Oh, hashed values are same when I hash
'amazingkeyB'! So encrypted value can be 'B'! "** So encryption and decryption is absolutely works like this in this algorithm. By this,
decryption is slower than the encryption.

In encryption, algorithm uses key and value that will be encrypted like "amazingkeyA" but it should change the style randomly. Because, if you don't do it,
a language professor could came and start to match "4 byte letters" with real letters and solve the problem. We don't want this.

When I program this on python, I used to add more copies of keys or letters to the "will be hashed" value. But in C, this is hard. So I used
Ceaser's thing randomly on random bytes that is on "will be hashed" string.

In encryption, **YOU CANNOT USE RANDOM** because of "every same thing should give same thing again and again" case. But the style
could be randomly seletected **(only randomly selected, not randomly used. so the style of encryption should be finite)** and in decryption,
every style could be tried to match. That way, we will make hard mr. professor's job. (when I choose style 1, style 1, style 1: I should get
exact same effect on text.)

## Naming
The algorithm and the style of encryption should be named for distinguishing from other encryptions. Generically ```Pan4``` or specifically ```133K.Pan-4``` will be a great name.

### Why?
Pan4 assembles from a short thing of "Pancrypter" and byte number that represents 1 unencrypted byte.
Pan4 looks good but we need more unique for seperation.
XK.Pan-B is a good name. X specifies a number that generaten from constants of the algorithm with arithmetics. (if constants are not known and want to know somehow, look at **Logic of Algorithm**
section.)

X = ((LEC x EFFECT_COUNT x HASH_BYTE) / (EFFECT_CONST * 1000))'s "before comma" side.

B represents the bytes of hashed bytes. HASH_BYTE.

133K.Pan-4 encryption is made by the default constants on the code.

## If Just Compiled From main.c and Didn't Customized...
You don't need anything else except GCC, ```stdio.h``` and ```stdlib.h``` while compiling it. GCC should provide ```stdio.h```, ```stdlib.h``` libraries.

Program will work well with files. You can use these options for general use:
- "--command [enc/dec]": You can choose whether you encrypt or decrypt a file.
- "--key [yourkeyforusingwithencryption]/": You can customise your key for encryption or decrypt a file with a key. **END OF THE KEY SHALL BE "/"** If you want something default, change the source code that is default. You can find this at start of the ```main.c```'s ```int main()``` function. ```char* key = "key/"``` And forgetting the "/" to put the end will be astonishing.
- "--maxtype [maximum amount of type] :  You can define maximum amount of type that will be used in encryption on will control on decryption. If something encrypted with 20 types, decryption should be use 20 types. Greater value, greater decryption time. (default 3)
- "--input [input file destionation]" : You should set a input file that will be encrypted or decrypted.
- "--output [output file destination]" : You should set a output file too. Encrypted or decrypted file will be this file. I generally put ".enc" filename extension to encrypted files.
