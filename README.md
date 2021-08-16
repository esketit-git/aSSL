# aSSL Ajax SSL - end to end encryption with client side JavaScript & server side PHP

aSSL implements technology similar to SSL over http. Embed in any http client / server application and provide end to end encryption without third party issuer. aSSL is in development and not ready for production. The files are a working demo. The goal of the project is to make the end to end encryption more secure, possibly even ID the server to the client without a certificate issuer.

The PHP directory is the only folder you need as it contains both the js and the php, simply copy and paste to web server and run index.php. The ASP example is a language port and aSSL folder is just the js files. PHP Version requires php-gmp so apt-get install php5-gmp and then you may need to enable PHP FPM in Apache2 by a2enmod proxy_fcgi setenvif and a2enconf php-fpm and reload apache as per the instructions provided by the installation of php-gmp.

**How aSSL works**

1. On page load the (Javascript) connection routine is called aSSL.connect(url,showConn) and the PHP connection routine is called aSSL::response() conn.php. The client side code and the server side code are mirror versions exact so the protocol is the same for both client and server. Rther than each side generating their own keys and exchanging them under a session id...

2. The server side PHP still generates and make available its RSA modulus and the public exponent to the client. (the pubic key)

3. But the client instead generates a random exchange 128-bit key, encrypts it using the server public key and passes the encrypted exchange key to the server.

4. The server receives this encrypted 128-bit key, decrypts it with its private key and, if the result is ok, returns the session duration time.

5. The browser receives the session duration time and sets a timeout to keep alive the connection.

All subsequent client-server exchanges via aSSL are encrypted and decrypted using AES algorithm. aSSL allows multiple secure connections to be established with one or more servers.

The data gets encryped and then encoded and then sent, upon receiving it gets decoded and then decrypted.

**aSSL reference**

aSSL.connect(uri,callBackFunction[,connectionName])

Client-side method. It starts the process to establish the connection.

uri is the uri of the server-side application.

callBackFunction is the function that is automatically called after connection is established

connectionName is the name of the connection. If it is not present aSSL opens the '0' connection as default.

aSSL.encrypt(clearText)

Client and server-side method. It encrypts the clearText string using the previously negotiated secret 128-bit key.

aSSL.decrypt(cipherText)

Client and server-side method. It decrypts the cipherText using the previously negotiated secret 128-bit key.

aSSL.response(myKey)

Server-side method. It using the myKey parameter (see above), establishes the connection.

aSSL.connections[connectionName].sessionTimeout

Client-side property. It is the session duration time of the specific connection. If you use the default connection you must specify it as '0'.

aSSL.connections[connectionName].elapsedTime

Client-side property. It is the time elapsed to establish the connection.

aSSL.keySize

Client-side property. As default aSSL generates a 128-bit key (e.g. a key of 16 characters). This is expressed in number of characters. If you want to generate a different key for some mysterous reason you can set this property. For example:

aSSL.keySize = 12

aSSL.onlyMantainSession

Client-side property. By default, once the connection has been established and the secret key has been exchanged with the server, aSSL merely mantains the session. If you prefer that aSSL continually re-negotiates a new key instead of just keeping the session open, set this property to false.

Is aSSL secure as SSL?

Currently No. *SSL* is secure because it is implemented at browser level so when a HTTPS connection has been established, the browser checks the SSL Certificate before continuing.

Suppose a man-in-the-middle (MiTM) attack. With an SSL connection, the attack would be successful only should the user click Ok when the browser alerts him saying that the certificate doesn't correspond to the connected server (the alert may also appear if some file is transferred over HTTP instead of HTTPS because in this file a hacker could inject malicious code).

If a hacker were to attack with a MiTM attack during an aSSL connection, he could be successful.

Password sniffing is much more diffuse because it is much easier. In fact, there are specific softwares that sniff the traffic, recognizes userid and passwords, and register them.

aSSL protects against these sniffers. When a server exchanges account information in clear HTTP, a sniffer can simply intercept all the data, but if the server exchanges the data via aSSL it is not possible to decode the passed data and so the level of security of the site is notably better.

The goal of aSSL development is remedy these issues, perhaps by the server sending an md5 checksum that only the correct server could have produced and too hard to guess in the session time or another idea. 

aSSL is composed of javascript files and a server side component. The major functions are located in the files assl_.js and assl_.php. Along with connection, encryption and decryption there are string manipulation functions. aSSL utilizes Ajax to conenct, send and receive. aSSL changed the negotiation algorithm from RC4 to RSA, an original Javascript (ASP) server component is made available with the source code but no longer supported, JS/PHP version, any porting should mirror the existing file structure functions so that any updates to one code can be applied universally.

**PHP Version** requires php-gmp so apt-get install php5-gmp and then you may need to enable PHP FPM in Apache2 by *a2enmod proxy_fcgi setenvif* and *a2enconf php-fpm* and reload apache as per the instructions provided by the installation of php-gmp. 

