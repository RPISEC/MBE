## Reversing Labs
I tried to base these more or less on Jeremy's labs. If you get the 
key correct, you get a shell, so we can structure these the same way 
we've been doing the rest of the levels.

### Lab C
Simple Integer compare, obvious yes/no path.

### Lab B
XOR'd string, you supply key by getting the difference between your input 
and a hardcoded value. "Correct" path is obfuscated so you have to actually xor 
stuff together and reason it out (or thats the idea)

### Lab A
Simple keygen. The serial is calculated by adding to a base checksum and doing 
some XOR / modulus stuff. 
