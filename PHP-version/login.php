<?php
//start session as RSA key is stored in $_SESSION
session_start();

//the main functions of the protocol
require_once 'assl-php/assl.php';

//decrypt server request
$decrypted = aSSL::decrypt($_POST['data']);

//get associative array from encrypted data
$res = aSSL::querystr($decrypted);

//now the server can compare for valid users
$users = array('guru' => 'jolly', 'admin' => 'crazy');

$result = ($users[$res['nickname']] && $users[$res['nickname']] == $res['password']) ? 1 : 0;
//Returns 1 or 0 to allow access.

//Output result. It can be done with aSSL::send($result) if data returned to server should be encrypted.

//aSSL::write($result);

aSSL::send($result); //must use send
?>
