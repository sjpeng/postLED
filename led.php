<html>
<head><title>BeagleBone LED Controller</title></head>
<?php
$cmd = $_SERVER['PHP_SELF'];
if (isset($_POST['led'])){
	if ($_POST['command']=="on")
		$command = "default-on";
	else if ($_POST['command']=="off")
		$command = "none";
	else 
		$command = "timer";
	
	shell_exec("echo ".$command." > /sys/class/leds/beaglebone:green:usr".$_POST['led']."/trigger");
	
	$stat = shell_exec("cat /sys/class/leds/beaglebone:green:usr".$_POST['led']."/trigger");
	echo "status: ".$stat."<br><br><br><hr>";
}
?>
<body>
	<h1>BeagleBone LED Controller</h1>
		<form action="<?php $cmd;?>" method="POST">
		<div>LED 
		<select name="led">
		  <option>0</option>
		  <option>1</option>
		  <option>2</option>
		  <option>3</option>
		</select>Status: 
			<input type="radio" name="command" value="on" checked/> On 
			<input type="radio" name="command" value="off"/> Off 
			<input type="radio" name="command" value="flash"/> Flash 
			<input type="checkbox" name="status"  checked/> Display Status </div>
			<input type="submit" value="Execute Command" />
		</div>
	</form>
</body></html>