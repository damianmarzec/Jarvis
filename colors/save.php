<?php
header('Access-Control-Allow-Origin: *');
echo json_encode($_POST);

file_put_contents("data.txt", file_get_contents('data.txt') .'
'. $_POST['s']);

die;