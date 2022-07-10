
	var audio = new Audio('../shootingstars.mp3');
	audio.play();

function getUser(tabuleiro){
    var user = prompt("Insira um nome de utilizador: ", "default");
    window.location.href = 'GandaGalo?'+tabuleiro+user;
}