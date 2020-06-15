If I was going to the trouble of wirting the code, why not put it online?

==
tp
==

Summary
-------
A program that lets you type into a pipeline.

Example
-------

	$ tp | sed -e "s/^/You just typed: /g"

Pro-tip
-------
Use rlwrap to give you a command history (i.e. hit UP and DOWN to replay commands)

	$ rlwrap tp | sed -e "s/^/You just typed: /g"



=======
hex2bin
=======

Summary
-------
A dumb little program that converts two hex characters at a time into raw binary bytes.
Accepts upper- and/or lower-case hex digits. Ignores all whitespace, but gives an error
for non-hex characters.

Example
-------
	$ echo "31 32 33 48 65 6c 6c 6f 0a" | hex2bin 

Protip
------
Use `hex2bin imm` for "immediate-mode" processing. Normally, hex2bin takes advantage of
stdio buffering to improve performance, but in an interactive setting this means you 
would have to give 4096 characters before hex2bin creates any output. 

	$ tp | hex2bin imm | od -t x1 -An

=====
eswap
=====

Summary
-------
Swaps endianness of 32-bit words. In other words, reads exactly 4 bytes at a time then
spits them out in reverse order. Does not use stdio buffering, so expect performance to
be really bad.

Example
-------
	$ echo "DEADBEEF" | hex2bin | eswap | od -t x1 -An
