var correntNumberWapprer = document.getElementById("currentNumber");
var correntNumber = 0;

function increment() {
    correntNumber = correntNumber + 1;
    correntNumberWapprer.innerHTML = correntNumber;
}

function decrement() {
    correntNumber = correntNumber - 1;
    correntNumberWapprer.innerHTML = correntNumber;
}