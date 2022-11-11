# Photo-Encryption
This project encrypts photos with a 16 character password which can then only be decrypted using that same 16 character password.

The project can be compiled and ran using the makefile provided

After making the project can be ran using the following example commands with the given cat.jpg image
./PhotoMagic cat.jpg output.jpg 1234567890abcdef

That creates the encrypted output.jpg file
To get the orginal image back you would use the command with the same password on the output.jpg file
./PhotoMagic output.jpg outputdecrypted.jpg 1234567890abcdef

The outputdecrypted.jpg file should then be the original cat once again

Example photos are in the examples folder
