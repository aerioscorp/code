<?php
$servername = "localhost";
$username = "pfe";
$password = "raspberry";
$database = "pfe";
 
$conn = new mysqli($servername, $username, $password, $database);
 
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$tables = array();

$sql = "SHOW TABLES FROM $database";
$stmt = $conn->prepare($sql);
$stmt->execute();
$stmt->bind_result($tab);
while($stmt->fetch())
{
	array_push($tables, $tab);
}

echo "[";

foreach($tables as $tab)
{
	$data = array();
	$temp = ['table_name'=>$tab];
	array_push($data, $temp);
	$sql = "SELECT * FROM $tab";
	$stmt = $conn->prepare($sql);
	$stmt->execute();
	$stmt->bind_result($date, $valeur);
	while($stmt->fetch()){
		$temp = ['date'=>$date,'valeur'=>$valeur];
		array_push($data, $temp);
	}
	echo json_encode($data).",";
}
 echo "[]]";