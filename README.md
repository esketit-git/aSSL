# aSSL
aSSL SSL over Ajax, enables the client to negotiate a secret random 128-bit key with the server using the RSA algorithm. Once the connection has been established, the data will be sent and received using AES algorithm.

aSSL implements a technology similar to SSL without HTTPS.

aSSL enables the client to negotiate a secret random 128-bit key with the server using the RSA algorithm. Once the connection has been established, the data will be sent and received using AES algorithm.

aSSL is composed of some Javascript files and a server side component. I have recently changed the negotiation algoritm from RC4 to RSA, only a pure Javascript (ASP) server component is currently available. Porting for the main web languages (PHP, Java, Perl, Python, TKL, etc.) is required.

How aSSL 1.2 works

1. The browser calls the server to start the process.

2. The server returns its RSA modulus and the public exponent.

3. The browser generates a random exchange 128-bit key, encrypts it using the server public key and passes the encrypted exchange key to the server.

4. The server receives this encrypted 128-bit exchange key, decrypts it with its private key and, if the result is ok, returns the session duration time.

5. The browser receives the session duration time and sets a timeout to maintain alive the connection.

All subsequent client-server exchanges via aSSL are encrypted and decrypted using AES algorithm. aSSL allows multiple secure connections to be established with one or more servers, contemporarily.

Created by Francesco Sullo - Rome, Italy

Thanks
Tom Wu for its BigIntegers and RSA in JavaScript
Chriss Veness for its AES Javascript implementation
Ryan Perry for the PHP aSSL porting 

30-12-2009, Fixed a bug in the aSSL PHP version. Thanks to Thomas Krapp.

19-11-2009, Fixed a bug in the aSSL PHP version. Thanks to Mark Brekelmans.

RSA Key Generator

http://travistidwell.com/blog/2013/09/06/an-online-rsa-public-and-private-key-generator/
