<?php
	$login = 'Chewbacca';
	$mdp1 = '@HanSoloO2018!';
	$hash = password_hash($mdp1, PASSWORD_BCRYPT);
	var_dump($hash);
	if (password_verify($mdp1, $hash)) { 
		echo 'Le mot de passe '. $mdp1 . ' est valide !';
	} else {
		echo 'Le mot de passe '. $mdp1 . ' est invalide.';
	}
?>