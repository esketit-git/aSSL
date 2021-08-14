# aSSL Ajax SSL - end to end encryption with Javascript
aSSL SSL over Ajax, enables the client to negotiate a secret random 128-bit key with the server using the RSA algorithm. Once the connection has been established, the data will be sent and received using AES algorithm.

aSSL implements a technology similar to SSL without HTTPS over http. Embedded in any client / server application and provide end to end encryption without third party issuer.

The goal of the project is make the end to end encryption more secure. Possibly even ID the server to the client without a certificate issuer.

aSSL enables the client to negotiate a secret random 128-bit key with the server using the RSA algorithm. Once the connection has been established, the data will be sent and received using AES algorithm.

aSSL is composed of some Javascript files and a server side component. I have recently changed the negotiation algoritm from RC4 to RSA, only a pure Javascript (ASP) server component is currently available. Porting for the main web languages (PHP, Java, Perl, Python, TKL, etc.) is required.

How aSSL 1.2 works

1. The browser calls the server to start the process.

2. The server returns its RSA modulus and the public exponent.

3. The browser generates a random exchange 128-bit key, encrypts it using the server public key and passes the encrypted exchange key to the server.

4. The server receives this encrypted 128-bit exchange key, decrypts it with its private key and, if the result is ok, returns the session duration time.

5. The browser receives the session duration time and sets a timeout to maintain alive the connection.

All subsequent client-server exchanges via aSSL are encrypted and decrypted using AES algorithm. aSSL allows multiple secure connections to be established with one or more servers, contemporarily.

The end to end encryption are written in .js (javascript files), the project can be ported to different programming languages or reverted to .js from other languages.

Created by Francesco Sullo - Rome, Italy

Thanks
Tom Wu for its BigIntegers and RSA in JavaScript
Chriss Veness for its AES Javascript implementation
Ryan Perry for the PHP aSSL porting 

30-12-2009, Fixed a bug in the aSSL PHP version. Thanks to Thomas Krapp.

19-11-2009, Fixed a bug in the aSSL PHP version. Thanks to Mark Brekelmans.

RSA Key Generator

http://travistidwell.com/blog/2013/09/06/an-online-rsa-public-and-private-key-generator/

aSSL starting, a brief tutorial

Introduction

aSSL is composed of two parts: a client-side component and a server-side component. The first is always a set of pure Javascript files, the second depends on specific languages (Javascript, PHP, Java, Ruby, etc.).

Client-side installation

Unzip the aSSL zip file and put the files into a subdirectory. Then, include the assl.js files into your HTML. For example:

<script type="text/javascript" 
src="assl/assl.js"></script>

This one include inserts all the aSSL scripts into the page.

Server-side installation

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

aSSL reference


aSSL.connect(uri,callBackFunction[,connectionName])

Client-side method. It starts the process to establish the connection.

uri is the uri of the server-side application

callBackFunction is the function that will be automatically called after connection is established

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

Currently No. SSL is secure because it is a technology implemented at browser level so that when an HTTPS connection has been established, the browser checks the SSL Certificate before continuing.

Suppose a man-in-the-middle (MiTM) attack. With an SSL connection, the attack would be successful only should the user click Ok when the browser alerts him saying that the certificate doesn't correspond to the connected server (the alert may also appear if some file is transferred over HTTP instead of HTTPS because in this file a hacker could inject malicious code).

If a hacker were to attack with a MiTM attack during an aSSL connection, he could be successful.

Password sniffing is much more diffuse because it is much easier. In fact, there are specific softwares that sniff the traffic, recognizes userid and passwords, and register them.

aSSL protects against these sniffers. When a server exchanges account information in clear HTTP, a sniffer can simply intercept all the data, but if the server exchanges the data via aSSL it is not possible to decode the passed data and so the level of security of the site is notably better.

The goal of aSSL development is remedy these issues, perhaps by the server sending an md5 checksum that only the correct server could have produced and too hard toguess in the session time or another idea. 
