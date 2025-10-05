TODO: write your answers for the design questions here


## Another encoding of Unicode is UTF-32, which encodes all Unicode code points in 4 bytes. For things like ASCII, the leading 3 bytes are all 0's. What are some tradeoffs between UTF-32 and UTF-8?  

A benefit to encoding Unicode this way is that it makes it much more simple to
decode unicode. Since it is garunteed to be 4 bytes for each codepoint we dont
have to worry about trying to figure out the byte length of each code point and
can just read in 4 bytes every time we want to decode a character. The obvious
disadvantage of this is it uses more storage to store any character that has a
codepoint length of less than 4 bytes. So the tradeoff is larger text file sizes
but increased simplicity when decoding the text. 


## UTF-8 has a leading 10 on all the bytes past the first for multi-byte code points. This seems wasteful – if the encoding for 3 bytes were instead 1110XXXX XXXXXXXX XXXXXXXX (where X can be any bit), that would fit 20 bits, which is over a million code points worth of space, removing the need for a 4-byte encoding. What are some tradeoffs or reasons the leading 10 might be useful? Can you think of anything that could go wrong with some programs if the encoding didn't include this restriction on multi-byte code points?

The leading 10 is useful because it makes it clear where a starting byte for a
codepoint is. If we allow continuation bytes to not have the "01" prefix there
is a chance that the byte could have the same prefix as a starting byte even
though it is a continuation byte. Something that could go wrong if the encoding
didnt include this restriction is if a input stream corrputs, and the computer continues reading from where it stopped, it won't know if the current
byte it is reading is a starting byte or a continuation byte. This would cause
unknown behavior. Overall removing the "10" overcomplicates a lot of scenarios
and can cause parsing errors when decoding.  

