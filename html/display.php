<?php
//Jason Millette
//gets data from html webpage, then calls call display function
//to display on SPI device

//Getting and using values
if (isset ( $_GET["status"] )) {
	$status = strip_tags ($_GET["status"]);
	
	// calling function to display status
	//exec("/usr/bin/python2.7 /var/www/html/infoDisplay.py ".$status, $error, $return);
	//displaying status for debug
        
	exec("./infoDisplay.py ".$status, $error, $return);

        //exec("ls -".$status, $error, $return);

        print_r(array_values($error));
        echo($return."\n");


        


        
}
?>
