<?php

$baseURL = "http://labs.ideeinc.com/multicolr#colors=F8FD79;";

$contents = file_get_contents($baseURL);

echo $contents;

//preg_match_all("/flickr.com\/photos\/([0-9]+@N[0-9]{2}/[0-9]+)/", $contents, $matches);
preg_match_all("/www.flickr.com/", $contents, $matches);

//var_dump($matches);

?>