aSSL uses an encryption lib that PHP no longer supports. https://github.com/pear/Crypt_RSA - implementation of RSA in php version,  https://pear.php.net/package/Crypt_RSA - message reads This package is not maintained anymore and has been superseded. Package has moved to channel phpseclib.sourceforge.net, package Crypt_RSA.

Created by Francesco Sullo - Rome, Italy

**Introduction**

aSSL is composed of two parts: a client-side component and a server-side component. The first is always a set of pure Javascript files, the second depends on specific languages (Javascript, PHP, Java, Ruby, etc.).

**Client-side installation**

Unzip the aSSL zip file and put the files into a subdirectory. Then, include the assl.js files into your HTML. For example:

<script type="text/javascript" 
src="assl/assl.js"></script>

This one include inserts all the aSSL scripts into the page.

**Server-side installation**

Javascript/ASP case

It is sufficient to unzip the aSSLforASP zip in a subdirectory. There are two type of processes managed by aSSL: the secret key negotiation, and the subsequent ecrypted data exchanges.

I suggest using a specific application for the first process and a different one for the others since only the key negotiation requires all of the libraries. For example you can create the following asslconn.asp file:

<%@language="Javascript"%>
<!--#include file="assl1.2forAsp/assl.asp" -->
<!--#include file="myKey.asp" --><%
aSSL.response(myKey)
%>

The myKey.asp is a file that contains the RSA server key. Look at the following example with a 512-bit key:

<*
var myKey = [
   '91305d87dd6de2944fd6a62ceaa5aae1'+
   '608798c73037747e55ac553b357c4b17'+
   '47848d671df1772fc755c7fdcbb81be1'+
   '3d854794622c29832d189aa1382d8617',
   '10001',
   '223e3701115f965e068a88bcf546c78b'+
   'ca7990b6021042407db25c93cf64964c'+
   'f752072a08c70489ef4a1b8e95d7a948'+
   'de312e46638cd0fcaa03d654b586ef71',
   'c4e3ec8bc8753e7ffb78ce2bda372ae2'+
   '266e3cf309d0940f5f1118c1d2a2bfdf',
   'bcc6e96e460c6c1461737e9a742ca369'+
   '320d60cb15a0310b8be7bc4b6ab720c9',
   '2c315488d387ad6da08e2f089cc44135'+
   'dd9664cbd06a26b1848f1bd57567de55',
   '668c23683cf3288f15b518b42ca1c70f'+
   '311a65574ce31d616959b446bfacc549',
   '9b6eb5314afaffd51cda024facc091f3'+
   '8c2f4554076d638844faa9b0f6e5a8c4'
]
*>

To generate your RSA key you can use the Simple RSA key generator for aSSL.

Any data exchanges following the initial key negotiation won't need all the aSSL files, but rather, only use assl_.asp (the aSSL kernel) and aes.asp (the AES encryption algorithm). You could include them as the following:

<%@language="Javascript"%>
<!--#include file="assl1.2forAsp/assl2.asp" -->

To better understand the process you can download the source of the aSSL 1.2beta ASP Login Example (including the aSSL libraries) by clicking here.
In this example, default.asp is the client-side application, conn.asp is the program that establish the connection, mykey.asp is the RSA key container, and loginCheck.asp is the program that does login autentication.


Thanks
Tom Wu for its BigIntegers and RSA in JavaScript
Chriss Veness for its AES Javascript implementation
Ryan Perry for the PHP aSSL porting 

30-12-2009, Fixed a bug in the aSSL PHP version. Thanks to Thomas Krapp.
19-11-2009, Fixed a bug in the aSSL PHP version. Thanks to Mark Brekelmans.

RSA Key Generator

http://www-cs-students.stanford.edu/~tjw/jsbn/rsa2.html

Parts of the RSA key used in aSSL. mykey.php

Modulus (hex):
BC86E3DC782C446EE756B874ACECF2A115E613021EAF1ED5EF295BEC2BED899D
26FE2EC896BF9DE84FE381AF67A7B7CBB48D85235E72AB595ABF8FE840D5F8DB

Public exponent (hex, F4=0x10001): 3, four hex digits also public

above is the public key

below is the private key

They can be generated http://www-cs-students.stanford.edu/~tjw/jsbn/rsa2.html and installed in mykey.php

Private exponent (hex):
7daf4292fac82d9f44e47af87348a1c0b9440cac1474bf394a1b929d729e5bbc
f402f29a9300e11b478c091f7e5dacd3f8edae2effe3164d7e0eeada87ee817b

P (hex):
ef3fc61e21867a900e01ee4b1ba69f5403274ed27656da03ed88d7902cce693f

Q (hex):
c9b9fcc298b7d1af568f85b50e749539bc01b10a68472fe1302058104821cd65

D mod (P-1) (hex):
9f7fd9696baefc6009569edcbd19bf8d576f89e1a439e6ad4905e50ac8899b7f

D mod (Q-1) (hex):
867bfdd7107a8bca39b503ce09a30e267d567606f02f7540cac03ab5856bde43

1/Q mod P (hex):
